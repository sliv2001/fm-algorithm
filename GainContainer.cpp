/*
 * GainContainer.cpp
 *
 *  Created on: 14 апр. 2023 г.
 *      Author: ivans
 */

#include "GainContainer.hpp"
#include <algorithm>

GainContainer::GainContainer(Reader& reader, Partition& partition): reader(reader), partition(partition) {
	for (int i=-reader.getEdgeCount(); i<reader.getEdgeCount(); i++){
		left0[i]=std::list<int>();
		right1[i] = std::list<int>();
	}
}

void GainContainer::initialize() {
	for (int i=0; i<reader.getVertexCount(); i++){
		int gain=0;
		bool isOnlyVertex=1, isOnOneSide=1;
		bool isRight = partition.at(i);
		for (auto& edge : reader.getVertEdge()[i]){
			for (auto& v1 : reader.getEdgeVert()[edge]){
				if (isOnlyVertex && partition.at(v1)==isRight){
					isOnlyVertex=0;
				}
				if (isOnOneSide && partition.at(v1)!=isRight){
					isOnOneSide=0;
				}
				if (!isOnlyVertex && !isOnOneSide)
					break;
			}
			gain+=isOnlyVertex?1:0;
			gain-=isOnOneSide?1:0;
		}
		this->putIntoBucket(i, gain);
	}
}

int GainContainer::getCost() {
	int cost=0;
	for (int vertex=0; vertex<reader.getVertexCount(); vertex++){
		bool isRight=partition.at(vertex);
		for (auto& edge : reader.getVertEdge()[vertex]){
			for (auto& v1 : reader.getEdgeVert()[edge]){
				if (partition.at(v1)!=isRight){
					cost++;
					break;
				}
			}
		}
	}
	return cost;
}

int GainContainer::bestFeasibleMove() {

	int diff = (*right1.rbegin()).first-(*left0.rbegin()).first;
	if (diff>0){
		return *(*right1.rbegin()).second.begin();
	}
	else if (diff<0){
		return *(*left0.rbegin()).second.begin();
	}
	else if (partition.checkBalance()>0){
		return *(*right1.rbegin()).second.begin();
	}
	else if (partition.checkBalance()<0){
		return *(*left0.rbegin()).second.begin();
	}
	else{
		return *(*right1.rbegin()).second.begin();
	}

}

std::map<int, std::list<int> >& GainContainer::getMap(int vertex) {
	return partition.at(vertex)?right1:left0;
}

int GainContainer::getGain(int move) {
	return (*getMap(move).rbegin()).first;
}

bool GainContainer::noVerts(int edge, bool part){
	for (auto& v : reader.getEdgeVert()[edge]){
		if (partition.at(v)==part)
			return 0;
	}
	return 1;
}

int GainContainer::oneV(int edge, bool part) {
	int resV=-1;
	for (auto& v : reader.getEdgeVert()[edge]){
		if (partition.at(v)==part && resV==-1){
			resV = v;
			continue;
		}
		if (partition.at(v)==part && resV!=-1){
			return -1;
		}

	}
	return resV;
}

void GainContainer::gain_update(int move) {
	bool sourcePart = partition.at(move);
	bool destPart = !sourcePart;

	for (auto& edge : reader.getVertEdge()[move]){
		if (noVerts(edge, destPart)){
			for (auto& v : reader.getEdgeVert()[edge])
				update(v, sourcePart, 1);
		}
		if (oneV(edge, sourcePart)>-1){
			for (auto& v : reader.getEdgeVert()[edge])
				update(v, destPart, -1);
		}

		partition.apply(move);
		int v = oneV(edge, sourcePart);
		if (v>-1)
			update(v, sourcePart, 1);
		partition.apply(move);

		v = oneV(edge, destPart);
		if (v>-1)
			update(v, destPart, -1);

	}
}

void GainContainer::update(int vertex, bool part, int delta) {
	auto& mm = part?right1:left0;
	for (auto mapit=mm.rbegin(); mapit!=mm.rend(); mapit--){
		for (auto iter=mapit->second.begin(); iter!=mapit->second.end(); iter++){
			if (*iter==vertex){
				mapit->second.erase(iter);
				(delta>0?mapit++:mapit--)->second.push_front(vertex);
			}
		}
	}
}

void GainContainer::putIntoBucket(int vertex, int gain) {
	getMap(vertex)[gain].push_front(vertex);
}

void GainContainer::remove(int move) {
	getMap(move).rbegin()->second.pop_front();
}

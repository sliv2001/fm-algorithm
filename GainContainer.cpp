/*
 * GainContainer.cpp
 *
 *  Created on: 14 апр. 2023 г.
 *      Author: ivans
 */

#include "GainContainer.hpp"
#include "Parser.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

extern Parser PRS;

//TODO Add skip iterators to all

GainContainer::GainContainer(Reader &reader, Partition &partition) :
		reader(reader), partition(partition), erased(reader.getVertexCount(), 0) {
	searchSupport.reserve(reader.getVertexCount());
}

void GainContainer::resetErased() {
	for (int i = 0; i < erased.size(); i++) {
		erased[i] = 0;
	}
}

void GainContainer::initialize() {
	resetErased();
	for (int i = 0; i < reader.getVertexCount(); i++) {
		int gain = 0;
		bool isRight = partition.at(i);
		for (auto &edge : reader.getVertEdge()[i]) {
			bool isOnlyVertex = 1, isOnOneSide = 1;
			for (auto &v1 : reader.getEdgeVert()[edge]) {
				if (v1 == i)
					continue;
				if (isOnlyVertex && partition.at(v1) == isRight) {
					isOnlyVertex = 0;
				}
				if (isOnOneSide && partition.at(v1) != isRight) {
					isOnOneSide = 0;
				}
				if (!isOnlyVertex && !isOnOneSide)
					break;
			}
			gain += isOnlyVertex ? 1 : 0;
			gain -= isOnOneSide ? 1 : 0;
		}
		this->putIntoBucket(i, gain);
	}
	if (PRS.getDebug())
		printGainBuckets();
}

int GainContainer::getCost() {
	int cost=0;
	for (int edge=0; edge<reader.getEdgeCount(); edge++){
		if (noVerts(edge, false))
			continue;
		if (noVerts(edge, true))
			continue;
		cost++;
	}
	return cost;
}

int GainContainer::bestFeasibleMove() {

	int diff = maxGainR - maxGainL;
	if (partition.checkBalance() > 0)
		return *right1[maxGainR].rbegin();
	else if (partition.checkBalance() < 0)
		return *left0[maxGainL].rbegin();
	else if (diff > 0)
		return *right1[maxGainR].rbegin();
	else if (diff < 0)
		return *left0[maxGainL].rbegin();
	return *right1[maxGainR].rbegin();
}

std::map<int, std::list<int> >& GainContainer::getMap(int vertex) {
	return partition.at(vertex) ? right1 : left0;
}

int GainContainer::getGain(int move) {
	int &maxGain = partition.at(move) ? maxGainR : maxGainL;
	return maxGain;
}

bool GainContainer::noVerts(int edge, bool part) {
	for (auto &v : reader.getEdgeVert()[edge]) {
		if (partition.at(v) == part)
			return 0;
	}
	return 1;
}

int GainContainer::oneV(int edge, bool part) {
	int resV = -1;
	for (auto &v : reader.getEdgeVert()[edge]) {
		if (partition.at(v) == part && resV == -1) {
			resV = v;
			continue;
		}
		if (partition.at(v) == part && resV != -1) {
			return -1;
		}

	}
	return resV;
}

void GainContainer::gain_update(int move) {
	bool sourcePart = partition.at(move);
	bool destPart = !sourcePart;

	for (auto &edge : reader.getVertEdge()[move]) {
		if (noVerts(edge, destPart)) {
			for (auto &v : reader.getEdgeVert()[edge]) {
				if (v == move)
					continue;
				update(v, sourcePart, 1);
			}
		}
		if (oneV(edge, sourcePart) > -1) {
			for (auto &v : reader.getEdgeVert()[edge]) {
				if (v == move)
					continue;
				update(v, destPart, -1);
			}
		}

		partition.apply(move);
		int v = oneV(edge, sourcePart);
		if (v > -1 && v != move)
			update(v, sourcePart, 1);
		partition.apply(move);

		v = oneV(edge, destPart);
		if (v > -1 && v != move)
			update(v, destPart, -1);

	}
}

void GainContainer::update(int vertex, bool part, int delta) {
	if (erased[vertex])
		return;

	auto &mm = part ? right1 : left0;
	int &maxGain = part ? maxGainR : maxGainL;

	auto &pr = searchSupport[vertex];
	auto mapIterator = mm.find(pr.first);
	auto listIterator = pr.second;

	if (*listIterator != vertex)
		throw "Some internal error in GainContainer::update";

	mapIterator->second.erase(listIterator);
	if (mapIterator->second.empty() && mapIterator->first == maxGain) {
		maxGain += delta;
	}
	if (delta>0)
		++mapIterator;
	else
		--mapIterator;
	mm[pr.first+delta].push_back(vertex);
	if (pr.first+delta > maxGain)
		maxGain = pr.first+delta;

	searchSupport[vertex].first+=delta;
	searchSupport[vertex].second = --(mm[pr.first].end());

	if (PRS.getDebug())
		printGainBuckets();
	return;
}

void GainContainer::putIntoBucket(int vertex, int gain) {
	int &maxGain = partition.at(vertex) ? maxGainR : maxGainL;
	getMap(vertex)[gain].push_back(vertex);

	searchSupport[vertex].first=gain;
	searchSupport[vertex].second=--(getMap(vertex)[gain].end());

	if (gain > maxGain)
		maxGain = gain;
}

/*TODO rewrite this*/
int GainContainer::getNextGain(int move,
		std::map<int, std::list<int>>::iterator iter) {
	int gain = partition.at(move) ? maxGainR : maxGainL;
	for (; iter != --(partition.at(move) ? right1 : left0).begin(); iter--) {
		if (!iter->second.empty())
			return gain;
		gain--;
	}
	return -INT_MAX + 1;
}

void GainContainer::remove(int move) {


	if (erased[move])
		return;

	bool part = partition.at(move);
	auto &mm = part ? right1 : left0;
	int &maxGain = part ? maxGainR : maxGainL;

	auto &pr = searchSupport[move];
	auto mapIterator = mm.find(pr.first);
	auto listIterator = pr.second;

	if (*listIterator != move)
		throw "Some internal error in GainContainer::remove";

	mapIterator->second.erase(listIterator);
	erased[move]=1;
	if (mapIterator->second.empty() && mapIterator->first == maxGain) {
		maxGain = getNextGain(move, mapIterator);
	}
	if (PRS.getDebug())
		printGainBuckets();
	return;
}

void GainContainer::printBucket(std::map<int, std::list<int>> &mm) {
	for (auto &a : mm) {
		cout << a.first << ": ";
		for (auto &l : a.second) {
			cout << l << ' ';
		}
		cout << endl;
	}
}

void GainContainer::printGainBuckets() {
	cout << "left bucket" << endl;
	printBucket(left0);
	cout << endl << "right bucket" << endl;
	printBucket(right1);
}

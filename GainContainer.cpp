/*
 * GainContainer.cpp
 *
 *  Created on: 14 апр. 2023 г.
 *      Author: ivans
 */

#include "GainContainer.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

extern bool debug;

//TODO Add skip iterators to all

GainContainer::GainContainer(Reader &reader, Partition &partition) :
		reader(reader), partition(partition), erased(reader.getVertexCount(), 0) {
	for (int i = -reader.getEdgeCount(); i <= reader.getEdgeCount(); i++) {
		left0[i] = std::list<int>();
		right1[i] = std::list<int>();
	}
}

void GainContainer::initialize() {
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
	if (debug)
		printGainBuckets();
}

int GainContainer::getCost() {
	int cost = 0;
	for (int vertex = 0; vertex < reader.getVertexCount(); vertex++) {
		bool isRight = partition.at(vertex);
		for (auto &edge : reader.getVertEdge()[vertex]) {
			for (auto &v1 : reader.getEdgeVert()[edge]) {
				if (partition.at(v1) != isRight) {
					cost++;
					break;
				}
			}
		}
	}
	return cost;
}

//TODO swap gain and balance

int GainContainer::bestFeasibleMove() {

	int diff = maxGainR - maxGainL;
	if (partition.checkBalance() > 0)
		return *right1[maxGainR].begin();
	else if (partition.checkBalance() < 0)
		return *left0[maxGainL].begin();
	else if (diff > 0)
		return *right1[maxGainR].begin();
	else if (diff < 0)
		return *left0[maxGainR].begin();
	return *right1[maxGainR].begin();
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
	for (auto mapit = mm.find(maxGain); mapit != mm.begin(); mapit--) {
		for (auto iter = mapit->second.begin(); iter != mapit->second.end();
				iter++) {
			if (*iter == vertex) {
				mapit->second.erase(iter);
				if (mapit->second.empty() && mapit->first == maxGain) {
					maxGain += delta;
				}
				(delta > 0 ? ++mapit : --mapit)->second.push_front(vertex);
				if (mapit->first > maxGain)
					maxGain = mapit->first;
				printGainBuckets();
				return;
			}
		}
	}
	printGainBuckets();
	throw "Some internal error in GainContainer::update";
}

void GainContainer::putIntoBucket(int vertex, int gain) {
	int &maxGain = partition.at(vertex) ? maxGainR : maxGainL;
	getMap(vertex)[gain].push_front(vertex);
	if (gain > maxGain)
		maxGain = gain;
}

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

/*TODO replace it with better search func*/
void GainContainer::remove(int move) {
	if (erased[move])
		return;
	bool part = partition.at(move);
	auto &mm = part ? right1 : left0;
	int &maxGain = part ? maxGainR : maxGainL;
	for (auto mapit = mm.find(maxGain); mapit != mm.begin(); mapit--) {
		for (auto iter = mapit->second.begin(); iter != mapit->second.end();
				iter++) {
			if (*iter == move) {
				mapit->second.erase(iter);
				erased[move]=1;
				if (mapit->second.empty() && mapit->first == maxGain) {
					maxGain = getNextGain(move, mapit);
				}
				printGainBuckets();
				return;
			}
		}
	}
	throw "Found no vertex " + to_string(move);
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

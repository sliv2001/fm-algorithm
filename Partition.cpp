/*
 * Partition.cpp
 *
 *  Created on: 13 апр. 2023 г.
 *      Author: ivans
 */

#include "Partition.hpp"
#include <cstdlib>

using namespace std;

Partition::Partition(int vertexSize): vertexSize(vertexSize) {
	initPartition(vertexSize);
}

void Partition::initPartition(int vertexSize) {
	contents.reserve(vertexSize);
	for (int i=0; i<vertexSize; i++){
		contents.push_back(rand()%2);
	}
}

void Partition::setOneZeroPartition() {
	for (int i=0; i<contents.size(); i++){
		contents[i]=i%2;
	}
}

int Partition::checkBalance() {
	int test=0;
	for (int i=0; i<contents.size(); i++){
		test+=contents[i]?1:-1;
	}
	return test;
}

int Partition::size() {
	return contents.size();
}

bool Partition::at(int i) {
	return contents[i];
}

void Partition::apply(int move) {
	contents[move]= !contents[move];
}

void Partition::setRandomPartition() {
	for (int i=0; i<vertexSize; i++){
		contents.push_back(rand()%2);
	}
}

void Partition::setSamplePartition() {
#ifdef DEBUG
	if (vertexSize==8){
		contents=vector<bool>({0, 1, 0, 0, 1, 1, 0, 1});
	}
#else
	throw "Use this in debug mode only";
#endif
}

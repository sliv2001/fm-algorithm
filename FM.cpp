/*
 * FM.cpp
 *
 *  Created on: 14 апр. 2023 г.
 *      Author: ivans
 */

#include "FM.hpp"
#include <fstream>

FM::FM(Reader& reader, Partition& partition):reader(reader), partition(partition) {
	// TODO Auto-generated constructor stub
	gc = new GainContainer(reader, partition);
}

void FM::calculate() {
	do{
		oldCost = newCost;
		gc->initialize();
		newCost=FMPass();
	} while (newCost<oldCost);
}

int FM::FMPass() {
	int cost = gc->getCost();
	for (int i=0; i<reader.getVertexCount(); i++){
		int move = gc->bestFeasibleMove();
		cost-=gc->getGain(move);
		gc->gain_update(move);
		gc->remove(move);
		partition.apply(move);
		saveBestMove(move, cost);
	}
	revertToBest();
	partition.print();
	bestCost=INT_MAX;
	bestCostMove=-1;
	return cost;
}

void FM::saveBestMove(int move, int cost) {
	moves.push(move);
	if (cost<bestCost){
		bestCost=cost;
		bestCostMove=moves.size()-1;
	}
}

void FM::revertToBest() {
	int revertCount = moves.size()-bestCostMove-1;
	for (int i=revertCount; i>0; i--){
		partition.apply(moves.top());
		moves.pop();
	}

}

void FM::save(std::string path) {
	std::ofstream fout(path, std::ios_base::out);
	if (!fout.is_open())
		throw "Could not open output file";
	for (int i=0; i<reader.getVertexCount(); i++){
		fout<<partition.at(i)<<std::endl;
	}
}

/*
 * FM.cpp
 *
 *  Created on: 14 апр. 2023 г.
 *      Author: ivans
 */

#include "FM.hpp"
#include "Parser.hpp"
#include <fstream>
#include <iostream>

using namespace std;

extern Parser PRS;

FM::FM(Reader& reader, Partition& partition):reader(reader), partition(partition) {
	// TODO Auto-generated constructor stub
	gc = new GainContainer(reader, partition);
}

void FM::calculate() {
	do{
		oldCost = newCost;
		gc->initialize();
		newCost=FMPass();
		cout<<"New partition cost: "<<newCost<<endl;
	} while (newCost<oldCost);
}

int FM::FMPass() {
	int cost = gc->getCost();
	bestCost=cost;
	int minLocalCost=cost;
	for (int i=0; i<reader.getVertexCount(); i++){
		int move = gc->bestFeasibleMove();
		cost-=gc->getGain(move);
		gc->gain_update(move);
		gc->remove(move);
		partition.apply(move);
		saveBestMove(move, cost);
		if (minLocalCost>cost)
			minLocalCost=cost;
		if (cost>minLocalCost && PRS.getMod())
			break;
	}
	revertToBest();
	if (PRS.getDebug())
		partition.print();
//	bestCost=cost;
	bestCostMove=-1;
	if (cost<=0 || bestCost<=0)
		throw "Cost became negative.";
	return bestCost;
}

void FM::saveBestMove(int move, int cost) {
	moves.push(move);

	if (cost<bestCost && partition.checkBalance()<=1 && partition.checkBalance()>=-1){
		bestCost=cost;
		bestCostMove=moves.size()-1;
	}
}

void FM::clearMoves() {
	while (!moves.empty())
		moves.pop();
}

void FM::revertToBest() {
	int revertCount = moves.size()-bestCostMove-1;
	for (int i=revertCount; i>0; i--){
		partition.apply(moves.top());
		if (PRS.getDebug())
			partition.print();
		moves.pop();
	}
	clearMoves();
}

void FM::save(std::string path) {
	std::ofstream fout(path, std::ios_base::out);
	if (!fout.is_open())
		throw "Could not open output file";
	for (int i=0; i<reader.getVertexCount(); i++){
		fout<<partition.at(i)<<std::endl;
	}
}

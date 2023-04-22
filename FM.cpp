/*
 * FM.cpp
 *
 *  Created on: 18 апр. 2023 г.
 *      Author: ivans
 */

#include "FM.hpp"
#include "Parser.hpp"
#include <set>
#include <fstream>
#include <iostream>

extern Parser PRS;

FM::FM(Graph &g, Partition &p): g(g), isMod(PRS.getMod()) {
	using std::chrono::high_resolution_clock;
	using std::chrono::duration_cast;
	using std::chrono::duration;
	using std::chrono::milliseconds;
	using namespace std;

	auto start=high_resolution_clock::now();

	while(1) {
		GainContainer gc(g, p);
		int Best = this->FMPass(gc, g, p);
		if (Best == p.getCost())
			break;
		p.setCost(Best);
	}

	auto finish = high_resolution_clock::now();
	auto ms_int = duration_cast<milliseconds>(finish - start);

//	cout<< "Execution time: ";
//	cout << ms_int.count() << "ms\n" <<endl;
//	cout << "Cost of partition: "<< p.getCost()<<endl;
	cout<<ms_int.count() << " "<< p.getCost();
}

int FM::FMPass(GainContainer &gc, Graph &g, Partition &p){
	std::set<int> vertsToMove;
	int cost = p.getCost(), best_cost = p.getCost();
	for (int color = p.getIsRight(); !gc.is_empty(p.getIsRight()); color = p.getIsRight()){
		std::pair<unsigned, int> currentGain = gc.best_feasible_move(color);
		vertsToMove.insert(currentGain.first);
		cost -= currentGain.second;
		if (cost < best_cost) {
			best_cost = cost;
			vertsToMove.clear();
		}
		if (cost>best_cost+PRS.getModValue() && isMod){
			break;
		}
		gainUpdate(gc, g, p, currentGain.first);
	}
	for (auto v : vertsToMove)
		p.apply(v);
	return best_cost;
}

void FM::gainUpdate(GainContainer &gc, Graph &g, Partition &p,
		unsigned movedVertex) {
	for (auto e : g.getVertEdge()[movedVertex]) {
		int no_v_in_dest = 1, is_1v_in_source = 1, v_dest_num = 0, v_source_num = 0;
		unsigned v_dest = 0, v_source = 0;
		for (auto v : g.getEdgeVert()[e]) {
			if (p.getIsRight() ^ p.getPartition()[v])
				no_v_in_dest = 0, v_dest_num++, v_dest = v;
			else if (v != movedVertex)
				v_source = v, v_source_num++;
			if (p.getPartition()[movedVertex] == p.getPartition()[v] && v != movedVertex)
				is_1v_in_source = 0;
		}
		int UpdateVal = no_v_in_dest ? 1 : is_1v_in_source ? -1 : 0;
		if (UpdateVal)
			for (auto v : g.getEdgeVert()[e])
				gc.update(v, p.getPartition()[v], UpdateVal);
		if (v_source_num == 1)
			gc.update(v_source, p.getPartition()[v_source], 1);
		if (v_dest_num == 1)
			gc.update(v_dest, p.getPartition()[v_dest], -1);
	}
	gc.erase(movedVertex, p.getPartition()[movedVertex]);
	gc.update_deleted(movedVertex);
	p.apply(movedVertex);
}

void FM::save(std::string path, Partition &p) {
	std::ofstream fout(path, std::ios_base::out);
	if (!fout.is_open())
		throw "Could not open output file";
	for (int i=0; i<g.getVertEdge().size(); i++){
		fout<<p.getPartition()[i]<<std::endl;
	}
}

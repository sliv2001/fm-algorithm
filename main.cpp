/*
 * main.cpp
 *
 *  Created on: 18 апр. 2023 г.
 *      Author: ivans
 */

#include "Parser.hpp"
#include "Graph.hpp"
#include "Partition.hpp"
#include "FM.hpp"
#include <iostream>

#define GRAPH_PART_EXT ".part.2"

using namespace std;

Parser PRS;

int main(int argc, char** argv){

	PRS = Parser(argc, argv);
	string path = PRS.getPath();

	cout<<path<<" ";

	Graph g(path);
	Partition p(g);
	FM solver(g, p);
	solver.save(path+GRAPH_PART_EXT, p);

	return 0;
}


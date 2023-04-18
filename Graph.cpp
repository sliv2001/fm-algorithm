/*
 * Graph.cpp
 *
 *  Created on: 18 апр. 2023 г.
 *      Author: ivans
 */

#include "Graph.hpp"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void Graph::initVectors_inGraph(int edge, int vert) {
	for (int i=0; i<edge; i++)
		edgeVert.push_back(vector<int>());
	for (int i=0; i<vert; i++)
		vertEdge.push_back(vector<int>());
}

Graph::Graph(std::string path) {

	ifstream fin(path, ios_base::in);
	if (!fin.is_open()){
		throw "Could not open the file "+path;
	}
	fin>>edgeCount;
	fin>>vertCount;
	while ('\n'!=fin.get());


	int currentEdge=0;
	string strBuf;
	initVectors_inGraph(edgeCount, vertCount);
	while (!fin.eof()){

		std::getline(fin, strBuf);
		stringstream strs(strBuf);
		while (!strs.eof()){
			int num;
			if (!(strs>>num)){
				break;
				//	throw "Something went wrong with reading edge "+to_string(currentEdge);
			}
			edgeVert[currentEdge].push_back(num-1);
			vertEdge[num-1].push_back(currentEdge);
		}
		currentEdge++;
	}
}


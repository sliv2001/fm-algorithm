/*
 * Reader.cpp
 *
 *  Created on: 13 апр. 2023 г.
 *      Author: ivans
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include "Reader.hpp"

using namespace std;

void Reader::initVectors_inGraph(int edge, int vert) {
	for (int i=0; i<edge; i++)
		edgeVert.push_back(vector<int>());
	for (int i=0; i<vert; i++)
		vertEdge.push_back(vector<int>());
}

Reader::Reader(string path) {
	ifstream fin(path, ios_base::in);
	if (!fin.is_open()){
		throw "Could not open the file "+path;
	}
	fin>>edgeCount;
	fin>>vertexCount;
	while ('\n'!=fin.get());


	int currentEdge=0;
	string strBuf;
	initVectors_inGraph(edgeCount, vertexCount);
	while (!fin.eof()){

		std::getline(fin, strBuf);
		stringstream strs(strBuf);
		while (!strs.eof()){
			int num;
			if (!(strs>>num)){
				break;
//				throw "Something went wrong with reading edge "+to_string(currentEdge);
			}
			edgeVert[currentEdge].push_back(num-1);
			vertEdge[num-1].push_back(currentEdge);
		}
		currentEdge++;
	}
}

void Reader::printMatrix() {
	for (auto& i : edgeVert){
		for (int j : i)
			cout<<j<<' ';
		cout<<endl;
	}
}

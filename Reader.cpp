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
	while (!fin.eof()){
		edgeVert.push_back(vector<int>());
		vertEdge.push_back(vector<int>());

		std::getline(fin, strBuf);
		stringstream strs(strBuf);
		while (!strs.eof()){
			int num;
			if (!(strs>>num)){
				break;
//				throw "Something went wrong with reading edge "+to_string(currentEdge);
			}
			edgeVert[currentEdge].push_back(num);
			vertEdge[num].push_back(currentEdge);
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

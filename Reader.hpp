/*
 * Reader.hpp
 *
 *  Created on: 13 апр. 2023 г.
 *      Author: ivans
 */

#ifndef READER_HPP_
#define READER_HPP_

#include <string>
#include <vector>

class Reader {
private:
	int vertexCount=0;
	int edgeCount=0;

	std::vector<std::vector<int>> edgeVert;
	std::vector<std::vector<int>> vertEdge;

	void initVectors_inGraph(int edge, int vert);

public:
	Reader(std::string path);
	virtual ~Reader(){};
	void printMatrix();

	int getVertexCount() const {return vertexCount;}
	int getEdgeCount() const {return edgeCount;}
	const std::vector<std::vector<int> >& getEdgeVert() const {return edgeVert;}
	const std::vector<std::vector<int> >& getVertEdge() const {return vertEdge;}
};

#endif /* READER_HPP_ */

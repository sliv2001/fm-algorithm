/*
 * Graph.hpp
 *
 *  Created on: 18 апр. 2023 г.
 *      Author: ivans
 */

#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <string>

class Graph {
private:
	int edgeCount;
	int vertCount;
	std::vector<std::vector<int>> vertEdge;
	std::vector<std::vector<int>> edgeVert;

	void initVectors_inGraph(int edge, int vert);
public:
	Graph(std::string path);
	virtual ~Graph() {
	}
	const std::vector<std::vector<int> >& getEdgeVert() const {
		return edgeVert;
	}

	const std::vector<std::vector<int> >& getVertEdge() const {
		return vertEdge;
	}
	;
};

#endif /* GRAPH_HPP_ */

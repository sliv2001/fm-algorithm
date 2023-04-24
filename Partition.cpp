/*
 * Partition.cpp
 *
 *  Created on: 18 апр. 2023 г.
 *      Author: ivans
 */

#include "Partition.hpp"
#include <algorithm>

Partition::Partition(Graph &g) {
	size_t size = g.getVertEdge().size();
	contents = std::vector<bool>(size, 0);
	for (size_t i = size / 2; i < size; contents[i++] = 1)
		isRight = (size-1) % 2;
	calculate_cost(g);
}

void Partition::calculate_cost(Graph &g) {
	for (auto it = g.getEdgeVert().begin(); it != g.getEdgeVert().end(); ++it)
		if (std::any_of(std::begin(*it), std::end(*it), [this, it](int v){return contents[v] != contents[(*it).front()];}))
			cost++;
}

void Partition::apply(int move) {
	isRight += contents[move] ? -1 : 1;
	contents[move] = !contents[move];
}

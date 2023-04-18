/*
 * GainContainer.cpp
 *
 *  Created on: 18 апр. 2023 г.
 *      Author: ivans
 */

#include "GainContainer.hpp"

#include <algorithm>

GainContainer::GainContainer(Graph &g, Partition &p) {
	size_t prt_size = p.getPartition().size();
	erased = std::vector<bool>(prt_size, false);
	gain = std::vector<int>(prt_size);
	its = std::vector<std::list<int>::iterator>(prt_size);
	for (unsigned i = 0; i != prt_size; ++i) {
		int current_gain = 0, current_prt = p.getPartition()[i];
		for (unsigned e : g.getVertEdge()[i]) {
			bool from_block = true, to_block = true;
			for (unsigned v : g.getEdgeVert()[e]) {
				if (current_prt != p.getPartition()[v])
					to_block = false;
				else if (v != i)
					from_block = false;
			}
			if (from_block)
				current_gain++;
			if (to_block)
				current_gain--;
		}
		getMap(current_prt)[current_gain].push_back(i);
		its[i] = std::prev(std::end(getMap(current_prt)[current_gain]));
		gain[i] = current_gain;

	}

}

std::map<int, std::list<int> >& GainContainer::getMap(int isRight) {
	return isRight ? right1 : left0;
}

std::pair<unsigned, int> GainContainer::best_feasible_move(int isRight) {
	std::map<int, std::list<int> > &c = getMap(isRight);
	auto&& [gainN, verticesN] = *c.rbegin();
	unsigned v = verticesN.front();
	auto ret = std::make_pair(v, gainN);
	verticesN.pop_front();
	erased[v] = true;
	if ((verticesN).empty())
		c.erase(std::prev(c.end()));
	return ret;
}

void GainContainer::update(unsigned vertex, int isRight, int value) {
	if (erased[vertex])
		return;
	erase(vertex, isRight);
	gain[vertex] += value;
	getMap(isRight)[gain[vertex]].push_front(vertex);
	its[vertex] = std::begin(getMap(isRight)[gain[vertex]]);
}

void GainContainer::erase(unsigned vertex, int isRight) {
	if(erased[vertex])
		return;
	getMap(isRight)[gain[vertex]].erase(its[vertex]);
	if (getMap(isRight)[gain[vertex]].empty())
		getMap(isRight).erase(gain[vertex]);
}

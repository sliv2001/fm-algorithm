/*
 * GainContainer.hpp
 *
 *  Created on: 18 апр. 2023 г.
 *      Author: ivans
 */

#ifndef GAINCONTAINER_HPP_
#define GAINCONTAINER_HPP_

#include "Graph.hpp"
#include "Partition.hpp"
#include <map>
#include <list>

class GainContainer {
private:
	std::vector<std::list<int>::iterator> its;
	std::map<int, std::list<int>> left0;
	std::map<int, std::list<int>> right1;
	std::vector<int> gain;
	std::vector<bool> erased;
	std::map<int, std::list<int>> &getMap(int color);
public:
	GainContainer(Graph& g, Partition& p);
	std::pair<unsigned, int> best_feasible_move(int color);
	bool is_empty(int color){return getMap(color).empty();};
	void update(unsigned vertex, int color, int value);
	void erase(unsigned vertex, int color);
	void update_deleted(unsigned vertex){erased[vertex]=true;};
};

#endif /* GAINCONTAINER_HPP_ */

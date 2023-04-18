/*
 * Partition.hpp
 *
 *  Created on: 18 апр. 2023 г.
 *      Author: ivans
 */

#ifndef PARTITION_HPP_
#define PARTITION_HPP_

#include "Graph.hpp"

class Partition {
private:
	std::vector<bool> contents;
	int isRight;
	int cost;
	void calculate_cost(Graph &g);
public:
	Partition(Graph &g);
	void apply(int move);
	virtual ~Partition() {
	}
	int getCost() const {
		return cost;
	}

	void setCost(int cost) {
		this->cost = cost;
	}

	int getIsRight() const {
		return isRight;
	}

	std::vector<bool>& getPartition() {
		return contents;
	}

	;
};

#endif /* PARTITION_HPP_ */

/*
 * Partition.hpp
 *
 *  Created on: 13 апр. 2023 г.
 *      Author: ivans
 */

#ifndef PARTITION_HPP_
#define PARTITION_HPP_

#include <vector>
#include <stack>
#include "Reader.hpp"

class Partition {
private:
	std::vector<bool> contents;
	std::stack<int> workOrder;
	int vertexSize;
public:
	Partition(int vertexSize);
	virtual ~Partition(){};
	void initPartition(int vertexSize);
	void setOneZeroPartition();
	void setRandomPartition();
	void setSamplePartition();
	int checkBalance();
	int size();
	bool at(int i);
	void apply(int move);
	void print();
};

#endif /* PARTITION_HPP_ */

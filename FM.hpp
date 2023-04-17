/*
 * FM.hpp
 *
 *  Created on: 14 апр. 2023 г.
 *      Author: ivans
 */

#ifndef FM_HPP_
#define FM_HPP_

#include "Reader.hpp"
#include "Partition.hpp"
#include "GainContainer.hpp"
#include <stack>

class FM {
private:
	Reader& reader;
	Partition& partition;
	GainContainer* gc;
	int newCost=INT_MAX;
	int oldCost=INT_MAX;
	std::stack<int> moves;
	int bestCost=INT_MAX;
	int bestCostMove=-1;
	int FMPass();
	void saveBestMove(int move, int cost);
	void revertToBest();
	void clearMoves();

public:
	FM(Reader& reader, Partition& partition);
	virtual ~FM(){delete gc;};
	void calculate();
	void save(std::string path);
};

#endif /* FM_HPP_ */

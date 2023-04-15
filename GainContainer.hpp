/*
 * GainContainer.hpp
 *
 *  Created on: 14 апр. 2023 г.
 *      Author: ivans
 */

#ifndef GAINCONTAINER_HPP_
#define GAINCONTAINER_HPP_

#include "Reader.hpp"
#include "Partition.hpp"
#include <map>
#include <list>

class GainContainer {
private:
	Reader& reader;
	Partition& partition;
	std::map<int, std::list<int>> left0;
	std::map<int, std::list<int>> right1;
	int maxGainL=-INT_MAX+1;
	int maxGainR=-INT_MAX+1;

	bool noVerts(int edge, bool part);
	int oneV(int edge, bool part);
	void printBucket(std::map<int, std::list<int>>& mm);

public:
	GainContainer(Reader& reader, Partition& partition);
	virtual ~GainContainer(){};
	void initialize();
	int getCost();
	int bestFeasibleMove();
	std::map<int, std::list<int>>& getMap(int vertex);
	int getGain(int move);
	void gain_update(int move);
	void update(int vertex, bool part, int delta);
	void putIntoBucket(int vertex, int gain);
	void remove(int move);
	void printGainBuckets();
};

#endif /* GAINCONTAINER_HPP_ */

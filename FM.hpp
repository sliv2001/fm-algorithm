/*
 * FM.hpp
 *
 *  Created on: 18 апр. 2023 г.
 *      Author: ivans
 */

#ifndef FM_HPP_
#define FM_HPP_

#include "Graph.hpp"
#include "Partition.hpp"
#include "GainContainer.hpp"

class FM {
private:
	Graph &g;
	bool isMod;
public:
	FM(Graph &g, Partition &p);
	virtual ~FM(){};
	int FMPass(GainContainer &gc, Graph &g, Partition &p);
	void gainUpdate(GainContainer &gc, Graph &g, Partition &p, unsigned move_vertex);
	void save(std::string path, Partition &p);
};

#endif /* FM_HPP_ */

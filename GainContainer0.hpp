///*
// * GainContainer.hpp
// *
// *  Created on: 13 апр. 2023 г.
// *      Author: ivans
// */
//
//#ifndef GAINCONTAINER0_HPP_
//#define GAINCONTAINER0_HPP_
//
//#include <map>
//#include <list>
//#include "Reader.hpp"
//#include "Partition.hpp"
//
//class GainContainer0 {
//private:
//	Reader& reader;
//	Partition& partition;
//	std::map<int, std::list<int>> left0;
//	std::map<int, std::list<int>> right1;
//	std::vector<bool> existPos;
//	std::vector<bool> existNeg;
//
//	std::map<int, std::list<int>>& getMap(int index);
//	std::vector<bool>& getExist(int edgeIndex);
//public:
//	GainContainer0(Reader& reader, Partition& partition);
//	virtual ~GainContainer0(){};
//	void fillContainer();
//	void initContainer();
//	void iterate();
//};
//
//#endif /* GAINCONTAINER0_HPP_ */

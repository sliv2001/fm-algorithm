///*
// * GainContainer.cpp
// *
// *  Created on: 13 апр. 2023 г.
// *      Author: ivans
// */
//
//#include "GainContainer0.hpp"
//
//using namespace std;
//
//GainContainer0::GainContainer0(Reader& reader, Partition& partition)
//:reader(reader), partition(partition),
// existPos(reader.getEdgeCount(), 0),
// existNeg(reader.getEdgeCount(), 0)
//{}
//
//std::map<int, std::list<int>>& GainContainer0::getMap(int index){
//	return partition.at(index)?right1:left0;
//}
//
//void GainContainer0::fillContainer() {
//	vector<int> gains(reader.getVertexCount(), 0);
//	int localGain=0;
//	bool isOnlyVertex=1, isOnOneSide=1;
//	for (auto& net : reader.getEdgeVert()){
//		for (auto& vertex : net){
//			bool isRight=partition.at(vertex);
//			for (auto &v1 : net){
//				if (isOnlyVertex && partition.at(v1)==isRight){
//					isOnlyVertex=0;
//				}
//				if (isOnOneSide && partition.at(v1)!=isRight){
//					isOnOneSide=0;
//				}
//			}
//			localGain+=isOnlyVertex?1:0;
//			localGain-=isOnOneSide?1:0;
//			gains[vertex]+=localGain;
//		}
//	}
//
//	for (int i=0; i<reader.getVertexCount(); i++){
//		if (!getExist(gains[i])[gains[i]]){
//			getMap(i)[gains[i]]=list<int>();
//			getMap(i)[gains[i]].push_back(i);
//			getExist(gains[i])[gains[i]]=1;
//		}
//		else{
//			getMap(i)[gains[i]].push_back(i);
//		}
//	}
//
//}
//
//std::vector<bool>& GainContainer0::getExist(int edgeIndex) {
//	return edgeIndex>=0?existPos:existNeg;
//}
//
//void GainContainer0::iterate() {
//	for (int i=0; i<reader.getVertexCount(); i++){
//		int diff = (*right1.rbegin()).first-(*left0.rbegin()).first;
//		if (diff>0){
//			auto& vertexi = ((*right1.rbegin()).second.begin());
//			int vertex= *vertex;
//			(*right1.rbegin()).second.pop_back();
//			partition[vertex]= !partition[vertex];
//		}
//		else if (diff<0){
//			auto& vertexi = ((*left0.rbegin()).second.begin());
//			int vertex= *vertex;
//			(*left0.rbegin()).second.pop_back();
//			partition[vertex]= !partition[vertex];
//		}
//		else if (partition.checkBalance()>0){
//			auto& vertexi = ((*right1.rbegin()).second.begin());
//			int vertex= *vertex;
//			(*right1.rbegin()).second.pop_back();
//			partition[vertex]= !partition[vertex];
//		}
//		else if (partition.checkBalance()<0){
//			auto& vertexi = ((*left0.rbegin()).second.begin());
//			int vertex= *vertex;
//			(*left0.rbegin()).second.pop_back();
//			partition[vertex]= !partition[vertex];
//		}
//		else{
//
//		}
//	}
//}

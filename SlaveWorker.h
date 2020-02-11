#ifndef ___SlaveWorker_H___
#define ___SlaveWorker_H___

#include <string> 
#include <iostream>
#include <fstream>

#include "SlaveHash.h"
#include "Optree.h"
#include <list>
#include <vector>

class SlaveWorker
{
	private:		
		std::ifstream is;  
		std::list<SlaveDataStruct*> dataStructPool;		
		
		SlaveDataStruct* treeSrc;
		
	public:
		std::string getAttemptId();
		std::string getOperatorStartTime(std::string _state, int _id); 
		std::string getOperatorEndTime(std::string _state, int _id); 
		int getOperatorRows(int _id);
		
		std::vector<Optree*> OptreePool;
		int OptreeTransformation();
		OptreeNode* getOptree(int _treeNum, int _index);
		SlaveWorker( std::string _address );
		virtual ~SlaveWorker();
};

#endif //___SlaveWorker_H___

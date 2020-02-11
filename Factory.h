#ifndef ___FACTORY_H___
#define ___FACTORY_H___

#include <iostream> 
#include <vector>
#include "C_Debug.h"
#include "MasterFileIn.h"
#include "SlaveFileIn.h"
#include "Task.h"
#include "TasksStruct.h"
#include "Tree.h"

class Factory: public MasterFileIn, public SlaveFileIn
{
	private:
		std::list<std::string> type_set;
		std::list<Task*> all_task;
		int numOfAttempt;
		int numOfSection;
		
		int MasterDealingProcess(std::string _locate);
		int SlaveDealingProcess();
		int DebugDealingProcess();
		int SlaveOptreeTransformingProcess();
		
	public:
		int MainProcess();
		std::vector<Optree*> treesPool;				//Do not need to delete the pointers in the vector
		std::vector<Optree*> combinedTreePool;
		std::vector<std::string> fileNamePool;
		Tree<Optree*> integratedTree;
		int getTree();
		int CombineTree();
		OptreeNode* getOptree(int _slaveWorkerNum, int _treeNum, int _index);
		
		int Clear();
	
		Factory();
		virtual ~Factory();
};

#endif //___FACTORY_H___

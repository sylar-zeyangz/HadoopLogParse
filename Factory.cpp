#include "Factory.h"

//#pragma comment(lib."json_vc71_libmt.lib")

Factory::Factory()
{
	numOfSection = 0;
	numOfAttempt = 0;
	
	WIN32_FIND_DATAA wfd;
	std::string path =  "LogData/master/";
	std::string des = "LogData/master/*.jhist";  
	HANDLE hFile = FindFirstFile(des.c_str(),&wfd);  
	if(INVALID_HANDLE_VALUE == hFile)  
	{  
	    C_DBG_ERR("FILE TYPE WRONG!\n");  
	    return;  
	}
	do
	{  
		path = path.append(wfd.cFileName);
	    fileNamePool.push_back(path);  
	    std::cout<<"Master Logs File: "<<path<<std::endl;
	    path =  "LogData/master/"; 
	}while(FindNextFile(hFile,&wfd));  
}

int Factory::MasterDealingProcess(std::string _locate)
{
	clock_t creatTaskBegin, creatTaskEnd;
	//LocateFile();
	//locate = "LogData/master/HIVE_Q3_2.jhist";
	ReadJsonFromFile( _locate.c_str() );											//can be created as a loop

	std::list<Json::Value*>::iterator it;
	creatTaskBegin = clock();
	
	for(it = value_pool.begin(); it != value_pool.end(); ++it)
	{	
		all_task.push_back(new Task( (**it) ));
		if( (**it)["type"] == "MAP_ATTEMPT_STARTED" || (**it)["type"] == "REDUCE_ATTEMPT_STARTED" ||
			(**it)["type"] == "MAP_ATTEMPT_FINISHED" || (**it)["type"] == "REDUCE_ATTEMPT_FINISHED" ||
			(**it)["type"] == "MAP_ATTEMPT_KILLED" || (**it)["type"] == "REDUCE_ATTEMPT_KILLED" )
		{
			numOfAttempt++;
		}
			
		numOfSection++;
	}

	creatTaskEnd = clock();
	std::cout << "Time of Dealing Master Logs: " << creatTaskEnd - creatTaskBegin << "ms" << std::endl;
}

int Factory::SlaveDealingProcess()
{
	TasksStruct* tasks_struct = new TasksStruct( all_task, numOfAttempt );	
	for(int i = 0; i < tasks_struct->getMatchesCount(); i++)
	{
		std::cout << "--------------------------" << std::endl;
		std::cout << "ATTEMPT_OF_TASK_"<< i <<"\n"; 
		tasks_struct->attemptMatch[i]->Display();
		
		slaveWorkerPool.push_back( new SlaveWorker( LocateSlaveFile( tasks_struct->attemptMatch[i]->startAttempt->getTrackerName(),
					     tasks_struct->attemptMatch[i]->startAttempt->getContainerid() )) ); 
			     
		if(tasks_struct->attemptMatch[i]->backUpStartAttempt)
		{
			if(tasks_struct->attemptMatch[i]->killedAttempt == NULL)
			{
					C_DBG_ERR("!!!");
			}
		
			slaveWorkerPool.push_back( new SlaveWorker( LocateSlaveFile( tasks_struct->attemptMatch[i]->backUpStartAttempt->getTrackerName(),
					  	 tasks_struct->attemptMatch[i]->backUpStartAttempt->getContainerid() )) );
		}
	}
}

int Factory::getTree()
{
	fprintf(stderr, "slaveWorkerPoolsize: %d\n",slaveWorkerPool.size());
	
	for(int i = 0; i < slaveWorkerPool.size(); i++)
	{
		if(slaveWorkerPool[i]->OptreePool.size() < 1)
			continue;
		treesPool.push_back(slaveWorkerPool[i]->OptreePool[0]); 
	}
} 
int Factory::CombineTree()
{
	for(int i = 0; i < treesPool.size(); i++)
	{
		if(combinedTreePool.size() == 0)
		{
			combinedTreePool.push_back( new Optree(NULL) );
			(*(combinedTreePool[i])) += treesPool[i];
			if(i != 0)
				C_DBG_ERR("treesPool combined logical error!\n");
			continue;
		}
		bool flag_combinable = false;

		for(int j = 0; j < combinedTreePool.size(); j++)
		{
			if( ((*(combinedTreePool[j])) += treesPool[i] ) == -1)
			{
				C_DBG_ERR("CAN NOT COMBINE CURRENT TREES\n");
			}
			else
			{
				if(flag_combinable == true)
					C_DBG_ERR("Element tree has two combinable trees in CombinedTreePool!\n");
				flag_combinable = true;
			}
		}
		if(flag_combinable == false)
		{
			combinedTreePool.push_back( new Optree(NULL) );
			(*(combinedTreePool[combinedTreePool.size() - 1])) += treesPool[i];
		}	
	}
	
	
	Optree* blank_tree = new Optree(NULL);
	
	return 0;
}

int Factory::DebugDealingProcess()
{
	
}

int Factory::SlaveOptreeTransformingProcess()
{
	int i = 0;
	std::list<SlaveWorker*>::iterator it;
	
	for(i = 0; i < slaveWorkerPool.size(); i++)
	{
		slaveWorkerPool[i]->OptreeTransformation();
	}
}

int Factory::MainProcess()
{
	//std::string str[4] = {"LogData/master/HIVE_Q3_1.jhist",
	//					    "LogData/master/HIVE_Q3_2.jhist",
	//					    "LogData/master/HIVE_Q3_3.jhist",
	//				 	    "LogData/master/HIVE_Q3_4.jhist"
	//				 	   };			 	 
	//for(int i = 0; i < 4; i++)
	for(int i = 0; i < fileNamePool.size(); i++)
	{
		int parentNo = -1;
		Clear();
		MasterDealingProcess(fileNamePool[i]);
		SlaveDealingProcess();
		SlaveOptreeTransformingProcess();
		getTree();
		CombineTree();
		if(combinedTreePool.size() < 1 || combinedTreePool.size() > 2)
		{
			C_DBG_ERR("treesPool SIZE ERROR size=0/>2\n");	
		}
		fprintf( stderr,"combinedTreePoolSIZE:%d\n",combinedTreePool.size());
		
		for(int j = 0; j < combinedTreePool.size(); j++)
		{
			fprintf( stderr,"rootName:%s\n",combinedTreePool[j]->root->name.c_str());
			if(combinedTreePool[j]->root->name == "MAP")
			{
				integratedTree.PushAsParent(combinedTreePool[j]); 
				parentNo = j;
				C_DBG_ERR("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
			}	
		}

		if(parentNo == -1)
		{
			C_DBG_ERR("NO PARENT\n");	
		}
		for(int j = 0; j < combinedTreePool.size(); j++)
		{
			if(j != parentNo)
			{
				integratedTree.PushAsParent(combinedTreePool[j]);
			}
		}
	}
}

int Factory::Clear()
{
	combinedTreePool.clear();
	
	std::list<Task*>::iterator it;
	for(it = all_task.begin(); it != all_task.end(); ++it)
	{
		delete (*it);
	}
	all_task.clear();
	
	/*
	for(int i = 0; i < treesPool.size(); i++)
	{
		delete treesPool[i];
	}
	*/
	treesPool.clear();
	
	MasterFileIn::Clear();
	SlaveFileIn::Clear();
}

OptreeNode* Factory::getOptree(int _slaveWorkerNum, int _treeNum, int _index)
{
	if(	_slaveWorkerNum >= slaveWorkerPool.size() )
		return (OptreeNode*)0xFFFFFFFF;
	return slaveWorkerPool[_slaveWorkerNum]->getOptree(_treeNum, _index);
}

Factory::~Factory()
{
	Clear();
}

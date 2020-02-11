#include "TasksStruct.h"

TasksStruct::TasksStruct( std::list<Task*> _all_task, int _numOfAttempt )
{
	std::list<Task*>::iterator it;
	std::vector<std::string> attemptIdPool;
	std::cout << _numOfAttempt << std::endl;
	attemptName = new std::string[_numOfAttempt];
	//attemptMatch = new AttemptMatch[_numOfAttempt / 2];

	for(it = _all_task.begin(); it != _all_task.end(); ++it)
	{	
		if((*it)->getAttemptid() == "")
		{
			continue;
		}
		int repeatFlag = false;
		for(int j = 0; j < attemptIdPool.size(); j++)
		{
			if(attemptIdPool[j] == (*it)->getAttemptid().substr(0, 35))
			{
				repeatFlag = true;		
			}
		}
		if(repeatFlag == false)
		{
			attemptIdPool.push_back((*it)->getAttemptid().substr(0, 35));
		}
	}
	char* monkeyTable = new char[attemptIdPool.size()*4];
	for(int i = 0; i < attemptIdPool.size() * 4; i++)
	{
		monkeyTable[i] = 0;
	}
 	attemptMatch.resize(attemptIdPool.size());
 	for(int i = 0; i < attemptMatch.size(); i++)
 	{
 		attemptMatch[i] = new AttemptMatch();
 	}
	for(it = _all_task.begin(); it != _all_task.end(); ++it)
	{
		int NO = -1;
		for(int j = 0; j < attemptIdPool.size(); j++) 
		{
			//std::cout<<attemptIdPool[j].substr(0, 35)<<"\n"<<(*it)->getAttemptid().substr(0, 35)<<std::endl;
			if(attemptIdPool[j].substr(0, 35) == (*it)->getAttemptid().substr(0, 35))
			//if(attemptIdPool[j] == (*it)->getAttemptid())
			{
				NO = j;
			}		
		}
		if(NO == -1)
		{
			//C_DBG_ERR("NO. DOES NOT EXIST\n");
		}
			
		if((*it)->typeTitle == "MAP_ATTEMPT_KILLED" || (**it).typeTitle == "REDUCE_ATTEMPT_KILLED" )
		{
			//C_DBG_ERR("killed !!");
			attemptMatch[NO]->setKilledAttempt( (**it) );
		}
		if((*it)->typeTitle == "MAP_ATTEMPT_FINISHED" || (**it).typeTitle == "REDUCE_ATTEMPT_FINISHED" )
		{
			//C_DBG_ERR("finished !!\n");
			attemptMatch[NO]->setFinishAttempt( (**it) );
		}
		if((*it)->typeTitle == "MAP_ATTEMPT_STARTED" || (**it).typeTitle == "REDUCE_ATTEMPT_STARTED" )
		{
			if( attemptMatch[NO]->startAttempt != NULL)
			{
				attemptMatch[NO]->setBackUpStartAttempt( (**it) );
			}		
			else
			{
				attemptMatch[NO]->setStartAttempt( (**it) );
			} 
		}
	}
	delete []monkeyTable;
}

int TasksStruct::getMatchesCount()
{
	return attemptMatch.size();	
}

TasksStruct::~TasksStruct()
{
	if(attemptName)
		delete []attemptName;
	
	for(int i = 0; i < attemptMatch.size(); i++)
		delete attemptMatch[i];
}

AttemptMatch::AttemptMatch()
{
	TimeChangeOn = 1;
	//std::cout << "Construction of AttemptMatch" << std::endl;
	startAttempt = NULL;
	backUpStartAttempt = NULL;
	finishAttempt = NULL;
	killedAttempt = NULL;
}

int AttemptMatch::setStartAttempt(Task& _task)
{
	startAttempt = new Task(_task);
}

int AttemptMatch::setBackUpStartAttempt(Task& _task)
{
	backUpStartAttempt = new Task(_task);
}

int AttemptMatch::setFinishAttempt(Task& _task)
{
	finishAttempt = new Task(_task);
}

int AttemptMatch::setKilledAttempt(Task& _task)
{
	killedAttempt = new Task(_task);
}

void AttemptMatch::Display()
{
	if(startAttempt != NULL)
	{
		std::cout << "startAttempt: "; 
		std::cout << startAttempt->getAttemptid();
		std::cout <<std::endl;	
	}
	
	if(backUpStartAttempt != NULL)
	{
		std::cout << "backUpStartAttempt: ";
		std::cout << backUpStartAttempt->getAttemptid();
		std::cout <<std::endl;
	}
	
	if(killedAttempt != NULL)
	{
		std::cout << "killedAttempt: ";
		std::cout << killedAttempt->getAttemptid();
		std::cout <<std::endl;
	}
	
	if(finishAttempt != NULL)
	{
		std::cout << "finishAttempt: ";
		std::cout << finishAttempt->getAttemptid();
		std::cout <<std::endl;
	}
	
	
 	//if(this->killedAttempt->getAttemptid() != "")
 	//	std::cout << "killedAttempt: " << killedAttempt->getAttemptid() << std::endl;
		 	
	if(TimeChangeOn == 1)
	{
		if(startAttempt && finishAttempt)
		{
			std::cout << "StartTime: ";
			SYSTEM_TIME t1 = TimeChange(startAttempt->getStartTime(), 8);
			std::cout << "\nFinishTime: ";
			SYSTEM_TIME t2 = TimeChange(finishAttempt->getFinishTime(), 8);
			
			std::cout << "\n";
			if(t2.wDay - t1.wDay != 0)
				std::cout << "TimeSpent(s): " << (t2.wHour-t1.wHour) * 60 * 60 + (t2.wMinute-t1.wMinute) * 60 + (t2.wSecond-t1.wSecond) + 86400 << std::endl;
			std::cout << "TimeSpent(s): " << (t2.wHour-t1.wHour) * 60 * 60 + (t2.wMinute-t1.wMinute) * 60 + (t2.wSecond-t1.wSecond) << std::endl;
		}
	}
	else
	{
		if(startAttempt && finishAttempt)
		{
			std::cout << "StartTime: ";
			std::cout <<  startAttempt->getStartTime();
			std::cout << "\nFinishTime: ";
			std::cout <<  finishAttempt->getFinishTime();
			std::cout << "\n";
			std::cout << "TimeSpent(s): " << finishAttempt->getFinishTime() - startAttempt->getStartTime() <<std::endl;
		}
	}
}

AttemptMatch::~AttemptMatch()
{
	delete []startAttempt;
	delete []finishAttempt;
	delete []killedAttempt;
}

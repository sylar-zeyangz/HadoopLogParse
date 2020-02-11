#ifndef ___TasksStruct_H___
#define ___TasksStruct_H___

#include "Task.h" 
#include <vector>

class AttemptMatch: public Task
{
	private:
		
	public:
		int TimeChangeOn;
	
		Task* startAttempt;
		Task* backUpStartAttempt;
		Task* finishAttempt;
		Task* killedAttempt;
	
		int setStartAttempt(Task& _task);
		int setBackUpStartAttempt(Task& _task);
 		int setFinishAttempt( Task& _task );
 		int setKilledAttempt( Task& _task );
 		
 		void Display(); 
 		
 		AttemptMatch();
 		virtual ~AttemptMatch();
};


class TasksStruct
{
	private:
		std::string* attemptName;
		//int matchesCount;
		
	public:
	//LogsMatch();
	//AttemptMatch* attemptMatch;
	std::vector<AttemptMatch*> attemptMatch;
	int getMatchesCount();
	
	TasksStruct( std::list<Task*> _all_task, int _numOfAttempt );
	~TasksStruct();
};



#endif //___TasksStruct_H___

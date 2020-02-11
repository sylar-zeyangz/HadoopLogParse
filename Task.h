#ifndef ___Task_H___
#define ___Task_H___

#define JOB_SUBMITTED 			0
#define JOB_INITED 				1
#define JOB_INFO_CHANGED 		2
#define TASK_STARTED 			3
#define MAP_ATTEMPT_STARTED 	4
#define MAP_ATTEMPT_FINISHED 	5
#define REDUCE_ATTEMPT_STARTED 	6
#define REDUCE_ATTEMPT_FINISHED 7
#define MAP_ATTEMPT_KILLED 		8
#define TASK_FINISHED			9
#define JOB_FINISHED 			10

#include "MasterFileIn.h"
#include <windef.h> 
#include <time.h> 
#include "SystemTime.h"

//REDUCE_ATTEMPT_KILLED not be concerned yet.

class Task
{
	private:
	//JOB_SUBMITTED
	//string jobid, string jobName, string userName, long submitTime, string jobConfPath, string workflowId, string workflowName, string workflowNodeName, string workflowAdjacencies ...

	//JOB_INITED
	//string jobid, long launchTime, int totalMaps, int totalReduces, string jobState, bool uberized

	//JOB_INFO_CHANGED
	//string jobid, submitTime, launchTime

	//TASK_STARTED
	//string taskid, string taskType, long startTime, string splitLocation

	//MAP_ATTEMPT_STARTED
	//string taskid, string taskType, string attemptId, long startTime, string trackerName, int httpPort,
	//int shufflePort, string containerId, string locality, string avataar

	//MAP_ATTEMPT_FINISHED
	//string taskid, string taskType, string attemptId, string taskStatus, long mapFinishTime, long finishTime, string hostname, int port, ...

	//TASK_FINISHED
	//string taskid, string taskType, long finishtTime, string status

	//REDUCE_ATTEMPT_STARTED
	//string taskid, string taskType, string attemptId, long startTime, string trackerName, int httpPort,
	//int shufflePort, string containerId, string locality, string avataar

	//MAP_ATTEMPT_KILLED
	//string taskid, string taskType, string attemptId, long finishTime, string hostname, int port, ...

	//REDUCE_ATTEMPT_FINISHED
	//string taskid, string taskType, string attemptId, string taskStatus, long shuffleFinishTime, long sortFinishTime, long finishTime,string hostname, int port, ...

	//JOB_FINISHED
	//string jobid, long finishTime, int finishedMaps, int finishedReduces, int failedMaps, int failedReduces..

	bool uberized;

	std::string jobid;
 	std::string jobName;
 	std::string userName;
 	std::string jobStatus;
 	std::string jobConfPath;
 	std::string workflowId;
 	std::string workflowName;
	std::string workflowNodeName;
	std::string workflowAdjacencies;
	std::string taskid;
	std::string taskType;
	std::string splitLocations;
	std::string attemptId;
	std::string trackerName;
	std::string containerId;
	std::string locality;
	std::string avataar;
	std::string hostname;
	std::string taskStatus;
	std::string status;

	long long submitTime;
	long long launchTime;
	long long shuffleFinishTime;
	long long sortFinishTime;
	long long mapFinishTime;
	long long finishTime;
	long long startTime;
	
	int httpPort;
	int shufflePort;	
	int port;
	int finishedMaps;
	int finishedReduces;
	int failedMaps;
	int failedReduces;
	int totalMaps;
	int totalReduces;
	
	public:
	int TimeChangeOn;
	
	std::string typeTitle;
	
	long long getStartTime();
	long long getFinishTime();
	std::string getAttemptid();
	std::string getTrackerName();
	std::string getContainerid();
	std::string getAvaatar();
	int getTypeNum();
	
	int getTimeChangeOn();
	
	int IsLeap(unsigned short _year);						
	SYSTEM_TIME TimeChange( long long time, long timezone );		//optional function, decided by users
	
	Task( Json::Value& _value );
	Task( const Task& _task );								//copy construction
	Task();
	virtual ~Task(); 
		
};

#endif //___Task_H___

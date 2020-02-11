#include "Task.h"
#include <sstream>
//#include <windows.h> 

Task::Task( Json::Value& _value )
{
	taskid = "";
	TimeChangeOn = 1;
	typeTitle = _value["type"].asString();	
	
	//std::string _type;
	//_type = _value["type"].asString();

	switch ( getTypeNum() )
	{		
		case JOB_SUBMITTED:
		{
			std::cout << ">> " << typeTitle << " <<" << std::endl; 
			
			jobid = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.JobSubmitted"]["jobid"].asString();
			std::cout <<  "jobid:" << jobid << std::endl;
			jobName = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.JobSubmitted"]["jobName"].asString();
			std::cout <<  "jobName:" << jobName << std::endl;
			userName = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.JobSubmitted"]["userName"].asString();
			std::cout <<  "userName:" << userName << std::endl; 
			
			//long long type data -- submitTime
			std::stringstream t_stream;
			t_stream << _value["event"]["org.apache.hadoop.mapreduce.jobhistory.JobSubmitted"].get("submitTime", _value);//time stamp
			t_stream >> submitTime;
			std::cout <<  "submitTime:";
			if(TimeChangeOn == 1)
				TimeChange( submitTime, 8 );
			std::cout << std::endl; 
			
			jobConfPath = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.JobSubmitted"]["jobConfPath"].asString();
		 	std::cout <<  "jobConfPath:" << jobConfPath << std::endl;
			workflowId = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.JobSubmitted"]["workflowId"].asString();
			std::cout <<  "workflowId:" << workflowId << std::endl;
			workflowName = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.JobSubmitted"]["workflowName"].asString();
			std::cout <<  "workflowName:\n" << workflowName << std::endl;
			//workflowNodeName = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.JobSubmitted"]["workflowNodeName"].asString();
			//std::cout <<  "workflowNodeName:" << workflowNodeName << std::endl;
			//workflowAdjacencies = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.JobSubmitted"]["workflowName"].asString();
			//std::cout <<  "workflowAdjacencies:" << workflowAdjacencies << std::endl;	 
			
			std::cout << "---------------------------------------------------------------------" << std::endl;  
		}break;
		case JOB_INITED:
		{
			std::cout << ">> " << typeTitle << " <<" << std::endl;
			
			jobid = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.JobInited"]["jobid"].asString();
			std::cout << "jobid:" << jobid << std::endl;
			
			//long long type data -- launchTime
			std::stringstream t_stream;
			t_stream << _value["event"]["org.apache.hadoop.mapreduce.jobhistory.JobInited"].get("launchTime", _value);//time stamp
			std::cout <<  "launchTime:";
		 	t_stream >> launchTime;
		 	if(TimeChangeOn == 1)
				TimeChange( launchTime, 8 );
			std::cout << std::endl; 
			
			totalMaps = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.JobInited"]["totalMaps"].asInt();
			std::cout << "totalMaps:" << totalMaps << std::endl;
			totalReduces = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.JobInited"]["totalReduces"].asInt();
			std::cout << "totalReduces:" << totalReduces << std::endl;
			jobStatus = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.JobInited"]["jobStatus"].asString();
			std::cout << "jobStatus:" << jobStatus << std::endl;
			uberized = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.JobInited"]["uberized"].asBool();
			std::cout << "uberized:" << uberized << std::endl;
			  		  
			std::cout << "---------------------------------------------------------------------" << std::endl; 		 
		}break;
		case JOB_INFO_CHANGED: 
		{
			std::cout << ">> " << typeTitle << " <<" << std::endl;
			
			jobid = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.JobInfoChange"]["jobid"].asString();
		 	std::cout << "jobid:" << jobid << std::endl;
		 	
		 	//long long type data -- submitTime, launchTime
		 	std::stringstream t_stream, tt_stream;
			t_stream << _value["event"]["org.apache.hadoop.mapreduce.jobhistory.JobInfoChange"].get("submitTime", _value);
			std::cout <<  "submitTime:";
		 	t_stream >> submitTime;
		 	if(TimeChangeOn == 1)
				TimeChange( submitTime, 8 );
			std::cout << std::endl; 
			tt_stream << _value["event"]["org.apache.hadoop.mapreduce.jobhistory.JobInfoChange"].get("launchTime", _value);
			std::cout <<  "launchTime:";
		 	tt_stream >> launchTime;
		 	if(TimeChangeOn == 1)
				TimeChange( launchTime, 8 );
			std::cout << std::endl; 
			
			std::cout << "---------------------------------------------------------------------" << std::endl; 
		}break;
		case TASK_STARTED: 
		{
			std::cout << ">> " << typeTitle << " <<" << std::endl;
			
			taskid = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskStarted"]["taskid"].asString();
		 	std::cout << "taskid:" << taskid << std::endl;
 			taskType = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskStarted"]["taskType"].asString();
		 	std::cout << "taskType:" << taskType << std::endl;

			//long long type data -- startTime
		 	std::stringstream t_stream;
			t_stream << _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskStarted"].get("startTime", _value);
			std::cout <<  "startTime:";
		 	t_stream >> startTime;
		 	if(TimeChangeOn == 1)
				TimeChange( startTime, 8 );
			std::cout << std::endl; 

			splitLocations = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskStarted"]["splitLocations"].asString();
		 	std::cout << "splitLocations:" << splitLocations << std::endl;
			
			std::cout << "---------------------------------------------------------------------" << std::endl; 
		}break;
		case MAP_ATTEMPT_STARTED: 
		{
			std::cout << ">> " << typeTitle << " <<" << std::endl; 
			
			taskid = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskAttemptStarted"]["taskid"].asString();
		 	std::cout << "taskid:" << taskid << std::endl;
 			taskType = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskAttemptStarted"]["taskType"].asString();
		 	std::cout << "taskType:" << taskType << std::endl;
			attemptId = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskAttemptStarted"]["attemptId"].asString();
		 	std::cout << "attemptId:" << attemptId << std::endl;

			//long long type data -- startTime
		 	std::stringstream t_stream;
			t_stream << _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskAttemptStarted"].get("startTime", _value);
			std::cout <<  "startTime:";
		 	t_stream >> startTime;
		 	if(TimeChangeOn == 1)
				TimeChange( startTime, 8 );
			std::cout << std::endl; 

			trackerName = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskAttemptStarted"]["trackerName"].asString();
		 	std::cout << "trackerName:" << trackerName << std::endl;
			httpPort = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskAttemptStarted"]["httpPort"].asInt();
		 	std::cout << "httpPort:" << httpPort << std::endl;
			shufflePort = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskAttemptStarted"]["shufflePort"].asInt();
		 	std::cout << "shufflePort:" << shufflePort << std::endl;
			containerId = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskAttemptStarted"]["containerId"].asString();
		 	std::cout << "containerId:" << containerId << std::endl;
			locality = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskAttemptStarted"]["locality"].asString();
		 	std::cout << "locality:" << locality << std::endl;
			avataar = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskAttemptStarted"]["avataar"].asString();
		 	std::cout << "avataar:" << avataar << std::endl;
			
			std::cout << "---------------------------------------------------------------------" << std::endl; 
		}break;
		case MAP_ATTEMPT_FINISHED: 
		{
			std::cout << ">> " << typeTitle << " <<" << std::endl;
			
			taskid = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.MapAttemptFinished"]["taskid"].asString();
		 	std::cout << "taskid:" << taskid << std::endl;
 			taskType = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.MapAttemptFinished"]["taskType"].asString();
		 	std::cout << "taskType:" << taskType << std::endl;
			attemptId = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.MapAttemptFinished"]["attemptId"].asString();
		 	std::cout << "attemptId:" << attemptId << std::endl;
			taskStatus = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.MapAttemptFinished"]["taskStatus"].asString();
		 	std::cout << "taskStatus:" << taskStatus << std::endl;

			//long long type data -- mapFinishTime, finishTime
		 	std::stringstream t_stream, tt_stream;
			t_stream << _value["event"]["org.apache.hadoop.mapreduce.jobhistory.MapAttemptFinished"].get("mapFinishTime", _value);
			std::cout <<  "mapFinishTime:";
		 	t_stream >> mapFinishTime;
		 	if(TimeChangeOn == 1)
				TimeChange( mapFinishTime, 8 );
			std::cout << std::endl; 
			tt_stream << _value["event"]["org.apache.hadoop.mapreduce.jobhistory.MapAttemptFinished"].get("finishTime", _value);
			std::cout <<  "finishTime:";
		 	tt_stream >> finishTime;
		 	if(TimeChangeOn == 1)
				TimeChange( finishTime, 8 );
			std::cout << std::endl; 

			hostname = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.MapAttemptFinished"]["hostname"].asString();
		 	std::cout << "hostname:" << hostname << std::endl;
			port = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.MapAttemptFinished"]["port"].asInt();
		 	std::cout << "port:" << port << std::endl;

			std::cout << "---------------------------------------------------------------------" << std::endl; 
		}break;
		case REDUCE_ATTEMPT_STARTED: 
		{
			std::cout << ">> " << typeTitle << " <<" << std::endl; 
			
			taskid = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskAttemptStarted"]["taskid"].asString();
		 	std::cout << "taskid:" << taskid << std::endl;
 			taskType = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskAttemptStarted"]["taskType"].asString();
		 	std::cout << "taskType:" << taskType << std::endl;
			attemptId = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskAttemptStarted"]["attemptId"].asString();
		 	std::cout << "attemptId:" << attemptId << std::endl;

			//long long type data -- startTime
		 	std::stringstream t_stream;
			t_stream << _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskAttemptStarted"].get("startTime", _value);
			std::cout <<  "startTime:";
		 	t_stream >> startTime;
		 	if(TimeChangeOn == 1)
				TimeChange( startTime, 8 );
			std::cout << std::endl; 

			trackerName = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskAttemptStarted"]["trackerName"].asString();
		 	std::cout << "trackerName:" << trackerName << std::endl;
			httpPort = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskAttemptStarted"]["httpPort"].asInt();
		 	std::cout << "httpPort:" << httpPort << std::endl;
			shufflePort = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskAttemptStarted"]["shufflePort"].asInt();
		 	std::cout << "shufflePort:" << shufflePort << std::endl;
			containerId = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskAttemptStarted"]["containerId"].asString();
		 	std::cout << "containerId:" << containerId << std::endl;
			locality = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskAttemptStarted"]["locality"].asString();
		 	std::cout << "locality:" << locality << std::endl;
			avataar = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskAttemptStarted"]["avataar"].asString();
		 	std::cout << "avataar:" << avataar << std::endl;
			
			std::cout << "---------------------------------------------------------------------" << std::endl; 
		}break;
		case REDUCE_ATTEMPT_FINISHED: 
		{
			std::cout << ">> " << typeTitle << " <<" << std::endl; 
			
			taskid = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.ReduceAttemptFinished"]["taskid"].asString();
		 	std::cout << "taskid:" << taskid << std::endl;
 			taskType = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.ReduceAttemptFinished"]["taskType"].asString();
		 	std::cout << "taskType:" << taskType << std::endl;
			attemptId = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.ReduceAttemptFinished"]["attemptId"].asString();
		 	std::cout << "attemptId:" << attemptId << std::endl;
			taskStatus = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.ReduceAttemptFinished"]["taskStatus"].asString();
		 	std::cout << "taskStatus:" << taskStatus << std::endl;

			//long long type data -- shuffleFinishTime, sortFinishTime, finishTime
		 	std::stringstream t_stream, tt_stream, ttt_stream;
			t_stream << _value["event"]["org.apache.hadoop.mapreduce.jobhistory.ReduceAttemptFinished"].get("shuffleFinishTime", _value);
			std::cout <<  "shuffleFinishTime:";
		 	t_stream >> shuffleFinishTime;
		 	if(TimeChangeOn == 1)
				TimeChange( shuffleFinishTime, 8 );
			std::cout << std::endl; 
			tt_stream << _value["event"]["org.apache.hadoop.mapreduce.jobhistory.ReduceAttemptFinished"].get("sortFinishTime", _value);
			std::cout <<  "sortFinishTime:";
		 	tt_stream >> sortFinishTime;
		 	if(TimeChangeOn == 1)
				TimeChange( sortFinishTime, 8 );
			std::cout << std::endl; 
			ttt_stream << _value["event"]["org.apache.hadoop.mapreduce.jobhistory.ReduceAttemptFinished"].get("finishTime", _value);
			std::cout <<  "finishTime:";
		 	ttt_stream >> finishTime;
		 	if(TimeChangeOn == 1)
				TimeChange( finishTime, 8 );
			std::cout << std::endl; 

			hostname = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.ReduceAttemptFinished"]["hostname"].asString();
		 	std::cout << "hostname:" << hostname << std::endl;
			port = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.ReduceAttemptFinished"]["port"].asInt();
		 	std::cout << "port:" << port << std::endl;
			
			std::cout << "---------------------------------------------------------------------" << std::endl; 
		}break;
		case MAP_ATTEMPT_KILLED:  
		{
			std::cout << ">> " << typeTitle << " <<" << std::endl;
			
			taskid = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskAttemptUnsuccessfulCompletion"]["taskid"].asString();
		 	std::cout << "taskid:" << taskid << std::endl;
 			taskType = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskAttemptUnsuccessfulCompletion"]["taskType"].asString();
		 	std::cout << "taskType:" << taskType << std::endl;
			attemptId = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskAttemptUnsuccessfulCompletion"]["attemptId"].asString();
		 	std::cout << "attemptId:" << attemptId << std::endl;
		 	
		 	//long long type data -- finishTime
		 	std::stringstream t_stream;
			t_stream << _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskAttemptUnsuccessfulCompletion"].get("finishTime", _value);
			std::cout <<  "finishTime:";
		 	t_stream >> finishTime;
		 	if(TimeChangeOn == 1)
				TimeChange( finishTime, 8 );
			std::cout << std::endl; 
			
			hostname = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskAttemptUnsuccessfulCompletion"]["hostname"].asString();
		 	std::cout << "hostname:" << hostname << std::endl;
		 	port = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskAttemptUnsuccessfulCompletion"]["port"].asInt();
		 	std::cout << "port:" << port << std::endl;
			
			std::cout << "---------------------------------------------------------------------" << std::endl;  
		}break; 
		case TASK_FINISHED: 
		{
			std::cout << ">> " << typeTitle << " <<" << std::endl;
			
			taskid = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskFinished"]["taskid"].asString();
		 	std::cout << "taskid:" << taskid << std::endl;
 			taskType = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskFinished"]["taskType"].asString();
		 	std::cout << "taskType:" << taskType << std::endl;
		 	
		 	//long long type data -- finishTime
		 	std::stringstream t_stream;
			t_stream << _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskFinished"].get("finishTime", _value);
			std::cout <<  "finishTime:";
		 	t_stream >> finishTime;
		 	if(TimeChangeOn == 1)
				TimeChange( finishTime, 8 );
			std::cout << std::endl; 
		 	
	 		status = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.TaskFinished"]["status"].asString();
		 	std::cout << "status:" << status << std::endl;
			
			std::cout << "---------------------------------------------------------------------" << std::endl; 
		}break;
		case JOB_FINISHED: 
		{
			std::cout << ">> " << typeTitle << " <<" << std::endl; 
			
			jobid = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.JobFinished"]["jobid"].asString();
			std::cout <<  "jobid:" << jobid << std::endl;
			
			//long long type data -- finishTime
		 	std::stringstream t_stream;
			t_stream << _value["event"]["org.apache.hadoop.mapreduce.jobhistory.JobFinished"].get("finishTime", _value);
			std::cout <<  "finishTime:";
		 	t_stream >> finishTime;
		 	if(TimeChangeOn == 1)
				TimeChange( finishTime, 8 );
			std::cout << std::endl; 
			
			finishedMaps = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.JobFinished"]["finishedMaps"].asInt();
			std::cout <<  "finishedMaps:" << finishedMaps << std::endl;
			finishedReduces = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.JobFinished"]["finishedReduces"].asInt();
			std::cout <<  "finishedReduces:" << finishedReduces << std::endl;
			failedMaps = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.JobFinished"]["failedMaps"].asInt();
			std::cout <<  "failedMaps:" << failedMaps << std::endl;
			failedReduces = _value["event"]["org.apache.hadoop.mapreduce.jobhistory.JobFinished"]["failedReduces"].asInt();
			std::cout <<  "failedReduces:" << failedReduces << std::endl;
			
			std::cout << "---------------------------------------------------------------------" << std::endl; 
		}break;
		default:
		{
			//std::cout << "UNRECONGNIZED TYPE:"  << typeTitle << std::endl; 
		} 
	}
}

Task::Task( const Task& _task )
{
	typeTitle = _task.typeTitle;
	jobid = _task.jobid;
	uberized = _task.uberized;

	jobName = _task.jobName;
	userName = _task.userName;
	jobStatus = _task.jobStatus;
	jobConfPath = _task.jobConfPath;
	workflowId = _task.workflowId;
	workflowName = _task.workflowName;
	workflowNodeName = _task.workflowNodeName;
	workflowAdjacencies = _task.workflowAdjacencies;
	taskid = _task.taskid;
	taskType = _task.taskType;
	splitLocations = _task.splitLocations;
	attemptId = _task.attemptId;
	trackerName = _task.trackerName;
	containerId = _task.containerId;
	locality = _task.locality;
	avataar = _task.avataar;
	hostname = _task.hostname;
	taskStatus = _task.taskStatus;
	status = _task.status;

	submitTime = _task.submitTime;
	launchTime = _task.launchTime;
	shuffleFinishTime = _task.shuffleFinishTime;
	sortFinishTime = _task.sortFinishTime;
	mapFinishTime = _task.mapFinishTime;
	finishTime = _task.finishTime;
	startTime = _task.startTime;
	
	httpPort = _task.httpPort;
	shufflePort = _task.shufflePort;	
	port = _task.port;
	finishedMaps = _task.finishedMaps;
	finishedReduces = _task.finishedReduces;
	failedMaps = _task.failedMaps;
	failedReduces = _task.failedReduces;
	totalMaps = _task.totalMaps;
	totalReduces = _task.totalReduces;
}

int Task::getTypeNum()
{
	if( typeTitle == "JOB_SUBMITTED" ) return 0;
	else if( typeTitle == "JOB_INITED" ) return 1;
	else if( typeTitle == "JOB_INFO_CHANGED" ) return 2;
	else if( typeTitle == "TASK_STARTED" ) return 3;
	else if( typeTitle == "MAP_ATTEMPT_STARTED" ) return 4;
	else if( typeTitle == "MAP_ATTEMPT_FINISHED" ) return 5;
	else if( typeTitle == "REDUCE_ATTEMPT_STARTED" ) return 6;
	else if( typeTitle == "REDUCE_ATTEMPT_FINISHED" ) return 7;
	else if( typeTitle == "MAP_ATTEMPT_KILLED" ) return 8; 
	else if( typeTitle == "TASK_FINISHED" ) return 9;
	else if( typeTitle == "JOB_FINISHED" ) return 10;
	else 
		return -1; 
}
#include<time.h>
int Task::IsLeap(unsigned short _year)
{ 
	return ((_year % 4 == 0) && (_year % 100 != 0) || (_year % 400 == 0));  
}

SYSTEM_TIME Task::TimeChange( long long time, long timezone )		//timezone can be changed by users' need
{															//China is +8
	const int monthLengths[2][13] = { 						 
        {0,31,59,90,120,151,181,212,243,273,304,334,365 },  
        {0,31,60,91,121,152,182,213,244,274,305,335,366 } 
    };  
    const int yearLengths[2] = {365,366};
    int year(0),month(0),minMonth(0),maxMonth(0),days(0),clock(0),isLeap(0),day(0),hour(0),minute(0),second(0);  
    time /= 1000;  
    time += timezone * 60 * 60;  
    days = time / 86400; 
    clock = time % 86400;  
  
    if(clock < 0)  
    {  
        clock += 86400;  
        days -= 1;  
    }  
  
    if(days >= 0)  
    {  
        year = days / 366;  
        days -= year * 365 + (year + 1)/4 - (year + 69)/100 + (year + 369) / 400;  
  
        for (year = year + 1970; ; year++)  
        {  
            isLeap = IsLeap(year);  
            if(days < yearLengths[isLeap])  
            {  
                break;  
            }  
            days -= yearLengths[isLeap];  
        }  
    }  
    else  
    {  
        year = days / 366;  
        days -= year * 365 + (year - 2)/4 - (year - 30) / 100 + (year - 30) / 400;  
        for(year = year + 1970 - 1; ; year--)  
        {  
            isLeap = false;  
            days += yearLengths[isLeap];  
            if (days >= 0)  
            {  
                break;  
            }  
        }  
    }  
  
    minMonth = 0;
    maxMonth = 12;
    for (month = 5 ;month < 12 && month > 0; month=(minMonth+maxMonth) / 2)  
    {  
        if (days<monthLengths[isLeap][month])  
        {  
            maxMonth = month;  
        }  
        else if (days >= monthLengths[isLeap][month + 1])  
        {  
            minMonth = month;  
        }  
        else  
        {  
            break;  
        }  
    }  
    days -= monthLengths[isLeap][month];  
    month++;  
    day = days + 1;  
  
    hour = clock / 3600;  
    clock = clock % 3600;  
    minute = clock / 60;  
    second = clock % 60;  
    
	SYSTEM_TIME st = {};
	st.wYear = year;
	st.wMonth = month;
	st.wDay = day;
	st.wHour = hour;
	st.wMinute = minute;
	st.wSecond = second;
	
    std::string rtn;
    std::cout <<st.wYear<<"-"<<st.wMonth<<"-"<<	st.wDay<<" "<<st.wHour<<":"<<st.wMinute<<":"<<st.wSecond;

    return st;
}

long long Task::getStartTime()
{
	return startTime;
}

long long Task::getFinishTime()
{
	return finishTime;
}

std::string Task::getAttemptid()
{
	return attemptId;
}

std::string Task::getTrackerName()
{
	return trackerName;
}

std::string Task::getContainerid()
{
	return containerId;
}

std::string Task::getAvaatar()
{
	return avataar;
}

int Task::getTimeChangeOn()
{
	return TimeChangeOn;	
}

Task::Task()
{
	
} 

Task::~Task()
{
	
}

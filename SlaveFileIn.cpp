#include "SlaveFileIn.h"

SlaveFileIn::SlaveFileIn()
{
	filename = NULL;
	containerId = NULL;
	trackerName = NULL;
} 

std::string SlaveFileIn::LocateSlaveFile( std::string _trackerName, std::string _containerId )
{
	trackerName = _trackerName.c_str();
	containerId = _containerId.c_str();
	
	std::string appId = new char();
	appId = _containerId.substr(10,18);
	//std::cout << "------\n" << appId << "\n";
	
	std::string address = "";
	address = address.append("LogData/");
	//std::cout << "-----" << appId << "------";
	//std::cout << "\n" << address << "\n";
	address = address.append(trackerName);
	//std::cout << "-----" << appId << "------";
	//std::cout << "\n" << address << "\n";
	address = address.append("/userlogs");
	//std::cout << "-----" << appId << "------";
	//std::cout << "\n" << address << "\n";
	address = address.append("/application_");
	//std::cout << "-----" << appId << "------";
	//std::cout << "\n" << address << "\n";
	address = address.append(appId);
	//std::cout << "-----" << appId << "------";
	//std::cout << "\n" << address << "\n";
	address = address.append("/");
	//std::cout << "\n" << address << "\n";
	address = address.append(containerId);
	//std::cout << "\n" << address << "\n";
	address = address.append("/syslog").c_str();
	//std::cout << address << "\n";
	
	return address;
}

/*
namespace
{
	struct destrcution
	{
		void operator()(SlaveWorker* _s)
		{
			if(_s) 
				delete _s;
		}
	}des;
}*/

int SlaveFileIn::Clear()
{
	if(filename)
		delete []filename;
	if(containerId)
		delete []containerId;
	if(trackerName)
		delete []trackerName;
	
	filename = NULL;
	containerId = NULL;
	trackerName = NULL;
	
	for(int i = 0; i < slaveWorkerPool.size(); i++)
	{
		if(slaveWorkerPool[i])
			delete slaveWorkerPool[i];
	}
	slaveWorkerPool.clear();
}

SlaveFileIn::~SlaveFileIn()
{	
	Clear();
}


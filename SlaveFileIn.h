#ifndef ___SlaveFileIn_H___
#define ___SlaveFileIn_H___

#include "SlaveWorker.h"
#include <vector>

class SlaveFileIn
{
	private:
		const char* filename;
		const char* containerId;
		const char* trackerName;
	
	protected:
		std::vector<SlaveWorker*> slaveWorkerPool;
	
	public:
		std::string LocateSlaveFile( std::string _trackerName, std::string _containerId );
		int GatherOptree();
		
		int Clear();
		
		SlaveFileIn();
		virtual ~SlaveFileIn(); 
};

#endif //___SlaveFileIn_H___

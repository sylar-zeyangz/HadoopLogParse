#ifndef ___FileIn_H___
#define ___FileIn_H___

#include <string>
#include <fstream>
#include <list>
#include <set>
#include "include/json.h"
#include "Task.h"
#include "C_Debug.h"

class MasterFileIn
{
	protected:
		std::list<Json::Value*> value_pool;
		std::set<std::string> ValueTypeSet;
		
		const char* masterFileLoc;
		
	public:
		int ReadJsonFromFile( const char* _filename );
		int LocateFile();
		
		int Clear();
							
		MasterFileIn();
		virtual ~MasterFileIn();
	
};

#endif //___FileIn_H___

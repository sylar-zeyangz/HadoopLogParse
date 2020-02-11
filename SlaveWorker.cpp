#include "SlaveWorker.h"
#include "C_Debug.h"

SlaveWorker::SlaveWorker( std::string _address )
{
	treeSrc = NULL;
	
	int pos1 = 0;
	int pos2 = 0;
	int pos3 = 0;
	int pos4 = 0;
	is.open( _address.c_str() );

    std::string* FileBuffer = new std::string;
    while( !is.eof() )
    {
    	
    	FileBuffer->clear();
    	getline(is, *FileBuffer);
    	
    	//std::cout << *FileBuffer << "\n";
    	if( *FileBuffer == "\r" )
    		continue;
	
		pos1 = FileBuffer->find('[');
		pos2 = FileBuffer->find(']');
		pos3 = FileBuffer->find(": ", pos2);
		pos4 = FileBuffer->find(": ", pos3 + 1);
		/*
		if( FileBuffer->find(": ", pos3) != std::string::npos )
		{
			std::cout<<"pos4: "<<pos4<<"\n";
			pos4 = FileBuffer->find(": ", pos3);
		}*/
	   	
   		if(pos1 == std::string::npos)
   			continue;
		
	    if( (*FileBuffer)[pos3 + 2] == '\0' )
		{
			std::string optree = "";
			do
			{
				//std::cout << *FileBuffer << "\n";
				FileBuffer->clear();
				getline(is, *FileBuffer);
				if((*FileBuffer)[0] != '2')
					optree.append(*FileBuffer + "\n");
			}while((*FileBuffer)[0] != '2');
			
			treeSrc = new SlaveDataStruct;
			treeSrc->setTime(FileBuffer->substr(0, 23));
			treeSrc->setLevel(FileBuffer->substr(24, pos1 - 24 - 1));
			treeSrc->setClass(FileBuffer->substr(pos1, 6));
			treeSrc->setInfo1(FileBuffer->substr(pos2 + 2, pos3 - pos2 - 1 - 1)); 
   			treeSrc->setInfo2( optree );	
		   	treeSrc->setInfo3( "" );			
			//std::cout << treeSrc->getInfo2() << "\n";
   		}
	   	//else if( (*FileBuffer)[pos3 + 2] == '\0' )
	   	else
	   	{
	   		SlaveDataStruct* st = new SlaveDataStruct;
	   		
		   	st->setTime(FileBuffer->substr(0, 23));
		   	//std::cout << (*dataStructPool.begin())->time << "\n";
			
	   		st->setLevel(FileBuffer->substr(24, pos1 - 24 - 1));
		   	//std::cout << (*dataStructPool.begin())->level << "\n";
		   	
		   	st->setClass(FileBuffer->substr(pos1, 6));
		    //std::cout << (*dataStructPool.begin())->relateclass << "\n";
	   		
		   	st->setInfo1(FileBuffer->substr(pos2 + 2, pos3 - pos2 - 1 - 1));
		   	//std::cout << "info1: " << (*dataStructPool.begin())->info1 << "\n";
		   	
		   	st->setInfo2(FileBuffer->substr(pos3 + 2, *FileBuffer->end() - pos2 ));
		   	//std::cout << "info2: " << (*dataStructPool.begin())->info2 << "\n";
	   		
	   		if( pos4 != std::string::npos )
	   		{
	   		
		   		st->setInfo3( FileBuffer->substr( pos4 + 2, *FileBuffer->end() - pos2 ) );
	   			//std::cout << "info3: " << (*dataStructPool.begin())->info3 << "\n";
		   	}	
		   	dataStructPool.push_back( st );
   		}
    }
    
    delete FileBuffer;
	is.close();		
}

int SlaveWorker::getOperatorRows(int _id)
{
	//fprintf(stderr, "id:%d\n", _id);
	int dstId = 0;
	int rows = 0;
	std::list<SlaveDataStruct*>::iterator it;
	for(it = dataStructPool.begin(); it != dataStructPool.end(); ++it)
	{	
		char* tmp = new char[10];
		itoa(_id, tmp, 10);
		sscanf((**it).info2.c_str(), "%d forwarded %d rows", &dstId, &rows);
		if((**it).info2.find("forwarded") != std::string::npos && dstId == _id)
		{
			//C_DBG_ERR("!!!FIND!!!\n");
			break;
		}
		delete[] tmp;
	}
	return rows;
}

std::string SlaveWorker::getOperatorStartTime(std::string _state, int _id)
{
	std::string retTime;
	std::string backUpSearch = "initialized"; 
	std::list<SlaveDataStruct*>::iterator it;
	
	char tmp[10];
	itoa(_id, tmp, 10);
	std::string st = tmp;
	
	for(it = dataStructPool.begin(); it != dataStructPool.end(); ++it)
	{
		if((**it).info2.find(_state) != std::string::npos && (**it).info2.find(tmp) != std::string::npos)
		{
			if(*it == NULL)
				C_DBG_ERR("dataStructPool pointer error!\n");
			fprintf(stderr, "START_time: %s\ninfo1:%s\ninfo2:%s\n", (**it).time.c_str(),(**it).info1.c_str(),(**it).info2.c_str());
			return (*it)->time;
		}
		if((**it).info2.find(backUpSearch) != std::string::npos && (**it).info2.find(tmp) != std::string::npos)
		{
			if(*it == NULL)
				C_DBG_ERR("dataStructPool pointer error!\n");
			fprintf(stderr, "START_BK_time: %s\ninfo1:%s\ninfo2:%s\n", (**it).time.c_str(),(**it).info1.c_str(),(**it).info2.c_str());
			return (*it)->time;
		} 
	}
	C_DBG_ERR("CAN NOT FIND STARTED TIME!\n");
	
	return "";	
}

std::string SlaveWorker::getOperatorEndTime(std::string _state, int _id)
{
	std::string retTime;
	std::string backUpSearch = "finished. closing...";
	std::string bbackUpSearch = "forwarded"; 
	std::list<SlaveDataStruct*>::iterator it;
	
	char tmp[10];
	itoa(_id, tmp, 10);
	std::string st = tmp;
	
	//fprintf(stderr, "desID:%d\n",_id);
	for(it = dataStructPool.begin(); it != dataStructPool.end(); ++it)
	{
		if((**it).info2.find(_state) != std::string::npos && (**it).info2.find(tmp) != std::string::npos)
		{
			if(*it == NULL)
				C_DBG_ERR("dataStructPool pointer error!\n");
			fprintf(stderr, "END_time: %s\ninfo1:%s\ninfo2:%s\n", (**it).time.c_str(),(**it).info1.c_str(),(**it).info2.c_str());
			return (*it)->time;
		}
		if((**it).info2.find(backUpSearch) != std::string::npos && (**it).info2.find(tmp) != std::string::npos)
		{
			if(*it == NULL)
				C_DBG_ERR("dataStructPool pointer error!\n");
			fprintf(stderr, "END_BK_time: %s\ninfo1:%s\ninfo2:%s\n", (**it).time.c_str(),(**it).info1.c_str(),(**it).info2.c_str());
			return (*it)->time;
		}
	}
	
	fprintf(stderr, "error_time: %s\ninfo1:%s\ninfo2:%s\n", (**it).time.c_str(),(**it).info1.c_str(),(**it).info2.c_str());
	C_DBG_ERR("CAN NOT FIND END TIME!\n");
	
	return "";
}

std::string SlaveWorker::getAttemptId()
{
	std::string retAttemptId = "";
	std::list<SlaveDataStruct*>::iterator it;
	for(it = dataStructPool.begin(); it != dataStructPool.end(); ++it)
	{	
		if((**it).info2.find("is done") != std::string::npos)
		{
			//C_DBG_ERR("!!!FIND!!!\n");
			retAttemptId = (**it).info2.substr(5, 38);
			//fprintf(stderr, "time: %s\ninfo1: %s\ninfo2: %s\n", (**it).time.c_str(),(**it).info1.c_str(),(**it).info2.c_str());
			break;
		}
	}
	fprintf(stderr, "retAttemptId:%s\n", retAttemptId.c_str());
	return retAttemptId;
}

OptreeNode* SlaveWorker::getOptree(int _treeNum, int _index)
{
	if(	_treeNum >= OptreePool.size() )
		return (OptreeNode*)0xFFFFFFFF;
	return OptreePool[_treeNum]->getOptree(_index);	
}

int SlaveWorker::OptreeTransformation()
{
	Optree* opTree;
	if( treeSrc != NULL )
	{
		opTree = new Optree(this);
		opTree->InitTree(treeSrc->getInfo2());
		OptreePool.push_back(opTree);
	}
	else
	{
		//opTree = new Optree(this);
	} 
	return 0;
	//std::cout << "--------------------------------------------------" <<"\n";
}

namespace
{
	struct destrcution
	{
		void operator()(SlaveDataStruct* _s)
		{
			delete _s;
			_s = NULL;
		}	
	}des;	
}


SlaveWorker::~SlaveWorker()
{
	if(treeSrc)
		delete treeSrc;
	
	for(int i = 0; i < OptreePool.size(); i++)
		delete OptreePool[i];
	
	std::for_each(dataStructPool.begin(), dataStructPool.end(), des);
	
} 

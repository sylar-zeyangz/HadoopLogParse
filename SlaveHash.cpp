#include "SlaveHash.h"

SlaveHash::SlaveHash()
{
	value = new SlaveDataStruct;
}	

/*
int SlaveHash::SlaveHash(SlaveDataStruct& _dataStruct)
{
	
	unsigned char*key = (unsigned char*)_dataStruct.getContent();   
    unsigned long seed1 =0x7FED7FED, seed2 =0xEEEEEEEE;   
    int ch;   
  
    while(*key !=0)   
    {   
        ch = toupper(*key );   
  
        seed1 = cryptTable[(dwHashType <<8) ch] ^ (seed1 seed2);   
        seed2 = ch+ seed1+ seed2 +(seed2 <<5) 3;   
    }   
    return 0;   
}*/

/*
int SlaveHash::HashInsert(SlaveDataStruct& _dataStruct)
{
	
}
*/
/*
bool SlaveHash::HashFind(SlaveDataStruct& _dataStruct)
{
	
}*/

SlaveHash::~SlaveHash()
{
	delete value; 
}

SlaveDataStruct::SlaveDataStruct()
{
	time = "";
	level = "";
	relateclass = "";
	info1 = "";
	info2 = "";
	info3 = "";

 	sign = '0';
}

SlaveDataStruct::~SlaveDataStruct()
{
	
}

int SlaveDataStruct::setTime( std::string _time )
{
	time = _time;
}

int SlaveDataStruct::setLevel( std::string _level )
{
	level = _level;
}

int SlaveDataStruct::setClass( std::string _relateclass )
{
	relateclass = _relateclass;
}

int SlaveDataStruct::setInfo1( std::string _info1 )
{
	info1 = _info1;
}

int SlaveDataStruct::setInfo2( std::string _info2 )
{
	info2 = _info2;
}

int SlaveDataStruct::setInfo3( std::string _info3 )
{
	info3 = _info3;
}

std::string SlaveDataStruct::getInfo2()
{
	return info2;
}





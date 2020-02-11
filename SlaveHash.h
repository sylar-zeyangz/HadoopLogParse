#ifndef ___SlaveHash_H___
#define ___SlaveHash_H___

#include <string>
#include <iostream>

#define HASH_MAXSIZE 300; 

class SlaveDataStruct
{
	private:
	 	char sign;								
	
	public:
		std::string time; 
		std::string level;
		std::string relateclass;				
		std::string info1;
		std::string info2;
		std::string info3;
	
		int setTime( std::string _time );
		int setLevel( std::string _level );
		int setClass( std::string _relateclass );
		int setInfo1( std::string _info2 );
		int setInfo2( std::string _info2 );
		int setInfo3( std::string _info3 );
		
		std::string getInfo2();
		
		SlaveDataStruct();
	 	virtual ~SlaveDataStruct();
};

typedef std::string KeyType; 		 
const int NULLKEY = 0;				 
//int confliction = 0; 				

class SlaveHash
{
	private:
	SlaveDataStruct *value;  	// storage of struction
    int length;					 
    
	public:
	
	//int SlaveHash(SlaveDataStruct& _dataStruct);
	//int HashInsert(SlaveDataStruct& _dataStruct);
    //bool HashFind(SlaveDataStruct& _dataStruct);
  
	SlaveHash();
	~SlaveHash();
	
};

#endif //___SlaveHash_H___

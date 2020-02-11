#include "MasterFileIn.h"

MasterFileIn::MasterFileIn()
{
	
}

int MasterFileIn::ReadJsonFromFile( const char* _filename  )  
{  
    Json::Reader reader;
    Json::Value* root; // Json::Value is a vital type£¬which can replace any type of data,e.g int, string, object, array         

    std::ifstream is;  
    is.open ( _filename ); 
    std::string FileBuffer;
    
    
    while( !is.eof() )
    {
    	int f_quote;
    	int b_quote;
    	FileBuffer.clear();
    	getline(is, FileBuffer);		//is >> FileBuffer; getline() function: read line till \n
    	if( FileBuffer == "\n" || FileBuffer == "Avro-Json\n" )
    	{
	    	continue;
	    }
    	f_quote = FileBuffer.length();
		
		while((b_quote = FileBuffer.rfind(":{\"", f_quote - 1)) != std::string::npos)  	
	   	{
	   		b_quote--;
			f_quote = FileBuffer.rfind("\"", b_quote - 1);
			std::string tmp;
			tmp = FileBuffer.substr(f_quote + 1, b_quote - f_quote - 1);
			//std::cout << f_quote << std::endl << b_quote << std::endl;
			//std::cout << tmp << std::endl;
			ValueTypeSet.insert(tmp);
	    }

		root = new Json::Value();
   		//std::cout << FileBuffer << std::endl; 
		//std::cout << "------------------------------------------------" << std::endl; 
		reader.parse( FileBuffer, *root, -1 );
		//std::string tmptype = **root["type"].asString();
		//	std::cout << "-------------"<< t <<"---------------------" << std::endl;
		//if( *root["type"].asString() == "record" || *root["type"].asString() == "AM_STARTED" )
		//	continue; 
  		value_pool.push_back( root ); 
    }

	is.close();
	
	return 0;
}

int MasterFileIn::LocateFile()
{
		
}

int MasterFileIn::Clear()
{
	std::list<Json::Value*>::iterator it;
	for(it = value_pool.begin(); it != value_pool.end(); ++it)
	{
		delete (*it);
	}
	value_pool.clear();
}

MasterFileIn::~MasterFileIn()
{
	Clear();
}


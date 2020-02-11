#ifndef ___Optree_H___
#define ___Optree_H___

#include <vector>
#include <iostream>
#include <set>
#include "TimeOperator.h"

class OptreeNode
{
	private:
		
	public:
	int ID;
	std::vector<OptreeNode*> children;
	int timeSpend;
	int rows;
	OptreeNode* parent;
	std::string name; 
	
	OptreeNode()
	{
		ID = -1;
		parent = NULL;
		timeSpend = 0;
		rows = 0;
	}
	
	virtual ~OptreeNode()
	{
		
	}
};

class SlaveWorker;

class Optree
{
	private:
	int SetParent( int _parent, int _index );
	int SetChildren( int _children, int _index );
	int	id_max;
	
	public:	
	SlaveWorker* upLayer;
	OptreeNode* root;
	std::vector<std::string> attemptId;
	int operator += ( Optree* _income );
	std::vector<OptreeNode*> index;
	int InitTree( std::string _optree );
	int DisplayOptree();
	
	OptreeNode* getOptree(int _index);
	
	Optree(SlaveWorker* _upLayer);
	~Optree();
};

#endif //___Optree_H___

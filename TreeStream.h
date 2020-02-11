#ifndef ___TreeStream_H___
#define ___TreeStream_H___

#include <vector>
#include <iostream>
#include <set>
#include <time.h>

class TreeStreamNode
{
	private:
		
	public:
	int ID;
	std::vector<TreeStreamNode*> children;
	TreeStreamNode* parent;
	
	TreeStreamNode()
	{
		ID = -1;
		parent = NULL;
	}
	
	virtual ~TreeStreamNode()
	{
		 
	}
};

class SlaveWorker;

class TreeStream
{
	private:
	int SetParent( int _parent, int _index );
	int SetChildren( int _children, int _index );
	int	id_max;
	
	public:	
	SlaveWorker* upLayer;
	OptreeNode* root;
	int operator += ( Optree* _income );
	std::vector<OptreeNode*> index;
	int InitTree( std::string _optree );
	int DisplayOptree();
	
	OptreeNode* getOptree(int _index);
	
	TreeStream(SlaveWorker* _upLayer);
	~TreeStream();
};

#endif //___TreeStream_H___

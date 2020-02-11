#include "Optree.h" 
#include <stack>
#include "C_Debug.h"
#include "SlaveWorker.h"

Optree::Optree(SlaveWorker* _upLayer)
{
	root = NULL;
	upLayer = _upLayer;
	//attemptId = "";
	if(upLayer)
		attemptId.push_back(upLayer->getAttemptId());							//attemptId
}

int Optree::InitTree( std::string _optree )
{
	int pos1 = 0;
	int pos2 = 0;
	id_max = 0;
	while(pos1 != std::string::npos )
	{
		pos1 = _optree.find("Id =", pos2);
		if( pos1 != std::string::npos )
		{
			pos2 = _optree.find("\n", pos1);
			if(_optree.substr(pos1 + 4, 1) == " ")
				continue;
			int tmp = 0;
			sscanf(_optree.substr(pos1, pos2 - pos1 ).c_str(), "Id =%d", &tmp);
			if( id_max < tmp )
				id_max = tmp;
		}	
	}
	index.resize(id_max + 1);
	for(int i = 0; i < id_max + 1; i++)
	{
		index[i] = NULL;
	}
	
	std::stack<std::string> data_stack;
	int beginoffset = 0;
	int next_lt = 0;
	int next_endl = 0;
	while(beginoffset != std::string::npos)
	{
		next_lt = _optree.find("<", beginoffset+1);
		next_endl = _optree.find('\n', beginoffset+1);
		int min;
		next_lt > next_endl ? (min = next_endl) : (min = next_lt);
		if(next_lt == std::string::npos)
			min = next_endl;
		std::string tmp_sub;
		tmp_sub = _optree.substr(beginoffset, min - beginoffset);
		
		if(tmp_sub[1] != '\\')
		{
			//std::cout << "push\n";
			//std::cout << "substr = \"" << tmp_sub << "\"\n";
			if(tmp_sub.find("Parent") != std::string::npos)
			{
				data_stack.push(tmp_sub);
			}
			else if(tmp_sub.find("Children") != std::string::npos)
			{
				data_stack.push(tmp_sub);
			}
			else
			{			
				int tmp_index_id;
				int tmp_rt = tmp_sub.find(">");
				sscanf(tmp_sub.substr(tmp_rt + 1).c_str(), "Id =%d", &tmp_index_id);
				index[tmp_index_id] = new OptreeNode;
				SYSTEM_TIME t1 = {};
				SYSTEM_TIME t2 = {};
				std::string s_start = "Initializing Self";
				std::string s_end = "Close done";
				C_DBG_ERR("-------------------------------\n");
				fprintf(stderr, "OPNAME:%s\n",tmp_sub.substr(1, tmp_rt - 1).c_str());
				t1 = TimeOperator::ToSystemTime(upLayer->getOperatorStartTime(s_start, tmp_index_id));	//time
				std::string tmp = upLayer->getOperatorEndTime(s_end, tmp_index_id);
				if(tmp == "")
					t2 = t1;
				else
					t2 = TimeOperator::ToSystemTime(tmp);						//time
				
				index[tmp_index_id]->rows = upLayer->getOperatorRows(tmp_index_id);					//rows
				index[tmp_index_id]->ID = tmp_index_id;
				index[tmp_index_id]->timeSpend = TimeOperator::TimeSubtraction(t1, t2);
				index[tmp_index_id]->name = tmp_sub.substr(1, tmp_rt - 1);
				
				data_stack.push(tmp_sub);
			}
		}
		else
		{
			//std::cout << "pop\n";
			//std::cout << "substr = \"" << tmp_sub << "\"\n";
			if(tmp_sub.find("Parent") != std::string::npos)
			{
				int tmp_prt = -1;
				int tmp_cld = -1;
				int tmp_rt;
		
				tmp_rt = data_stack.top().find(">");
				sscanf(data_stack.top().substr(tmp_rt + 1).c_str(), "Id =%d", &tmp_prt);
				//std::cout<<"tmp_prt: "<<tmp_prt<<"\n";
				if(data_stack.top().find("Parent") == std::string::npos)
					std::cout<< "ERROR: STACK UNMATCHED" << "\n";
				data_stack.pop();
				
				tmp_rt = data_stack.top().find(">");
				sscanf(data_stack.top().substr(tmp_rt + 1).c_str(), "Id =%d", &tmp_cld);
				//std::cout<<"tmp_cld: "<<tmp_cld<<"\n";
				
				SetParent(tmp_prt, tmp_cld);
			}
			else if(tmp_sub.find("Children") != std::string::npos)
			{
				if(data_stack.top().find("Children") == std::string::npos)
					std::cout<< "ERROR: STACK UNMATCHED" << "\n";	
				data_stack.pop();
			}
			else
			{	
				int tmp_prt = -1;
				int tmp_cld = -1;
				int tmp_rt;	
					
				//std::cout<<"data_stack top: "<<data_stack.top()<<"\n";
				tmp_rt = data_stack.top().find(">");
				sscanf(data_stack.top().substr(tmp_rt + 1).c_str(), "Id =%d", &tmp_cld);
				//std::cout<<"tmp_cld: "<<tmp_cld<<"\n";
			
				if(data_stack.top().find("Children") != std::string::npos
					|| data_stack.top().find("Children") != std::string::npos)
					std::cout<< "ERROR: STACK UNMATCHED" << "\n";
				data_stack.pop();
				
				if(data_stack.empty() == true)
					break;
				
				data_stack.pop();
				tmp_rt = data_stack.top().find(">");
				sscanf(data_stack.top().substr(tmp_rt + 1).c_str(), "Id =%d", &tmp_prt);
				//std::cout<<"tmp_prt: "<<tmp_prt<<"\n";
				data_stack.push("<Children>");

				SetChildren(tmp_cld, tmp_prt);
			}
		}
		
		beginoffset = next_lt;
	}
	
	for(int i = 0; i < index.size(); i++)
	{
		if(index[i] == NULL)
			continue;
		if(index[i]->parent == NULL)
			root = index[i];
	}
}

int Optree::operator += ( Optree* _income )
{
	int count1 = 0;
	int count2 = 0;
	for(int i = 0; i<this->index.size();i++)
	{
		if(this->index[i] != NULL)
			count1++;
	}
	//fprintf(stderr, "count1 = %d\n", count1);
	
	//C_DBG_ERR("JIN RU +=\n");
	int resize_num;
	int min_num;
	(_income->index.size()) > (this->index.size()) ? resize_num = (_income->index.size()) : resize_num = (this->index.size());
	(_income->index.size()) < (this->index.size()) ? min_num = (_income->index.size()) : min_num = (this->index.size());
	if(this->root == NULL && this->index.size() == 0)
	{
		//C_DBG_ERR("LV DENG\n");
	}
	else
	{		
		if(_income == NULL)
		{
			//C_DBG_ERR("NO INCOME TREE\n");
			return -1;
		}
		if(!(this->root->ID == _income->root->ID && this->root->name == _income->root->name))
		{
			//C_DBG_ERR("geng jie dian bu tong\n");
			return -1;
		}
			
		for(int i = 0; i < min_num; i++)
		{
			if(this->index[i] == NULL || _income->index[i] == NULL)
				continue;
			if(this->index[i]->name != _income->index[i]->name)
			{
				//C_DBG_ERR("ming zi id chong tu\n");
				return -1;
			}		
		}
	}
	
	//C_DBG_ERR("Starting Combining\n");
	this->index.resize( resize_num );
	for(int i = 0; i < _income->index.size(); i++)
	{
		if(_income->index[i] == NULL)
			continue;
		if(this->index[i] == NULL)
		{
			OptreeNode* t_node = new OptreeNode;
			t_node->ID =_income->index[i]->ID;
			t_node->name =_income->index[i]->name;
			this->index[t_node->ID] = t_node;
			t_node->timeSpend = _income->index[i]->timeSpend;
			t_node->rows = _income->index[i]->rows;
		}
		else
		{
			if(this->index[i]->name == _income->index[i]->name)
			{
				index[i]->timeSpend += _income->index[i]->timeSpend;
				index[i]->rows += _income->index[i]->rows;
			} 
		}
	}
	for(int i = 0; i < _income->index.size(); i++)
	{
		if(_income->index[i] == NULL)
		{
			continue;	
		}
		if(_income->index[i]->parent != NULL)
		{
			this->index[i]->parent = this->index[_income->index[i]->parent->ID];
//			for(int j = 0; j < _income->index[j]->children.size(); j++)
//			{
//				this->index[i]->children[j] = this->index[_income->index[i]->children[j]->ID];
//			}	
		}	
	} 
	fprintf(stderr, "%d\n", this->index.size());
	for(int i = 0; i < this->index.size(); i++)
	{
		if(this->index.size() == 0)
			break;
		if(this->index[i] == NULL)
			continue;
		if(this->index[i]->parent == NULL)
		{
			this->root = this->index[i];
		}
	}
	
	for(int i = 0; i<this->index.size();i++)
	{
		if(this->index[i] != NULL)
			count2++;
	}
	//fprintf(stderr, "count2 = %d\n", count2);
}

int Optree::SetParent( int _parent, int _index )
{
	(index[_index]) -> parent = index[_parent];
}

int Optree::SetChildren( int _children, int _index )
{
	((index[_index]) -> children).push_back( index[_children] );
}

OptreeNode* Optree::getOptree(int _index)
{
	if(_index >= index.size())
		return (OptreeNode*)0xFFFFFFFF;
	return index[_index];
}

Optree::~Optree()
{
//	std::cout<<"caocao!!!:" <<attemptId.size()<<std::endl;
//	for(int i = 0; i < attemptId.size(); i++)
//	{
//		std::cout<< "caocao:"<<attemptId[i] << std::endl;
//	}
	
	for(int i = 0; i < index.size(); i++)
	{
		if(index[i])
		{
			delete (index[i]);
		}	
	}
	std::cout<<"destruction optree!"<<std::endl;
}


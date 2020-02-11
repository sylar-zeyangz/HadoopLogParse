#include "SystemBase.h"
#include "TTF.h"

//#include <windows.h> 

SystemBase::SystemBase( int _w , int _h )
{
	SDL_Init( SDL_INIT_EVERYTHING );
	w = _w;
	h = _h;
	Screen = SDL_SetVideoMode( w , h , 32 , SDL_HWSURFACE | SDL_DOUBLEBUF );
	Running = 1;
	KeyState = SDL_GetKeyState( NULL );
	TTF_Init();
	
	ttf = new TTF(".\\COOPBL.TTF", 13); 
	ttf2 = new TTF(".\\COOPBL.TTF", 20);
	ttf3 = new TTF(".\\COOPBL.TTF", 20);
	ttf->SetTextColor(255, 255, 50);
	ttf2->SetTextColor(255, 50, 255);
	ttf3->SetTextColor(0, 200, 200);
	
	curSlaveWorkerNum = 14;
 	curTreeNum = 0;
 	curNodeNum = 0;
}

SystemBase::~SystemBase()
{
	delete ttf;
	delete ttf2;
	delete ttf3;
	TTF_Quit();
	SDL_FreeSurface( Screen );
	SDL_Quit();	
}

int SystemBase::PrintElementTree(SDL_Rect _rect, Optree* _tree)
{
	if(_tree != NULL)
		AnalysisOpTree( _tree );
	else
		C_DBG_ERR("ELEMENT TREE IS NULL!\n");
		
	RenderCurrentNodeList(_rect);
	OnClean();
}

int SystemBase::PrintIntegratedTree()
{
	SDL_Colour color_line;
	color_line.r = 0;
	color_line.g = 100;
	color_line.b = 100;
	
	SDL_Colour a_color;
	a_color.r = 0;
	a_color.g = 100;
	a_color.b = 100;
	
	int max_layer = -1;
 	for(int i = 0; i < factory.integratedTree.size(); i++)
	{
		fprintf(stderr, "factory.integratedTree.GetLayer(i)= %d\n", factory.integratedTree.GetLayer(i));
		if(factory.integratedTree.GetLayer(i) > max_layer)
			max_layer = factory.integratedTree.GetLayer(i);
	}
 	
 	max_layer++;
 	fprintf(stderr, "max_layer=%d\n",max_layer);
 	if(max_layer == -1)
 	{
	 	C_DBG_ERR("IntegratedTree ERROR(max_layer = -1)!\n");
 	}

 	int* layerWidth = new int[max_layer];
 	for(int i = 0; i < max_layer; i++)
	{
		layerWidth[i] = 0;
	}
 	for(int i = 0; i < factory.integratedTree.size(); i++)
	{
		layerWidth[factory.integratedTree.GetLayer(i)]++;
	}

 	int* layerCount = new int[max_layer]; 
 	for(int i = 0; i < max_layer; i++)
 	{
 		fprintf(stderr, "layerWidth=%d\n",layerWidth[i]);
 		layerCount[i] = 1;
	}
	
	for(int i = 0; i < factory.integratedTree.size(); i++)
	{
		SDL_Rect Etree_Rect = {0,0,0,0};
		Etree_Rect.x = layerCount[factory.integratedTree.GetLayer(i)] * 1024 * 1 / 5 / (layerWidth[factory.integratedTree.GetLayer(i)] + 1);
		layerCount[factory.integratedTree.GetLayer(i)]++;
		Etree_Rect.y = (factory.integratedTree.GetLayer(i) - 1) * 768 / (max_layer);
		Etree_Rect.w = 400;
		Etree_Rect.h = 768 / (factory.integratedTree.size() + 1);
		
		//SDL_Rect line_rect;
		//line_rect.x = Etree_Rect.x + Etree_Rect.w / 2;
		//line_rect.y = Etree_Rect.y + Etree_Rect.h;
		//line_rect.w = Etree_Rect.x + Etree_Rect.w / 2;
		//line_rect.h = Etree_Rect.x;
		//		
		//C_DrawSegment(Screen, line_rect, color_line);
		
		
		fprintf(stderr, "x=%d, y=%d\n",Etree_Rect.x,Etree_Rect.y);
		PrintElementTree(Etree_Rect, factory.integratedTree[i]);
		C_DrawFrame(Screen, Etree_Rect, a_color);
	}
	delete[] layerWidth;
	delete[] layerCount;
}

int SystemBase::RenderCurrentNodeList(SDL_Rect _rect)
{
	SDL_Rect a_rect, a_id_rect;
	SDL_Colour color;
	color.r = 255;
	color.g = 255;
	color.b = 50;
	
	SDL_Colour color_line;
	color_line.r = 0;
	color_line.g = 100;
	color_line.b = 100;

	for(int i = 0; i < rectPool.size(); i++)
	{
		color_line.r += 50;
		SDL_Rect line_rect;
		line_rect.x = rectPool[i].x * _rect.w / (1024 / 2) + _rect.x;
		line_rect.y = rectPool[i].y * _rect.h / 768  + _rect.y;
		line_rect.w = rectPool[i].w * _rect.w / (1024 / 2) + _rect.x;
		line_rect.h = rectPool[i].h * _rect.h / 768 + _rect.y;
		//fprintf(stderr, "%d %d %d %d",rectPool[i].x, rectPool[i].y, rectPool[i].w, rectPool[i].h);
		C_DrawSegment(Screen, line_rect, color_line);	
	}

	for(int i = 0; i < nodeGraphicPool.size(); i++)
	{
		a_rect.x = nodeGraphicPool[i]->node_rect.x * _rect.w / (1024 / 2) + _rect.x;
		a_rect.y = nodeGraphicPool[i]->node_rect.y * _rect.h / 768 + _rect.y;
		a_rect.w = nodeGraphicPool[i]->node_rect.w;
		a_rect.h = nodeGraphicPool[i]->node_rect.h;
		
		a_id_rect.x = a_rect.x + a_rect.w / 3;
		a_id_rect.y = a_rect.y;
		a_id_rect.w = a_rect.w;
		a_id_rect.h = a_rect.h;
		
		SDL_Surface* text_name = ttf->TransFormUTF(nodeGraphicPool[i]->ptr->name.c_str());
		char* id = new char[10]; 
		std::string t = "id=";
		itoa(nodeGraphicPool[i]->ptr->ID, id, 10);
		t = t.append(id);
		SDL_Surface* text_id = ttf->TransFormUTF(t.c_str());
		
		a_rect.x -= text_name->w / 2;
		a_rect.w = text_name->w;
		a_rect.h = text_name->h;
		
		
		SDL_FillRect(Screen, &a_rect, 0);
		C_DrawFrame(Screen ,a_rect, color);
		//
		bool flag_inMsgPool = false;
		for(int j = 0; j < msgMappingPool.size(); j++)
		{
			if(msgMappingPool[j]->ptr == nodeGraphicPool[i]->ptr)
			{
				flag_inMsgPool = true;
			}
		}
		if(flag_inMsgPool == false)
		{
			UINode* tmp_uinode = new UINode;
			//tmp_uinode = nodeGraphicPool[i];
			tmp_uinode->ptr = nodeGraphicPool[i]->ptr;
			tmp_uinode->node_rect = a_rect;
			tmp_uinode->layer = nodeGraphicPool[i]->layer;
			msgMappingPool.push_back(tmp_uinode);
		}
				
		SDL_BlitSurface(text_name, NULL, Screen, &a_rect);
		
		//SDL_FillRect(Screen, &a_id_rect, 0);
		SDL_BlitSurface(text_id, NULL, Screen, &a_id_rect);
		
		SDL_FreeSurface(text_id);
		SDL_FreeSurface(text_name);
	}
	return 0;
}

int SystemBase::OnInit()
{
	factory.MainProcess();
}

int SystemBase::OnPrepare()
{
							

	
	//fprintf(stderr, "length = %d\n",nodeGraphicPool.size());
	/*
	for(int i = 0; i < nodeGraphicPool.size(); i++)
	{
		fprintf(stderr, "length = %d\t",nodeGraphicPool[i]->node_rect.x);
		fprintf(stderr, "length = %d\t",nodeGraphicPool[i]->node_rect.y);
		fprintf(stderr, "length = %d\t",nodeGraphicPool[i]->node_rect.w);
		fprintf(stderr, "length = %d\t\n",nodeGraphicPool[i]->node_rect.h);
	}
	*/
	return 0;
}

int SystemBase::OnEvent()
{
	//event dealing
	switch(Event.type)
	{
		case SDL_QUIT: 
		{
			Running = false;	
		}
		break;
		
		case SDL_KEYUP:
		{
			switch( Event.key.keysym.sym )
			{
				case SDLK_ESCAPE:
					Running = false;
				break;
			}
		}
		break;
		
		case SDL_MOUSEBUTTONUP:
		{
			switch( Event.button.button )
			{
				case SDL_BUTTON_LEFT:
					//C_DBG_ERR("LEFT");
				break;
				case SDL_BUTTON_RIGHT:
					//C_DBG_ERR("RIGHT");
				break;
			}
		} 
		break;
		
		default:
		{
			
		}
	}
	return 0;
}

int SystemBase::OnEvent_Map()
{
	return 0;
}

int SystemBase::OnCalculate()
{
	return 0;
}

int SystemBase::OnRender()
{	
	SDL_FillRect(Screen, NULL, 0);
	RenderMainGraphicDomain();
	RenderNodeMsgDomain();
	
	return 0;
}

int SystemBase::RenderNodeMsgDomain()
{
	SDL_Rect r_title = {600, 10, 200, 300};
	SDL_Rect r_name = {600 + 50, 45, 200, 300};
	SDL_Rect r_id = {600, 80, 200, 300};
	SDL_Rect r_rows = {600, 100, 200, 300};
	SDL_Rect r_timeSpend = {600, 120, 200, 300};
	std::string t_name = "";
	
	int x, y;
	SDL_GetMouseState(&x, &y);
	for(int i = 0; i < msgMappingPool.size(); i++)
	{
		if(msgMappingPool[i]->node_rect.x < x &&
		   msgMappingPool[i]->node_rect.x + msgMappingPool[i]->node_rect.w > x &&
		   msgMappingPool[i]->node_rect.y < y &&
		   msgMappingPool[i]->node_rect.y + msgMappingPool[i]->node_rect.h > y )
		{
			SDL_Surface* text_title = ttf3->TransFormUTF("OperatorName: ");	
				
			std::string t0 = "";
			t0 = t0.append(msgMappingPool[i]->ptr->name);
			if(msgMappingPool[i]->ptr->name == "TS")
			{
				t0.append("(Table Scan Operator)");
			}
			else if(msgMappingPool[i]->ptr->name == "JOIN")
			{
				t0.append("(Join Operator)");
			}
			else if(msgMappingPool[i]->ptr->name == "GBY")
			{
				t0.append("(Group By Operator)");
			}
			else if(msgMappingPool[i]->ptr->name == "EX")
			{
				t0.append("(Extract Operator)");
			}
			else if(msgMappingPool[i]->ptr->name == "LIM")
			{
				t0.append("(Limit Operator)");
			}
			else if(msgMappingPool[i]->ptr->name == "FIL")
			{
				t0.append("(Filter Operator)");
			}
			else if(msgMappingPool[i]->ptr->name == "SEL")
			{
				t0.append("(Select Operator)");
			}
			else if(msgMappingPool[i]->ptr->name == "RS")
			{
				t0.append("(Reduce Sink Operator)");
			}
			else if(msgMappingPool[i]->ptr->name == "FS")
			{
				t0.append("(File Sink Operator)");
			}
			else
			{
				C_DBG_ERR("UNKNOWN OPERATOR NAME!\n");
			}
				
			SDL_Surface* text_name = ttf3->TransFormUTF(t0.c_str());
			
			char* rows = new char[10]; 											//rows
			std::string t2 = "rows= ";
			itoa(msgMappingPool[i]->ptr->rows, rows, 10);
			t2 = t2.append(rows);
			SDL_Surface* text_rows = ttf2->TransFormUTF(t2.c_str());
			
			char* timeSpend = new char[10]; 									//timespend
			std::string t1 = "timeSpend= ";
			itoa(msgMappingPool[i]->ptr->timeSpend, timeSpend, 10);
			t1 = t1.append(timeSpend);
			t1 = t1.append(" millisecond");
			SDL_Surface* text_timeSpend = ttf2->TransFormUTF(t1.c_str());
			
			char* id = new char[10]; 											//id
			std::string t3 = "id=";
			itoa(msgMappingPool[i]->ptr->ID, id, 10);
			t3 = t3.append(id);
			SDL_Surface* text_id = ttf2->TransFormUTF(t3.c_str());
			
			SDL_BlitSurface(text_title, NULL, Screen, &r_title);
			SDL_BlitSurface(text_name, NULL, Screen, &r_name);
			SDL_BlitSurface(text_rows, NULL, Screen, &r_rows);
			SDL_BlitSurface(text_timeSpend, NULL, Screen, &r_timeSpend);
			SDL_BlitSurface(text_id, NULL, Screen, &r_id);
			
			SDL_FreeSurface(text_title);
			SDL_FreeSurface(text_name);
			SDL_FreeSurface(text_rows);
			SDL_FreeSurface(text_timeSpend);
			SDL_FreeSurface(text_id);
			
			delete text_title;
			delete text_name;
			delete text_rows;
			delete text_timeSpend;
			delete text_id;
			delete rows;
			delete timeSpend;
   		}
	}
}

int SystemBase::RenderMainGraphicDomain()
{
	
	SDL_Rect test_rect;
	test_rect.x = 1024 * 4 / 7;
	test_rect.y = 0;
	test_rect.w = 1024 * 4 / 7;
	test_rect.h = 768;
	
	SDL_Colour test_color;
	test_color.r = 100;
	test_color.g = 100;
	test_color.b = 100;
	
	int currentIntegratedLayer = -1;
	for(int i = 0; i < factory.integratedTree.size(); i++)
	{
		currentIntegratedLayer = factory.integratedTree.GetLayer(i);
	}
	
	PrintIntegratedTree();
	C_DrawSegment(Screen, test_rect, test_color);
}

int SystemBase::OnClean()
{	
	for(int i = 0; i < nodeGraphicPool.size(); i++)
		delete nodeGraphicPool[i];
	
	nodeGraphicPool.clear();
	rectPool.clear(); 
	
	return 0;
}

int SystemBase::AnalysisOpTree( Optree* _optree )
{
	std::vector<int> layerNum;
	std::vector<int> layerNumSize;
	std::vector<int> layerNumCount;
	int a_NodeNum = 0;
	int a_layer = 0;
	int max_layer = 0;

	OptreeNode* t_node;
	int a_distance = 0;
	while((t_node = _optree->getOptree(a_NodeNum)) != (OptreeNode*)0xFFFFFFFF)
	{
		
		int i = 0;
		if(t_node == NULL)
		{
			a_NodeNum++;
			continue;
		}		
		
		C_DBG_ERR(t_node->name.c_str());
		
		OptreeNode* tmp_node = t_node;;
		a_layer = 0;

		while(tmp_node->parent)
		{
			a_layer++;
			tmp_node = tmp_node->parent;			
		}
		layerNum.push_back(a_layer);
		
		
		if(a_layer > max_layer)
			max_layer = a_layer;
			
		UINode* uinode = new UINode;		
		uinode->layer = a_layer;
		uinode->ptr = t_node; 
		uinode->layer = a_layer;
		if(uinode->ptr->name !=  "MAP")
			nodeGraphicPool.push_back(uinode);
		
		a_NodeNum++;
	}
	layerNumSize.resize(max_layer + 1);
	layerNumCount.resize(max_layer + 1);

	for(int i = 0; i < layerNumSize.size(); i++)	//0,0,0,0
	{
		layerNumSize[i] = 0;			
	}
	for(int i = 0; i < layerNumCount.size(); i++)	//0,0,0,0
	{
		layerNumCount[i] = 0;			
	}

	for(int i = 0; i < layerNumSize.size(); i++)	//1,2,2,2
	{
		for(int j = 0; j < layerNum.size(); j++)
			if(i == layerNum[j])
				layerNumSize[i]++;
	}

	a_distance = (660 - 100) / (max_layer + 1);
	
	for(int i = 0; i < nodeGraphicPool.size(); i++)
	{
		fprintf(stderr, "%d: name:%s\n",i,nodeGraphicPool[i]->ptr->name.c_str());
	}
	
	for(int i = 0; i < nodeGraphicPool.size(); i++)
	{
		if(nodeGraphicPool[i]->ptr->name == "FS" || nodeGraphicPool[i]->ptr->name == "RS")
		{
			nodeGraphicPool[i]->node_rect.x = nodeGraphicPool[i - 1]->node_rect.x;
		}
		else
			nodeGraphicPool[i]->node_rect.x = (512 / (layerNumSize[nodeGraphicPool[i]->layer] + 1)) * (layerNumCount[nodeGraphicPool[i]->layer] + 1);
		layerNumCount[nodeGraphicPool[i]->layer]++;
		nodeGraphicPool[i]->node_rect.y = 0 + 80 + a_distance * nodeGraphicPool[i]->layer;
		nodeGraphicPool[i]->node_rect.w = 80;
		nodeGraphicPool[i]->node_rect.h = 40;
	}

	for(int i = 0; i < nodeGraphicPool.size(); i++)
	{
		if(nodeGraphicPool[i]->ptr->parent == NULL)
			continue;
		for(int j = 0; j < nodeGraphicPool.size(); j++)
		{
			if(nodeGraphicPool[j]->ptr->ID == nodeGraphicPool[i]->ptr->parent->ID)
			{
				SDL_Rect a_rect;
				a_rect.x = nodeGraphicPool[j]->node_rect.x;
				a_rect.y = nodeGraphicPool[j]->node_rect.y;
				a_rect.w = nodeGraphicPool[i]->node_rect.x;
				a_rect.h = nodeGraphicPool[i]->node_rect.y;
				rectPool.push_back(a_rect);
				break;					
			}	
		}		
	}
	C_DBG_ERR("Analysis Tree over."); 
}

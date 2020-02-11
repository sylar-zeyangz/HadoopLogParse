#ifndef ___SYSTEMBASE_H___
#define ___SYSTEMBASE_H___

#include "SDL\SDL.h"
#include "C_Debug.h"
#include "C_SDL_Draw.h"
#include "Factory.h"
#include "UINode.h"
#include <vector>
#include "TTF.h"

#define ERR_EVENT -1
#define ERR_LOOP -2
#define ERR_RENDER -3 

class SystemBase
{
private:
	int w;
	int h;
	SDL_Surface* Screen;
	bool Running;
	SDL_Event Event;
	Uint8* KeyState;   								//char array
	Factory factory;
	TTF* ttf;
	TTF* ttf2;
	TTF* ttf3;
	int curSlaveWorkerNum, curTreeNum, curNodeNum;	//current file number, tree number, optreeNode number 
	
	std::vector<UINode*> nodeGraphicPool;
	std::vector<UINode*> msgMappingPool;
	std::vector<SDL_Rect> rectPool;
	std::vector<SDL_Rect> DrawRectPool;
	int AnalysisOpTree( Optree* _optree );										//This is a adapter function
	int PrintIntegratedTree();
	int PrintElementTree(SDL_Rect _rect, Optree* _tree);						//little tree
	
	int RenderCurrentNodeList(SDL_Rect _rect);
	int RenderMainGraphicDomain();
	int RenderNodeMsgDomain();
	int OnInit();
	int OnPrepare();
	int OnEvent(); 
	int OnCalculate();
	int OnRender();
	int OnEvent_Map();
	int OnClean();
		
public:
	SystemBase( int _w = 1024 , int _h = 720 );
	virtual ~SystemBase();
	
	int OnExecute();
};

#endif	//___SYSTEMBASE_H___ 


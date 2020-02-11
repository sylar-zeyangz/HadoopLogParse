#ifndef ___UINode_H___
#define ___UINode_H___

#include "Optree.h"
#include "SDL\SDL.h"

class UINode
{
	private:	
	
	public:
	OptreeNode* ptr;
	SDL_Rect node_rect;
	int layer;
	
	UINode(); 
	virtual ~UINode();
		
};

#endif //___UINode_H___

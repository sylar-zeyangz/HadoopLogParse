#include "SystemBase.h"

int SystemBase::OnExecute() 
{
	if( OnInit()<0 )   
	{
		C_DBG_ERR("ERR_LOOP\n");
		return ERR_LOOP; 
	}
	
	if( OnPrepare()<0 )   
	{
		C_DBG_ERR("ERR_LOOP\n");
		return ERR_LOOP; 
	}
		
	while( Running )	//frame loop 
	{
		while( SDL_PollEvent( &Event ) ) 	//event loop 
		{
			if( OnEvent()<0 )  //ret error_code<0
			{
				C_DBG_ERR("ERR_EVENT\n");
				return ERR_EVENT;		
			}
		}
		
		if( OnCalculate()<0 )   
		{
			C_DBG_ERR("ERR_LOOP\n");
			return ERR_LOOP; 
		}
			
		if( OnRender()<0 ) 
		{
			C_DBG_ERR("ERR_RENDER\n");
			return ERR_RENDER; 
		}
		SDL_Flip(Screen);
	}	
	
	if( OnClean()<0 )   
	{
		C_DBG_ERR("ERR_LOOP\n");
		return ERR_LOOP; 
	}
}

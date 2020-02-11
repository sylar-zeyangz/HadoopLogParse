#include "TTF.h"

int TTF::Blit( SDL_Surface* dst , SDL_Rect dstRect , Uint16* text )
{
	SDL_Surface* src = NULL;
	src = TTF_RenderUNICODE_Blended( pFont , text , textColor );
	
	if( src )
		SDL_BlitSurface( src , NULL , dst , &dstRect );
	else
	{
		return -1;
		fprintf( stderr , "pSurDBG is NULL ////CAS.OnDebug.cpp->OnDebug\n" );
	}
	
	if( src )
		SDL_FreeSurface( src );
	
	return 0;
}

int TTF::Blit( SDL_Surface* dst , SDL_Rect dstRect , Uint16* text , SDL_Color fg )
{
	SDL_Surface* src = NULL;
	src = TTF_RenderUNICODE_Blended( pFont , text , fg );
	
	if( src )
		SDL_BlitSurface( src , NULL , dst , &dstRect );
	else
	{
		return -1;
		fprintf( stderr , "pSurDBG is NULL ////CAS.OnDebug.cpp->OnDebug\n" );
	}
	
	if( src )
		SDL_FreeSurface( src );
	
	return 0;
}

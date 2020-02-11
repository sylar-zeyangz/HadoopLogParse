#include "TTF.h"

SDL_Surface* TTF::TransForm( Uint16 *text )
{
	SDL_Surface* ret = NULL; 
	ret = TTF_RenderUNICODE_Blended( pFont , text , textColor );
	return ret;
}

SDL_Surface* TTF::TransForm( Uint16 *text , SDL_Color fg )
{
	SDL_Surface* ret = NULL;
	ret = TTF_RenderUNICODE_Blended( pFont , text , fg );
	return ret;
}

SDL_Surface* TTF::TransFormUTF( char* text )
{
	SDL_Surface* ret = NULL;
	ret = TTF_RenderUTF8_Blended( pFont , text , textColor );
	return ret;
}

SDL_Surface* TTF::TransFormUTF( char* text , SDL_Color fg)
{
	SDL_Surface* ret = NULL;
	ret = TTF_RenderUTF8_Blended( pFont , text , fg );
	return ret;
}

SDL_Surface* TTF::TransFormUTF( const char* text )
{
	SDL_Surface* ret = NULL;
	ret = TTF_RenderUTF8_Blended( pFont , text , textColor );
	return ret;
}

SDL_Surface* TTF::TransFormUTF( const char* text , SDL_Color fg)
{
	SDL_Surface* ret = NULL;
	ret = TTF_RenderUTF8_Blended( pFont , text , fg );
	return ret;
}

#include "TTF.h"

TTF::TTF( const char* FontFile , int FontSize )
{
	pFont = NULL;
	pSurMessage = NULL;
	pFont = TTF_OpenFont( FontFile , FontSize );
	
	textColor.r = 250;
	textColor.g = 250;
	textColor.b = 250;
	
	if( pFont == NULL )
	{
		fprintf( stderr , "TTF_OpenFont: Open ttf file <%s> %s\n",
				 FontFile, TTF_GetError());
		return;
	}
	
	//TTF_SetFontStyle( pFont , TTF_STYLE_BOLD );
	
}

TTF::~TTF()
{
	if( pFont )
		TTF_CloseFont( pFont );
	pFont = NULL;
	
	if( pSurMessage )
		SDL_FreeSurface( pSurMessage );
	pSurMessage = NULL;
}

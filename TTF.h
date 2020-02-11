#ifndef __SDL_TTF_H__
#define __SDL_TTF_H__

#include <SDL\SDL_ttf.h>
#include <stdarg.h>

#define STXINWEI 0x0

class TTF
{
	TTF_Font* pFont;
	SDL_Color textColor;
	SDL_Surface* pSurMessage;
public:
	
	void SetTextColor( Uint8 r , Uint8 g ,Uint8 b );
	SDL_Surface* TransForm( Uint16 *text );
	SDL_Surface* TransForm( Uint16 *text , SDL_Color fg );
	SDL_Surface* TransFormUTF( char *text );
	SDL_Surface* TransFormUTF( char *text , SDL_Color fg );
	SDL_Surface* TransFormUTF( const char *text );
	SDL_Surface* TransFormUTF( const char *text , SDL_Color fg );
	int Blit( SDL_Surface* dst , SDL_Rect dstRect , Uint16* text );
	int Blit( SDL_Surface* dst , SDL_Rect dstRect , Uint16* text , SDL_Color fg );
	
	TTF( const char* FontFile , int FontSize );
	~TTF();
};

#endif	//__SDL_TTF_H__

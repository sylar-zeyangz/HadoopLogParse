#ifndef __C_SDL_DRAW__
#define __C_SDL_DRAW__

#include <stdio.h>
#include <iostream>

#include <SDL\SDL.h>
#include <SDL\SDL_image.h>

void C_DrawPixel(SDL_Surface *dstscreen, Uint16 x, Uint16 y, SDL_Color color);

void C_DrawFrame(SDL_Surface *dstscreen, SDL_Rect rect, SDL_Color color);

void C_DrawSegment(SDL_Surface *dstscreen, SDL_Rect rect, SDL_Color color);

void C_DrawSegmentEx(SDL_Surface *dstscreen, SDL_Rect rect, SDL_Color color ,double width);

SDL_Surface* C_LoadPng( char* PngName );

SDL_Surface* C_Cut_Surface(SDL_Surface* _src, SDL_Rect _rect);

#endif /*__C_SDL_DRAW__*/

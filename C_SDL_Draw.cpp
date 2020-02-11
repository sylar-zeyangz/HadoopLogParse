#include "C_SDL_Draw.h"
#include "C_Debug.h"
#include "math.h"

void C_DrawPixel(SDL_Surface *dstscreen, Uint16 x, Uint16 y, SDL_Color Color)
{
	Uint32 color = SDL_MapRGB(dstscreen->format, Color.r, Color.g, Color.b);
	
	if( x >= dstscreen->w || y >= dstscreen->h )
		return;
	
	if( SDL_MUSTLOCK(dstscreen) )
		if( SDL_LockSurface(dstscreen) < 0 )
			return;
	
	switch(dstscreen->format->BytesPerPixel)
	{
		case 1:
		{ /* assume 8-bpp */ 
			Uint8 *bufp;
			
			bufp = (Uint8 *)dstscreen->pixels + y*dstscreen->pitch + x;
			*bufp = color;
		}
		break;
		
		case 2:
		{ /* Maybe 15-bpp or 16-bpp */ 
			Uint16 *bufp;
			
			bufp = (Uint16 *)dstscreen->pixels + y*dstscreen->pitch/2 + x;
			*bufp = color;
		}
		break;
		
		case 3:
		{ /* slowest 24-bpp mode£¬Almostly Never */ 
			Uint8 *bufp;
			
			bufp = (Uint8 *)dstscreen->pixels + y*dstscreen->pitch + x;
			*(bufp+dstscreen->format->Rshift/8) = Color.r;
			*(bufp+dstscreen->format->Gshift/8) = Color.g;
			*(bufp+dstscreen->format->Bshift/8) = Color.b;
		}
		break;
		
		case 4:
		{ /* Maybe 32-bpp */ 
			Uint32 *bufp;
			
			bufp = (Uint32 *)dstscreen->pixels + y*dstscreen->pitch/4 + x;
			*bufp = color;
		}
		break;
	}
	
	if( SDL_MUSTLOCK(dstscreen) )
		SDL_UnlockSurface(dstscreen);
	
	//SDL_UpdateRect(dstscreen, x, y, 1, 1);
}

void C_DrawFrame(SDL_Surface *dstscreen, SDL_Rect rect, SDL_Color color)
{
	if( rect.w <= 0 || rect.h <= 0 )
		return;
	
	for( int i = rect.x; i < rect.x + rect.w; i++ )
	{
		C_DrawPixel( dstscreen , i, rect.y, color);
	}
	for( int i = rect.x; i < rect.x + rect.w; i++ )
	{
		C_DrawPixel( dstscreen , i, rect.y+rect.h-1, color);
	}
	for( int i = rect.y+1; i < rect.y+rect.h-1; i++ )
	{
		C_DrawPixel( dstscreen , rect.x, i, color);
	}
	for( int i = rect.y+1; i < rect.y+rect.h-1; i++ )
	{
		C_DrawPixel( dstscreen , rect.x+rect.w-1, i, color);
	}
}

void C_DrawSegment(SDL_Surface *dstscreen, SDL_Rect rect, SDL_Color color)
{
	if(rect.x == rect.w && rect.y == rect.h)
	{
		C_DrawPixel(dstscreen,rect.x,rect.y,color);
		return;
	}
	
	if(abs(rect.x-rect.w)>=abs(rect.y-rect.h))
		if(rect.w>=rect.x)
			for(int i = 0;i<rect.w-rect.x+1;i++)
				C_DrawPixel(dstscreen,rect.x+i,rect.y+(rect.h-rect.y)*i/(rect.w-rect.x),color);
		else
			for(int i = 0;i<rect.x-rect.w+1;i++)
				C_DrawPixel(dstscreen,rect.x-i,rect.y+(rect.h-rect.y)*i/(rect.x-rect.w ),color);
	else
		if(rect.h>=rect.y)
			for(int i = 0;i<rect.h-rect.y+1;i++)
				C_DrawPixel(dstscreen,rect.x+(rect.w-rect.x)*i/(rect.h-rect.y),rect.y+i,color);
		else
			for(int i = 0;i<rect.y-rect.h+1;i++)
				C_DrawPixel(dstscreen,rect.x+(rect.w-rect.x)*i/(rect.y-rect.h),rect.y-i,color);
}

void C_DrawSegmentEx(SDL_Surface *dstscreen, SDL_Rect rect, SDL_Color color ,double width)
{
	C_DBG_ERR("To Do.\n");
}

SDL_Surface* C_Cut_Surface(SDL_Surface* _src, SDL_Rect _rect)
{
	if(_src == NULL)
		return NULL;
	
	//The cuted surface that will be used 
	SDL_Surface* cutImage = SDL_CreateRGBSurface( _src->flags,
														_rect.w,
														_rect.h,
														32,
														_src->format->Rmask,
														_src->format->Gmask,
														_src->format->Bmask,
														_src->format->Amask );
	
	//The optimized surface that will be used 
	SDL_Surface* optimizedImage = NULL;
	
	//If the surface was created 
	if( cutImage == NULL )
	{
		C_DBG_ERR("Transformed Image Err\n");
		return NULL;
	}
	
	SDL_Rect r = {0,0,0,0};
	SDL_Rect fr = {0,0,0,0};
	
	fr.w = cutImage->w;
	fr.h = cutImage->h;
	
	SDL_FillRect( cutImage, &fr, SDL_MapRGB(cutImage->format, 0x0, 0xFF, 0xFF));
	
	SDL_BlitSurface( _src, &_rect, cutImage, &r );
	
	//Create an optimized surface 
	optimizedImage = SDL_DisplayFormat( cutImage );
	
	//Free the loaded surface 
	SDL_FreeSurface( cutImage );
	
	//If the surface was optimized 
	if( optimizedImage == NULL )
	{
		C_DBG_ERR("Transformed Image Err\n");
		return NULL;
	}
	
	//Color key surface 
	SDL_SetColorKey( optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
	
	//Return the optimized surface 
	return optimizedImage;
}

SDL_Surface* C_LoadPng( char* PngName )
{
	//The image that's loaded 
	SDL_Surface* loadedImage = NULL;
	
	//The optimized surface that will be used 
	SDL_Surface* optimizedImage = NULL;
	
	//Load the image 
	loadedImage = IMG_Load( PngName );
	
	//If the image loaded 
	if( loadedImage == NULL )
	{
		C_DBG_ERR("Loaded Image Err\n");
		
		return NULL;
	}
	
	//Create an optimized surface 
	optimizedImage = SDL_DisplayFormat( loadedImage );
	
	//Free the loaded surface 
	SDL_FreeSurface( loadedImage );
	
	//If the surface was optimized 
	if( optimizedImage == NULL )
	{
		C_DBG_ERR("Transformed Image Err\n");
		return 0;
	}
	
	//Color key surface 
	SDL_SetColorKey( optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
	
	//Return the optimized surface 
	return optimizedImage;
}

// gray = red * 0.299 + green * 0.587 + blue * 0.114
//(r * 76 + g * 150 + b * 30) >> 8 

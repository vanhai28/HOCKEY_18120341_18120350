
#include "CommonFunction.h"
#include"TextObject.h"
/*
 * Function:
 * ----------------------------------
 *	Free memory

 */
void SDL_CFunction::CleanUp()
{
	SDL_FreeSurface(g_screen);
	SDL_FreeSurface(g_bkground);
}

/*
 * Function: ApplySurface
 * ----------------------------
 *	 Apply the source of surface to detination of surface
 *
 *	 scr: a pointer point to source of Surface
 *   des : a pointer point to destination of Surface
 *
 *   Return : Tọa độ của biến đích
 */
SDL_Rect SDL_CFunction::ApplySurface(SDL_Surface* scr, SDL_Surface* des, int x, int y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(scr, NULL, des, &offset);

	return offset;
}

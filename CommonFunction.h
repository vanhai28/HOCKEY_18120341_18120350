#pragma once
#include <windows.h>
#include <SDL_image.h>
#include <SDL.h>
#include <string>
#include <SDL_ttf.h>
#include <SDL_image.h>

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 700;
const int SCREEN_BPP = 32;
const int RIGHT_BOUNDARY = 500;
const int LEFT_BOUNDARY = 5;
const int TOP_BOUNDARY = 5;
const int BOTTOM_BOUNDRY = SCREEN_HEIGHT - 5;


static SDL_Surface * g_screen = NULL;
static SDL_Surface * g_bkground = NULL;
static SDL_Surface* g_img_menu = NULL;
static SDL_Event g_event;

namespace SDL_CFunction {
	void   CleanUp();
	SDL_Rect  ApplySurface(SDL_Surface* scr, SDL_Surface* des, int x, int y);
	SDL_Surface* LoadImage(std::string file_path);
}
int ShowMenu(SDL_Surface *des, TTF_Font * font);

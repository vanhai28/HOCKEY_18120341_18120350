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
const int RIGHT_BOUNDARY = 545;
const int LEFT_BOUNDARY = 5;
const int TOP_BOUNDARY = 5;
const int BOTTOM_BOUNDRY = SCREEN_HEIGHT ;


static SDL_Surface * g_screen = NULL;
static SDL_Surface * g_bkground = NULL;
static SDL_Event g_event;

namespace SDL_CFunction {
	void   CleanUp();
	void   ApplySurface(SDL_Surface*& scr, SDL_Surface*& des, int x, int y);

	SDL_Surface*   LoadImage(std::string file_path);
}

void pause_game();
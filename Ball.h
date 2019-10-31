#pragma once

#include "Player.h"
#include <SDL_mixer.h>

#define WIDTH_BALL 15
#define HEIGHT_BALL 15
#define MAX_SPEED 50
//-------------------static variable---------------
static Mix_Chunk* g_sound_player1 = NULL;
static Mix_Chunk* win = NULL;



class Ball : public   BaseObject
{
public:
	void HandleMove(SDL_Rect playerTop, SDL_Rect playerButtom, bool &is_finish, int &win,Mix_Chunk*& bullet_sound, int & mark);

	int Get_x_val() { return x_val; }
	void Set_x_val(int val) { x_val = val; }

	int Get_y_val() { return y_val; }
	void Set_y_val(int val) { y_val = val; }

	bool Get_is_move() { return is_move; }
	void Set_is_move(bool val) { is_move = val; }

	Ball();
	~Ball();
private :
	bool is_move;
	int x_val;
	int y_val;
};


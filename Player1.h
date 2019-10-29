#pragma once
#include <SDL_mixer.h>
#include "BaseObject.h"
const int  X_PLAYER_1 = RIGHT_BOUNDARY / 2;
const int  Y_PLAYER_1 = 20;

#define WIDTH_Player_1 88
#define HEIGHT_Player_1 30
class Player1 : public BaseObject
{
public:
	Player1();
	~Player1();

	void HandleInputAction(SDL_Event events);
	void  HandleMove();
	bool Get_is_move() {return is_move;}
	void Set_is_move(bool val) { is_move = val; }

private:
	bool is_move;
	int x_val;
	int y_val;
};


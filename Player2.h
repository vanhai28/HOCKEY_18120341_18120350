#pragma once
#include "PLAYER.h"

const int  X_PLAYER_2 = RIGHT_BOUNDARY / 2;
const int  Y_PLAYER_2 = SCREEN_HEIGHT - 30;

class Player2 : public PLAYER
{
public:
	Player2();

	~Player2();
	void PredictDropPoint(SDL_Rect a, int b, int c) {};
	void HandleInputAction(SDL_Event events);
	void HandleMove();
	bool Get_is_move() { return is_move; }
	void Set_is_move(bool val) { is_move = val; }
private:
	bool is_move;
	int x_val;
	int y_val;
};


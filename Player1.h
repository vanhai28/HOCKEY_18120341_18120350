#pragma once
#include <SDL_mixer.h>
#include "PLAYER.h"

class Player1 : public PLAYER
{
public:
	Player1();
	~Player1();

	void HandleInputAction(SDL_Event events);
	void  HandleMove();
	void PredictDropPoint(SDL_Rect a, int b, int c) {};
	bool Get_is_move() {return is_move;}
	void Set_is_move(bool val) { is_move = val; }

private:
	bool is_move;
	int x_val;
	int y_val;
};


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


};


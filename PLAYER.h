#pragma once
#include "BaseObject.h"

const int  X_PLAYER_1 = RIGHT_BOUNDARY / 2;
const int  Y_PLAYER_1 = 20;

#define WIDTH_Player_1 88
#define HEIGHT_Player_1 30
class PLAYER :public BaseObject
{
public:
	virtual void HandleInputAction(SDL_Event events) = 0;
	virtual void HandleMove() = 0;
	virtual void PredictDropPoint(SDL_Rect, int, int) = 0;
	PLAYER();
	~PLAYER();
};


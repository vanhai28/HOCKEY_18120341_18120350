#pragma once
#include "BaseObject.h"

const int  X_PLAYER = RIGHT_BOUNDARY / 2;
const int  Y_PLAYER = 20;

#define WIDTH_PLAYER 88
#define HEIGHT_PLAYER 30
class PLAYER :public BaseObject
{
public:
	virtual void HandleInputAction(SDL_Event events) = 0;
	virtual void HandleMove() = 0;
	virtual void PredictDropPoint(SDL_Rect, int, int) = 0;
	PLAYER();
	~PLAYER();
};


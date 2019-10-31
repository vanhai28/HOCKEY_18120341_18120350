#pragma once
#include "BaseObject.h"

const int  X_PLAYER = RIGHT_BOUNDARY / 2;
const int  Y_PLAYER = 20;

#define WIDTH_PLAYER 120
#define HEIGHT_PLAYER 15
class PLAYER :public BaseObject
{
public:
	virtual void HandleInputAction(SDL_Event events) = 0;
	virtual void HandleMove() = 0;
	virtual void PredictDropPoint(SDL_Rect, int, int) = 0;

	bool GetIsMove() { return is_move; }
	void SetIsMove(bool val) { is_move = val; }

	int GetMark() { return mark; }
	void SetMark(int val) { mark = val; }

	PLAYER();
	~PLAYER();


protected :
	bool is_move;
	int x_val;
	int y_val;
	int mark;
};


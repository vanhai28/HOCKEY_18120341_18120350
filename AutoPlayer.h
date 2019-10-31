#pragma once
#include "Player1.h"
#define x_step 10
class AutoPlayer : public Player1
{
public:
	AutoPlayer();
	~AutoPlayer();

	void PredictDropPoint(SDL_Rect, int, int);
	void  HandleMove();


private:
	int x_des;
};


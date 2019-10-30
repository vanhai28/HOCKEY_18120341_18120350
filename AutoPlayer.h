#pragma once
#include "Player1.h"
class AutoPlayer : public Player1
{
public:
	AutoPlayer();
	~AutoPlayer();

	void PredictDropPoint(SDL_Rect, int, int);
	void  HandleMove();
	bool Get_is_move() { return is_move; }
	void Set_is_move(bool val) { is_move = val; }

private:
	bool is_move;
	int x_val;
	int x_des;
};

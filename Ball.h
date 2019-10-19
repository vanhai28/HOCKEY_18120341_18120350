#pragma once

#include "BaseObject.h"
#include "Player1.h"
#include "Player2.h"
#include "CommonFunction.h"
#define WIDTH_BALL 40
#define HEIGHT_BALL 31



class Ball : public   BaseObject
{
public:
	void HandleMove(SDL_Rect playerTop, SDL_Rect playerButtom, bool &is_finish, int &win);

	int Get_x_val() { return x_val; }
	void Set_x_val(int val) { x_val = val; }

	int Get_y_val() { return y_val; }
	void Set_y_val(int val) { y_val = val; }

	Ball();
	~Ball();
private :
	int x_val;
	int y_val;
};


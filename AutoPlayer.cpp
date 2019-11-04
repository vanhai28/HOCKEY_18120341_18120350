#include "AutoPlayer.h"



AutoPlayer::AutoPlayer()
{
	is_move = false;
	x_val = 5;
	rect_.x = X_PLAYER;
	rect_.y = Y_PLAYER;
	rect_.w = HEIGHT_PLAYER;
	rect_.h = HEIGHT_PLAYER;
}


AutoPlayer::~AutoPlayer()
{
}

void AutoPlayer::PredictDropPoint(SDL_Rect ball, int x_val_ball, int y_val_ball)
{
	if (y_val_ball > 0 || ball.y > BOTTOM_BOUNDRY / 2)
	{
		return;
	}
	int x = ball.x;
	int y = ball.y;

	while (y > rect_.y + rect_.h)
	{
		if (x > LEFT_BOUNDARY && x < RIGHT_BOUNDARY)
		{
			x += x_val_ball;
			y += y_val_ball;
		}
		else
		{
			x -= x_val_ball;
			y += y_val_ball;
			x_val_ball *= -1;
		}
	}

	is_move = true;
	x_des = x;
}

void AutoPlayer::HandleMove()
{
	if (is_move && rect_.x < x_des && x_des < (rect_.x + WIDTH_PLAYER))
	{
		is_move = false;
	}
	else if (is_move)
	{
		if (rect_.x + WIDTH_PLAYER <= x_des && rect_.x + WIDTH_PLAYER + x_step < RIGHT_BOUNDARY)
		{
			rect_.x += x_step;
		}
		else if (rect_.x >= x_des && rect_.x - x_step > LEFT_BOUNDARY)
		{
			rect_.x -= x_step;
		}
	}

}
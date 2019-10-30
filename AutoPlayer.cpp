#include "AutoPlayer.h"



AutoPlayer::AutoPlayer()
{
	is_move = false;
	x_val = X_PLAYER_MOVE;
	rect_.x = X_PLAYER_1;
	rect_.y = Y_PLAYER_1;
	rect_.w = HEIGHT_Player_1;
	rect_.h = HEIGHT_Player_1;
}


AutoPlayer::~AutoPlayer()
{
}

void AutoPlayer::PredictDropPoint(SDL_Rect ball, int x_val_ball, int y_val_ball)
{
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

void AutoPlayer::HandleMove(SDL_Rect ball, int x_val_ball, int y_val_ball)
{
	if ( !is_move && ball.y <= SCREEN_HEIGHT / 2 && y_val_ball < 0)
	{
		PredictDropPoint(ball, x_val_ball, y_val_ball);
	}

	if (is_move && !(rect_.x <= x_des && x_des < rect_.x + WIDTH_Player_1))
	{
		if (rect_.x <= x_des)
		{
			rect_.x += x_val;
		}
		else if (rect_.x + WIDTH_Player_1 >= x_des)
		{
			rect_.x -= x_val;
		}
	}
	else
	{
		is_move = false;
	}
}

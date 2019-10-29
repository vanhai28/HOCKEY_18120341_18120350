#include "Player2.h"



Player2::Player2()
{
	is_move = true;
	x_val = 0;
	y_val = 0;
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = HEIGHT_Player_1;
	rect_.h = HEIGHT_Player_1;
}

void Player2::HandleInputAction(SDL_Event events)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_LEFT:
			x_val -= HEIGHT_Player_1 / 3;
			break;
		case SDLK_RIGHT:
			x_val += HEIGHT_Player_1 / 3;;
			break;
		default:
			break;
		}//end switch
	}
	else if (events.type == SDL_KEYUP) {
		x_val = 0;
		y_val = 0;
	}//end if
}

Player2::~Player2()
{
	if (p_object_ != NULL) {
		SDL_FreeSurface(p_object_);
		p_object_ = NULL;
	}
}
void Player2::HandleMove()
{
	if (is_move)
	{
		rect_.x += x_val;

		if (rect_.x + WIDTH_Player_1 > RIGHT_BOUNDARY || rect_.x < 0) {
			rect_.x -= x_val;
		}
	}

}


#include "Player1.h"



Player1::Player1()
{
	is_move = true;
	x_val = 0;
	y_val = 0;
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = HEIGHT_PLAYER;
	rect_.h = HEIGHT_PLAYER;
}


Player1::~Player1()
{
	if (p_object_ != NULL) {
		SDL_FreeSurface(p_object_);
		p_object_ = NULL;
	}
}

void Player1::HandleInputAction(SDL_Event events)
{
	
	if (events.type == SDL_KEYDOWN) 
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_q:
			x_val -= HEIGHT_PLAYER / 3;
			break;
		case SDLK_e:
			x_val += HEIGHT_PLAYER / 3;;
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

void Player1::HandleMove()
{
	if (is_move)
	{
		rect_.x += x_val;

		if (rect_.x + WIDTH_PLAYER > RIGHT_BOUNDARY || rect_.x < 0) {
			rect_.x -= x_val;
		}
	}
	
}


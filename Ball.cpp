#include "Ball.h"
#include <iostream>
void Ball::HandleMove(SDL_Rect playerTop, SDL_Rect playerButtom, bool &is_finish, int& winner, Mix_Chunk*& bullet_sound, int& mark)
{

	if (!is_finish)
	{
		int x = rect_.x + x_val;
		int y = rect_.y + y_val;

		if (rect_.y <= TOP_BOUNDARY)
		{
			is_finish = true;
			winner = 2;
			win = Mix_LoadWAV("Music\\winSound.wav");
			Mix_PlayChannel(-1, win, 0);

		}
		else if (rect_.y + HEIGHT_BALL >= BOTTOM_BOUNDRY)
		{
			is_finish = true;
			winner = 1;
			if (mark != -1)
			{
				win = Mix_LoadWAV("Music\\lose.wav");
				Mix_PlayChannel(-1, win, 0);
			}
			else
			{
				win = Mix_LoadWAV("Music\\winSound.wav");
				Mix_PlayChannel(-1, win, 0);
			}

		}
		else if ((y <= playerTop.y + HEIGHT_PLAYER && playerTop.y + HEIGHT_PLAYER / 2 < y && ((x + WIDTH_BALL / 2 <= playerTop.x && playerTop.x < x + WIDTH_BALL && x_val > 0) || (x <= playerTop.x + WIDTH_PLAYER && playerTop.x + WIDTH_PLAYER <= x + WIDTH_BALL / 2 && x_val < 0))
			|| (y + HEIGHT_BALL >= playerButtom.y && playerButtom.y > y + HEIGHT_BALL / 2 && ((x + WIDTH_BALL / 2 <= playerButtom.x && playerButtom.x < x + WIDTH_BALL && x_val > 0) || (x <= playerButtom.x + WIDTH_PLAYER && playerButtom.x + WIDTH_PLAYER <= x + WIDTH_BALL / 2 && x_val < 0)))))
		{
			rect_.x -= x_val;
			rect_.y -= x_val;
			x_val *= -1;
			y_val *= -1;

			if (y_val < 0 && mark != -1)
			{
				mark++;
			}

			Mix_PlayChannel(-1, bullet_sound, 0);
		}
		//dinh hai ben thanh truot
		else if ((y < playerTop.y + HEIGHT_PLAYER && ((x + WIDTH_BALL >= playerTop.x && playerTop.x >= x + WIDTH_BALL - 3 && x_val > 0) || (x + 3 >= playerTop.x + WIDTH_PLAYER && playerTop.x + WIDTH_PLAYER >= x && x_val < 0))
			|| (y + HEIGHT_BALL > playerButtom.y && ((x + WIDTH_BALL >= playerButtom.x && playerButtom.x >= x + WIDTH_BALL - 3 && x_val > 0) || (x + 3 >= playerButtom.x + WIDTH_PLAYER && playerButtom.x + WIDTH_PLAYER > x && x_val < 0)))))
		{
			if (x + WIDTH_BALL > RIGHT_BOUNDARY || x <= LEFT_BOUNDARY)
			{
				rect_.x -= x_val;
				rect_.y -= x_val;
				x_val *= -1;
				y_val *= -1;
			}
			else
			{
				rect_.y = y;
				rect_.x -= x_val;
			}

			if (y_val < 0 && mark != -1)
			{
				mark++;
			}

			Mix_PlayChannel(-1, bullet_sound, 0);
		}
		else if ((y < playerTop.y + HEIGHT_PLAYER && x + WIDTH_BALL - 2 >= playerTop.x && playerTop.x + WIDTH_PLAYER > x + 2 && y_val < 0)
			|| (y + HEIGHT_BALL > playerButtom.y && x + WIDTH_BALL - 2 >= playerButtom.x && playerButtom.x + WIDTH_PLAYER > x + 2 && y_val > 0))
		{
			rect_.x = x;
			y_val *= -1;

			if (y_val < 0 && mark != -1)
			{
				mark++;
			}

			Mix_PlayChannel(-1, bullet_sound, 0);
		}
		else if (x + WIDTH_BALL > RIGHT_BOUNDARY || x <= LEFT_BOUNDARY)
		{
			rect_.y = y;
			x_val *= -1;
			return;
		}
		else {
			rect_.x = x;
			rect_.y = y;
			return;
		}

		if (abs(x_val) < MAX_SPEED)
		{
			if (x_val > 0) {
				x_val++;
			}
			else {
				x_val--;
			}
		}

		if (abs(y_val) < MAX_SPEED)
		{
			if (y_val > 0) {
				y_val++;
			}
			else {
				y_val--;
			}
		}


	}
}

Ball::Ball()
{
	is_move = false;
	x_val = 2;
	y_val = 2;
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = WIDTH_BALL;
	rect_.h = HEIGHT_BALL;
}


Ball::~Ball()
{
}

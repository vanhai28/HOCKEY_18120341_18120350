// Mô tả : Định nghĩa lớp người chơi thứ nhất
// Ngày cập nhật : 01/11/2019

#pragma once
#include <SDL_mixer.h>
#include "PLAYER.h"

class Player1 : public PLAYER
{
public:
	Player1();
	~Player1();
	//-------------- Định nghĩa các hàm ảo từ lớp cơ sở --------------
	void HandleInputAction(SDL_Event events);

	void  HandleMove();

	void PredictDropPoint(SDL_Rect a, int b, int c) {};

	//----------------------------------------------------------------
};


// Mô tả : định nghĩa lớp người chơi 2
// Ngày cập nhật : 01/11/2019

#pragma once
#include "BasePlayer.h"

const int  X_PLAYER_2 = RIGHT_BOUNDARY / 2 - WIDTH_PLAYER / 2;
const int  Y_PLAYER_2 = SCREEN_HEIGHT - 30;

class Player2 : public BasePlayer
{
public:
	Player2();
	~Player2();
	//-------------- Định nghĩa các hàm ảo từ lớp cơ sở --------------

	void HandleInputAction(SDL_Event events);

	void HandleMove();

	//----------------------------------------------------------------

};

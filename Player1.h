// Mô tả : định nghĩa lớp người chơi 1
// Ngày cập nhật : 01/11/2019
#pragma once
#include <SDL_mixer.h>
#include "BasePlayer.h"

class Player1 : public BasePlayer
{
public:
	Player1();
	~Player1();

	//-------------- Định nghĩa các hàm ảo từ lớp cơ sở --------------
	void HandleInputAction(SDL_Event events);

	void  HandleMove();

	//----------------------------------------------------------------
};

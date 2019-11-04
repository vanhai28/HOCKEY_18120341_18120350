
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

	void PredictDropPoint(SDL_Rect a, int b, int c) {};

	//----------------------------------------------------------------
};

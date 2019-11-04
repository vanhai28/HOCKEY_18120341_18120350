// Mô tả : định nghĩa lớp cho người chơi là máy tính
#pragma once
#include "Player1.h"
#define x_step 10
class AutoPlayer : public Player1
{
public:
	AutoPlayer();
	~AutoPlayer();
	//--------------- Định nghĩa các hàm ảo ở lớp cơ sở -----------------
	void PredictDropPoint(SDL_Rect ball, int x_val_ball, int y_val_ball);
	void  HandleMove();

private:
	int x_des;//vj trí dự đoán quả bóng rơi
};
// Mô tả : định nghĩa lớp người chơi là máy tính
// Ngày cập nhật : 01/11/2019

#pragma once
#include "BasePlayer.h"
#define x_step 10
class AutoPlayer : public BasePlayer
{
public:
	AutoPlayer();
	~AutoPlayer();

	//--------------- Định nghĩa các hàm ảo ở lớp cơ sở -----------------
	void PredictDropPoint(SDL_Rect ball, int x_val_ball, int y_val_ball);
	void  HandleMove();
	void HandleInputAction(SDL_Event events) {};

private:
	int x_des;//vị trí dự đoán quả bóng rơi
};
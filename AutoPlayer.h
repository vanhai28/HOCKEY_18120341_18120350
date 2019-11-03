// Mô tả : định nghĩa lớp cho người chơi là máy tính
// Ngày cập nhật : 01/11/2019
#pragma once
#include "BasePlayer.h"
#define x_step 10//Khoảng cách mỗi lần di chuyển của máy
class AutoPlayer : public BasePlayer
{
public:
	AutoPlayer();
	~AutoPlayer();
	//--------------- Định nghĩa các hàm ảo ở lớp cơ sở -----------------
	void HandleInputAction(SDL_Event events) {};
	void PredictDropPoint(SDL_Rect ball, int x_val_ball, int y_val_ball);
	void  HandleMove();

private:
	int x_ball_predict;//vị trí dự đoán quả bóng rơi
};


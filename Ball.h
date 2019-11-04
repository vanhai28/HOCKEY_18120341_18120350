﻿#pragma once

#include "Player.h"
#include <SDL_mixer.h>

#define WIDTH_BALL 15
#define HEIGHT_BALL 15
#define MAX_SPEED 18
//-------------------static variable---------------



class Ball : public   BaseObject
{
public:

	// Tên hàm 	: HandleMove
	// Mô tả	: Di chuyển vị trí quả bóng
	// Kiểu trả về  : void
	// Tham số SDL_Rect playerTop : tọa độ thnah trượt 1, giúp xác định khi bóng va chạm
	// Tham số SDL_Rect playerButtom : Tạo độ thanh trượt 2, giúp xác định khi bóng va chạm
	// Tham số bool &is_finish : xác định trò chơi đã kết thúc chưa
	// Tham số int &win : Xác định người chiến thắng khi bóng roi vào biên
	// Tham số Mix_Chunk*& bullet_sound : Biến sử dụng tải âm thanh khi bóng cham thanh
	// Tham số mark : Tăng điểm của người chơi trong màn chơi với máy

	int HandleMove(SDL_Rect playerTop, SDL_Rect playerButtom, bool &is_finish, Mix_Chunk* sound[3], int& mark);

	//------------- Các hàm Getter - Setter------------
	int Get_x_val() { return x_val; }
	void Set_x_val(int val) { x_val = val; }

	int Get_y_val() { return y_val; }
	void Set_y_val(int val) { y_val = val; }

	bool Get_is_move() { return is_move; }
	void Set_is_move(bool val) { is_move = val; }

	int Get_speed() { return speed; }
	void Set_speed(int val) { speed = val; }
	//-------------------------------------------------

	Ball();
	~Ball();

private:
	int speed;
	bool is_move;
	int x_val;
	int y_val;
};
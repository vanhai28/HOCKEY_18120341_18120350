
#pragma once
#include "BaseObject.h"

#define WIDTH_PLAYER 120
#define HEIGHT_PLAYER 15


class PLAYER :public BaseObject
{
public:

	// Tên hàm 	: HandleInputAction
	// Mô tả	: Là hàm ảo, Xác định hướng di chuyển của thanh trượt
	// Kiểu trả về  : void
	// Tham số SDL_Event events : Nhận sự kiện vào từ chuột hoặc bàn phím
	virtual void HandleInputAction(SDL_Event events) = 0;

	// Tên hàm 	: HandleMove
	// Mô tả : Thay đổi vị trí thanh trượt
	// Kiểu trả về : void
	virtual void HandleMove() = 0;

	// Tên hàm 	: PredictDropPoint
	// Mô tả	: Hàm ảo, dự đoán vị trí rơi của bóng, sử dụng cho người chơi là máy tính.
	// Kiểu trả về : void
	// Tham số SDL_Rect ball: Tọa độ của quả bóng
	// Tham số int x_val_ball : Khoảng cách di chuyển của bóng theo trục x
	// Tham số int y_val_ball : Khoảng cách di chuyển của bóng theo trục y
	virtual void PredictDropPoint(SDL_Rect ball, int x_val_ball, int y_val_ball) = 0;

	//-------------- Các hàm GETTER -SETTER -----------------
	bool GetIsMove() { return is_move; }
	void SetIsMove(bool val) { is_move = val; }

	int GetMark() { return mark; }
	void SetMark(int val) { mark = val; }
	//------------------------------------------------------
	PLAYER() {};
	~PLAYER() {};


protected:
	bool is_move;
	int x_val;
	int y_val;
	int mark;//Ðiểm của nguời chơi
};

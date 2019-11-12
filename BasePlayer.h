// Mô tả : Là lớp cơ sở cho các lớp người chơi khác, khai báo các hàm ảo sẽ được sử dụng trong các lớp người chơi khác
// Ngày cập nhật : 01/11/2019

#pragma once
#include "BaseObject.h"
//Kích thước thnah trượt
#define WIDTH_PLAYER 120
#define HEIGHT_PLAYER 15

//Vị trí ban đầu của thanh trượt
const int  X_PLAYER = RIGHT_BOUNDARY / 2 - WIDTH_PLAYER /2 ;
const int  Y_PLAYER = 20;

class BasePlayer :public BaseObject
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
	// Tham số int x_val_ball : step di chuyển của bóng theo trục x
	// Tham số int y_val_ball : step di chuyển của bóng theo trục y
	virtual void PredictDropPoint(SDL_Rect ball, int x_val_ball, int y_val_ball) {};

	//-------------- Các hàm GETTER -SETTER -----------------
	bool GetIsMove() { return is_move; }
	void SetIsMove(bool val) { is_move = val; }

	int GetMark() { return mark; }
	void SetMark(int val) { mark = val; }
	//------------------------------------------------------
	BasePlayer();
	~BasePlayer();


protected :
	//Trạng thái của thanh trượt 
	bool is_move;
	//Giá trị x thay đổi mỗi khi người chơi nhấn nút di chuyển
	int x_val;
	int y_val;

	int mark;//Ðiểm của nguời chơi
};


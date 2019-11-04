
#pragma once
#include <SDL.h>
#include "CommonFunction.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();

	// Tên hàm 	: LoadImg
	// Mô tả	: Tải hình ảnh lên
	// Kiểu trả về  : bool
	// Tham số const char* file_name :  đường dẫn file

	bool LoadImg(const char* file_name);

	// Tên hàm 	: show
	// Mô tả	: Thể hiện đối tượng lên cửa sổ
	// Kiểu trả về  : void
	// Tham số DL_Surface* des : Biến đích (thường là cửa sổ màn hình)
	void show(SDL_Surface* des);

	SDL_Rect GetRect() { return rect_; };
	void SetRect(int x, int y, int w = 0, int h = 0) { rect_.x = x; rect_.y = y; rect_.w = w; rect_.h = h; }

	SDL_Surface* GetObject() { return  p_object_; }

protected:

	SDL_Rect rect_;
	SDL_Surface* p_object_;
};
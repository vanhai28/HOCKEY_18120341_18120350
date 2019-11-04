
#pragma once
#include <windows.h>
#include <SDL_image.h>
#include <SDL.h>
#include <string>
#include <SDL_ttf.h>
#include <SDL_image.h>

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 700;
const int SCREEN_BPP = 32;
const int RIGHT_BOUNDARY = 500;
const int LEFT_BOUNDARY = 5;
const int TOP_BOUNDARY = 5;
const int BOTTOM_BOUNDRY = SCREEN_HEIGHT - 5;



namespace SDL_CFunction {

	//-------------------------------------------------------------
	// Tên hàm 	: CleanUp
	// Mô tả	: Giải phóng bộ nhớ các con trỏ sử dụng
	// Kiểu trả về : void
	void   CleanUp();

	//-------------------------------------------------------------
	// Tên hàm     : ApplySurface
	// Mô tả	   : Ðặt SDL_Surface nguồn vào SDL_SurFace dích (thường là màn hình)
	// Kiểu trả về : SDL_Rect
	// Tham số SDL_Surface* scr : con trỏ trỏ đến nguồn
	// Tham số  SDL_Surface* des : con trỏ trỏ đến đích
	// Tham số int x : Tọa độ vị trí đặt hình trên cửa sổ .
	// Tham số int y : Tọa độ vị trí đặt hình trên cửa sổ .
	SDL_Rect  ApplySurface(SDL_Surface* scr, SDL_Surface* des, int x, int y);

	//-------------------------------------------------------------
	// Tên hàm 	: LoadImage
	// Mô tả : Tải hình lên
	// Kiểu trả về : SDL_Surface*
	// Tham số string file_path : Đường dẫn file
	SDL_Surface* LoadImage(std::string file_path);
}

// Tên hàm 	: ShowMenu
// Mô tả	: Hiển thị cửa sổ menu
// Kiểu trả về  : int, xác định chức năng người chơi chọn
// Tham số SDL_Surface *des : Biến đích (thường là màn hình)
// Tham số TTF_Font * font : Font chữ hiển thị
int ShowMenu(SDL_Surface * g_img_menu,SDL_Surface *des, TTF_Font * font);
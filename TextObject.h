// Mô tả : Định nghĩa lớp TextObject, hiển thị kí tự lên màn hình
// Ngày cập nhật : 01/11/2019

#pragma once
#include "BaseObject.h"
#include <string>


class TextObject : public BaseObject
{
public:
	enum TextColor {
		RED_TEXT = 0,
		WHITE_TEXT = 1,
		BLACK_TEXT = 2
	};
	TextObject();
	~TextObject();

	//--------------Các hàm GETTER- SETTER -------------
	std::string GetText() { return str_val_; }
	void SetText(const std::string text) { str_val_ = text; }

	SDL_Color GetColor() { return text_color; }
	void SetColor(const int &type);
	//--------------------------------------------------

	// Tên hàm 	: creatText
	// Mô tả	: hiển thị chữ lên màn hình
	// Kiểu trả về  : void 
	// Tham số TTF_Font *font: Font chữ hiển thị
	// Tham số SDL_Surface* des : đối tượng đích sẽ hiển thị lên, thường là cửa sổ người chơi
	void creatText(TTF_Font *font, SDL_Surface* des);

private:
	std::string str_val_;
	SDL_Color text_color;
};


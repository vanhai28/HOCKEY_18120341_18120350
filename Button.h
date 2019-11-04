
#pragma once
#include "TextObject.h"
class Button : public TextObject
{
public:

	// Tên hàm 	: UpdateColorButton
	// Mô tả	: Cập nhật lại màu hiển thị của text khi người chơi di chuyển chuột 
	// Kiểu trả về  : void 
	// Tham số SDL_Event& _event : Sự kiện nhận vào từ chuột
	// Tham số SDL_Surface *& des : Đối tượng đích để hiển thị lên, thường là cửa sổ người chơi.
	void UpdateColorButton(TTF_Font *font, SDL_Event& _event, SDL_Surface *& des);

	// Tên hàm 	: CheckFocusWithRect
	// Mô tả	: Kiểm tra xem con trỏ chuột có di chuyển đến vị trí nút (button )
	// Kiểu trả về  : bool
	// Tham số onst int &x : Tọa độ x của con trỏ chuột
	// Tham số const int &y : Tọa độ y của con trỏ chuột 
	// Tham số  const SDL_Rect& rect : Tọa độ của nút 
	bool CheckFocusWithRect(const int &x, const int &y, const SDL_Rect& rect);

	Button();
	~Button();
};

#include "Button.h"

bool Button::CheckFocusWithRect(const int &x, const int &y, const SDL_Rect& rect)
{
	if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y + 5 && y <= rect.y + rect.h)
	{
		return true;
	}

	return false;
}


void Button::UpdateColorButton(SDL_Event& _event, SDL_Surface * &des)
{

	TTF_Font* font = TTF_OpenFont("comic.ttf", 40);

	int x_mouse = _event.motion.x;
	int y_mouse = _event.motion.y;

	if (_event.type == SDL_MOUSEMOTION)
	{
		//text_menu[i].SetColor(TextObject::RED_TEXT);
		if (CheckFocusWithRect(x_mouse, y_mouse, this->GetRect()))
		{
			this->SetColor(TextObject::RED_TEXT);
			this->creatText(font, des);
		}
		else
		{
			this->SetColor(TextObject::BLACK_TEXT);
			this->creatText(font, des);
		}
	}

	TTF_CloseFont(font);
	return ;
}

Button::Button()
{

	SetColor(TextObject::BLACK_TEXT);
}


Button::~Button()
{
}

#include "Button.h"

bool Button::CheckFocusWithRect(const int &x, const int &y, const SDL_Rect& rect)
{
	if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h)
	{
		return true;
	}

	return false;
}


bool Button::SetColorButton(SDL_Event _event, SDL_Surface *des)
{
	if (TTF_Init() < 0)
	{
		return false;
	}

	TTF_Font* font = TTF_OpenFont("comic.ttf", 60);

	int x_mouse = _event.motion.x;
	int y_mouse = _event.motion.y;

	switch (_event.type)
	{
		case SDL_MOUSEMOTION:
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
			break;
		}
	}

	TTF_CloseFont(font);
	return false;
}

Button::Button()
{
	SetColor(TextObject::BLACK_TEXT);
}


Button::~Button()
{
}

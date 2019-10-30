#pragma once
#include "TextObject.h"
class Button : public TextObject
{
public:
	bool SetColorButton(SDL_Event _event, SDL_Surface *des);
	bool CheckFocusWithRect(const int &x, const int &y, const SDL_Rect& rect);

	Button();
	~Button();
};


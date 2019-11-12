#include "TextObject.h"



TextObject::TextObject(){}

TextObject::~TextObject(){}

void TextObject::SetColor(const int & type)
{
	SDL_Color  color;

	if (type == RED_TEXT)
	{
		color = { 255, 0, 0 };
	}
	else if (type == WHITE_TEXT)
	{
		color = { 255, 255, 255 };
	}
	else
	{
		color = { 0, 0, 0 };
	}

	text_color = color;
}

void TextObject::displayText(TTF_Font * font, SDL_Surface *des)
{
	p_object_ = TTF_RenderText_Solid(font, str_val_.c_str(), text_color);
	show(des);
	SDL_FreeSurface(p_object_);
}
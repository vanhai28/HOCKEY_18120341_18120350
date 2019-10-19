#pragma once
#include <SDL.h>
#include "CommonFunction.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();

	bool LoadImg(const char* file_name);
	void show(SDL_Surface* des);

	SDL_Rect GetRect() { return rect_; };
	void SetRect(const int x, const int y) { rect_.x = x; rect_.y = y; }
	SDL_Surface* GetObject() { return  p_object_; }

protected:

	SDL_Rect rect_;
	SDL_Surface* p_object_;
};


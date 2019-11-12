#include "BaseObject.h"



BaseObject::BaseObject()
{
	rect_.x = 0;
	rect_.y = 0;
	p_object_ = NULL;
}


BaseObject::~BaseObject(){}

bool BaseObject::LoadImg(const char* file_name) {
	p_object_ = SDL_CFunction::LoadImage(file_name);
	return p_object_ != NULL;
}

void BaseObject::show(SDL_Surface * des) {
	if (p_object_ != NULL) {
		SDL_CFunction::ApplySurface(p_object_, des, rect_.x, rect_.y);
	}
}
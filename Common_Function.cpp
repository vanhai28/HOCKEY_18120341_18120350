#include "pch.h"
#include "Common_Function.h"


void SDL_CFunction::CleanUp()
{
	SDL_FreeSurface(g_screen);
	SDL_FreeSurface(g_bkground);
}

void SDL_CFunction::ApplySurface(SDL_Surface*& scr, SDL_Surface*& des, int x, int y)

{

	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(scr, NULL, des, &offset);

}

bool CheckFocusWithRect(const int &x, const int &y, const SDL_Rect& rect)
{
	if (x >= rect.x && x < rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h)
	{
		return true;
	}
	return false;
}
int SDL_CFunction::ShowMenu(SDL_Surface *des, TTF_Font * font)
{
	g_img_menu = LoadImage("menu.png");

	if (g_img_menu == NULL)
	{
		return 1;
	}

	const int kMenuItemNum = 2;
	SDL_Rect pos_Arr[kMenuItemNum];
	pos_Arr[0].x = 100;
	pos_Arr[0].y = 400; 

	pos_Arr[1].x = 100;
	pos_Arr[1].y = 450;

	TextObject text_menu[kMenuItemNum];

	text_menu[0].SetText("Play Game");
	text_menu[0].SetColor(TextObject::BLACK_TEXT);
	text_menu[0].SetRect(pos_Arr[0].x, pos_Arr[0].y);
	  
	text_menu[1].SetText("EXIT GAME");
	text_menu[1].SetColor(TextObject::BLACK_TEXT);
	text_menu[1].SetRect(pos_Arr[1].x, pos_Arr[1].y);

	bool selected[kMenuItemNum] = { 0,0 };
	int xm = 0; 
	int ym = 0;
	SDL_Event m_event;

	while (true)
	{
		SDL_CFunction::ApplySurface(g_img_menu, des, 0, 0);
		for (int i = 0; i < kMenuItemNum; i++)
		{
			text_menu[i].createGameText(font, des);
		}

		while (SDL_PollEvent(&m_event)) 
		{
			switch (m_event.type)
			{
			case SDL_QUIT:
				return 1;
			case SDL_MOUSEMOTION:
			{
				xm = m_event.motion.x;
				xm = m_event.motion.y;

				for (int i = 0; i < kMenuItemNum; i++)
				{

					if (CheckFocusWithRect(xm, ym, text_menu[i].GetRect()))
					{
						if (selected[i] == false)
						{
							selected[i] = 1;
							text_menu[i].SetColor(TextObject::RED_TEXT);
						}
					}
					else
					{
						if (selected[i] == true)
						{
							selected[i] = 0;
							text_menu[i].SetColor(TextObject::BLACK_TEXT);
						}
					}
				}
				break;
			}
			}
		}
	}

}

SDL_Surface*  SDL_CFunction::LoadImage(std::string file_path) {
	SDL_Surface* load_image = NULL;
	SDL_Surface *optimize_image = NULL;

	load_image = IMG_Load(file_path.c_str());

	if (load_image != NULL)
	{
		optimize_image = SDL_DisplayFormat(load_image);
		SDL_FreeSurface(load_image);
		// transparent background 
		if (optimize_image != NULL)
		{
			UINT32 color_key = SDL_MapRGB(optimize_image->format, 0xFF, 0xFF, 0xFF);
			SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key);
		}
	}

	return optimize_image;
}


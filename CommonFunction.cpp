
#include "CommonFunction.h"
#include"TextObject.h"

void SDL_CFunction::CleanUp()
{
	SDL_FreeSurface(g_screen);
	SDL_FreeSurface(g_bkground);
}

SDL_Rect SDL_CFunction::ApplySurface(SDL_Surface* scr, SDL_Surface* des, int x, int y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(scr, NULL, des, &offset);

	return offset;
}
//description: kiểm tra tọa độ.
bool SDL_CFunction::CheckFocusWithRect(const int &x, const int &y, const SDL_Rect& rect)
{
	if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h)
	{
		return true;
	}
	return false;
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

//description: vẽ menu và lựa chọn cách chơi game.
int SDL_CFunction::ShowMenu(SDL_Surface *des, TTF_Font * font)
{
	g_img_menu = LoadImage("menu.png");
	
	if (g_img_menu == NULL)	//kiểm tra có ảnh menu hay không.
	{
		return 1;
	}

	const int kMenuItemNum = 3;
	//tạo mảng để lưu 3 tọa độ của 3 chức năng cần sử dụng.
	SDL_Rect pos_Arr[kMenuItemNum];
	//chơi 1 vs 1.
	pos_Arr[0].x = 100;
	pos_Arr[0].y = 300;
	//chơi 1 vs may.
	pos_Arr[1].x = 100;
	pos_Arr[1].y = 500;
	//thoát game.
	pos_Arr[2].x = 100;
	pos_Arr[2].y = 400;

	TextObject text_menu[kMenuItemNum];

	//vẽ các yêu cầu lên menu.png.
	text_menu[0].SetText("Play Game: 1 vs 1");
	text_menu[0].SetColor(TextObject::BLACK_TEXT);
	text_menu[0].SetRect(pos_Arr[0].x, pos_Arr[0].y);

	text_menu[2].SetText("Play Game: 1 vs may");
	text_menu[2].SetColor(TextObject::BLACK_TEXT);
	text_menu[2].SetRect(pos_Arr[2].x, pos_Arr[2].y);

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
		for (int i = 0; i < kMenuItemNum; ++i)
		{
			text_menu[i].creatText(font, des);
		}

		while (SDL_PollEvent(&m_event))
		{
			switch (m_event.type)
			{
			case SDL_QUIT:
			{ return 1; }
			case SDL_MOUSEMOTION:
			{
				xm = m_event.motion.x;
				ym = m_event.motion.y;

				for (int i = 0; i < kMenuItemNum; i++)
				{
					if (CheckFocusWithRect(xm, ym, text_menu[i].GetRect()))		//nêu con trỏ chuột nằm trong vi trí 
					{															//của các yêu cầu thì các yêu cầu chuyển sang mau đỏ
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
			}
			break;
			case SDL_MOUSEBUTTONDOWN:
			{
				xm = m_event.button.x;
				ym = m_event.button.y;

				for (int i = 0; i < kMenuItemNum; i++)
				{
					if (CheckFocusWithRect(xm, ym, text_menu[i].GetRect()))
					{
						return i;		// return 0 là chơi với người, return 1 là chơi với máy
					}					// return 2 là exit;
				}
			}
			break;
			case SDL_KEYDOWN:
				if (m_event.key.keysym.sym == SDLK_ESCAPE)
				{
					return 1;
				}
			default:
				break;
			}
		}
		SDL_Flip(des);
	}

	return 1;
}
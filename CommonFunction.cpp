
#include "CommonFunction.h"
#include <iostream>
#include"TextObject.h"
/*
 * Function:
 * ----------------------------------
 *	Free memory

 */
void SDL_CFunction::CleanUp()
{
	SDL_FreeSurface(g_screen);
	SDL_FreeSurface(g_bkground);
}

/*
 * Function: ApplySurface
 * ----------------------------
 *	 Apply the source of surface to detination of surface
 *
 *	 scr: a pointer point to source of Surface
 *   des : a pointer point to destination of Surface
 *
 *   Return coordinates of the surface destination
 */
SDL_Rect SDL_CFunction::ApplySurface(SDL_Surface* scr, SDL_Surface* des, int x, int y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(scr, NULL, des, &offset);

	return offset;
}

/*
 * Function: CheckFocusWithRect
 * ----------------------------------
 *	x :
 *	y :
 *	rect :
 *
 *   Return
 */
bool SDL_CFunction::CheckFocusWithRect(const int &x, const int &y, const SDL_Rect& rect)
{
	if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h)
	{
		return true;
	}

	return false;
}


/*
 * Function:LoadImage
 * ----------------------------------
 *	Load the file of image
 *	file_path: the path to file on the computer including the name of the file
 *
 *   Return an SDL_Surface pointer point to the surface of the image
 */
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

/*
 * Function:ShowMenu
 * ----------------------------------
 *	Display the menu of the program when it begin
 *
 *	des: The Surface to apply image background
 *	font: the font of the text to show on screen
 *
 *   Return 0: if the user click to 2 player button
 *   Return 2: if the user click to play with PC
 *   Return 2: if this has the error or user click quit button
 *
 */

int SDL_CFunction::ShowMenu(SDL_Surface *des, TTF_Font * font)
{
	g_img_menu = LoadImage("Bkground.png");

	if (g_img_menu == NULL)
	{
		return 2;
	}
	//số chức năng chơi game.
	const int kMenuItemNum = 3;
	TextObject text_menu[kMenuItemNum];

	text_menu[0].SetText("Play Game: 1 vs 1");
	text_menu[0].SetColor(TextObject::BLACK_TEXT);
	text_menu[0].SetRect(100,300,458,60);

	text_menu[1].SetText("PLay Game: 1 vs may");
	text_menu[1].SetColor(TextObject::BLACK_TEXT);
	text_menu[1].SetRect(100,400,558,60);

	text_menu[2].SetText("EXIT GAME");
	text_menu[2].SetColor(TextObject::BLACK_TEXT);
	text_menu[2].SetRect(100,500,350,60);

	bool selected[kMenuItemNum] = { 0,0,0 };
	int xm = 0;
	int ym = 0;
	SDL_Event m_event;
	SDL_CFunction::ApplySurface(g_img_menu, des, 0, 0);
	for (int i = 0; i < kMenuItemNum; i++)
	{
		//text_menu[i].SetColor(TextObject::RED_TEXT);
		text_menu[i].creatText(font, des);
	}

	while (true)
	{
		
		while (SDL_PollEvent(&m_event))
		{
			switch (m_event.type)
			{
			case SDL_QUIT:
			{
				return 2;
			}
			case SDL_MOUSEMOTION:
			{
				xm = m_event.motion.x;
				ym = m_event.motion.y;
				std::cout <<"x =  "<<xm<<"  y =  "<< ym;
				for (int i = 0; i < kMenuItemNum; i++)
				{
					//text_menu[i].SetColor(TextObject::RED_TEXT);
					if (CheckFocusWithRect(xm, ym, text_menu[i].GetRect()))
					{
						text_menu[i].SetColor(TextObject::RED_TEXT);
						text_menu[i].creatText(font, des);
						if (selected[i] == false)
						{
							selected[i] = 1;
							text_menu[i].SetColor(TextObject::RED_TEXT);
						}
					
					}
					else
					{
						text_menu[i].SetColor(TextObject::BLACK_TEXT);
						text_menu[i].creatText(font, des);
						if (selected[i] == true)
						{
							selected[i] = 0;
							text_menu[i].SetColor(TextObject::BLACK_TEXT);
						}
					}
				}
				break;
			}

			case SDL_MOUSEBUTTONDOWN:
			{
				xm = m_event.button.x;
				ym = m_event.button.y;

				for (int i = 0; i < kMenuItemNum; i++)
				{
					if (CheckFocusWithRect(xm, ym, text_menu[i].GetRect()))
					{
						return i;
					}
				}
			}
			break;
			case SDL_KEYDOWN:
				if (m_event.key.keysym.sym == SDLK_ESCAPE)
				{
					return 2;
				}
			default:
				break;
			}
		}
		if (SDL_Flip(des) == -1) {
			return 2;
		}
	}
}
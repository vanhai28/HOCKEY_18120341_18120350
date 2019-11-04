#include "GameFunction.h"




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

int ShowMenu(SDL_Surface *des, TTF_Font * font)
{
	g_img_menu = SDL_CFunction::LoadImage("Bkground.png");

	if (g_img_menu == NULL)
	{
		return 2;
	}
	//số chức năng chơi game.
	const int kMenuItemNum = 3;
	Button button[kMenuItemNum];

	button[0].SetText("Play Game: 1 vs 1");
	button[0].SetColor(TextObject::BLACK_TEXT);
	button[0].SetRect(100, 300, 458, 60);

	button[1].SetText("PLay Game: 1 vs may");
	button[1].SetColor(TextObject::BLACK_TEXT);
	button[1].SetRect(100, 400, 558, 60);

	button[2].SetText("EXIT GAME");
	button[2].SetColor(TextObject::BLACK_TEXT);
	button[2].SetRect(100, 500, 350, 60);

	bool isClick = false;

	SDL_Event m_event;

	SDL_CFunction::ApplySurface(g_img_menu, des, 0, 0);

	for (int i = 0; i < kMenuItemNum; i++)
	{
		//button[i].SetColor(TextObject::RED_TEXT);
		button[i].creatText(font, des);
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
				for (int i = 0; i < kMenuItemNum; i++)
				{
					button[i].UpdateColorButton(m_event, des);
				}
				break;
			}

			case SDL_MOUSEBUTTONDOWN:
			{
				for (int i = 0; i < kMenuItemNum; i++)
				{
					isClick = button[i].CheckFocusWithRect(m_event.button.x, m_event.button.y, button[i].GetRect());

					if (isClick)
					{
						return i;
					}
				}
			}
			break;
			}
			if (SDL_Flip(des) == -1) {
				return 2;
			}
		}
	}


}
	
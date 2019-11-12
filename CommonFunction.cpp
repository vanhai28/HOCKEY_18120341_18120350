
#include "CommonFunction.h"
#include"TextObject.h"
#include "Button.h"



SDL_Rect SDL_CFunction::ApplySurface(SDL_Surface* scr, SDL_Surface* des, int x, int y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(scr, NULL, des, &offset);

	return offset;
}


SDL_Surface*  SDL_CFunction::LoadImage(std::string file_path) {
	SDL_Surface* load_image = NULL;
	SDL_Surface *optimize_image = NULL;

	load_image = IMG_Load(file_path.c_str());

	if (load_image != NULL)
	{
		optimize_image = SDL_DisplayFormat(load_image);
		SDL_FreeSurface(load_image);
	}

	return optimize_image;
}

int ShowMenu(SDL_Surface * g_img_menu,SDL_Surface *des, TTF_Font * font)
{
	//nếu con trỏ hình ảnh menu Null thì trả về 2 tương đương chức năng thoát chương trình
	if (g_img_menu == NULL)
	{
		return 2;
	}

	//số chức năng chơi game.
	const int kMenuItemNum = 3;
	Button button[kMenuItemNum];

	//Hàm trả về 0 khi người chơi nhấn vào button[0]
	button[0].SetText("Play Game: 1 vs 1");
	button[0].SetColor(TextObject::BLACK_TEXT);
	button[0].SetRect(300, 300, 458, 60);

	//Hàm trả về 1 khi người chơi nhấn vào button[1]
	button[1].SetText("PLay Game: 1 vs may");
	button[1].SetColor(TextObject::BLACK_TEXT);
	button[1].SetRect(300, 400, 558, 60);

	//Hàm trả về 2 khi người chơi nhấn vào button[2]
	button[2].SetText("EXIT GAME");
	button[2].SetColor(TextObject::BLACK_TEXT);
	button[2].SetRect(300, 500, 350, 60);

	bool isClick = false;
	SDL_Event m_event;
	SDL_CFunction::ApplySurface(g_img_menu, des, 0, 0);//Đặt hình nền cho menu

	//Hiển thị các button chức năng
	for (int i = 0; i < kMenuItemNum; i++)
	{
		button[i].displayText(font, des);
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
				//cập nhật màu các button chức năng khi người chơi di chuyển con trỏ chuột
				for (int i = 0; i < kMenuItemNum; i++)
				{
					button[i].UpdateColorButton(font,m_event, des);
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
						//nếu người chơi nhấn vào button thì trả về số thứ tự button
						return i;
					}
				}
			}
			break;
			}
			//cập nhật lại màn hình
			if (SDL_Flip(des) == -1) {
				return 2;
			}
		}
	}


}
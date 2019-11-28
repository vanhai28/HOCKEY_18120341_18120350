﻿
#include <iostream>
#include "Player1.h"
#include "Player2.h"
#include "AutoPlayer.h"
#include "Ball.h"
#include "Button.h"
#include "BasePlayer.h"
#include <random>
#include <time.h>
#undef main
using namespace std;

//-------------------Khai báo biến toàn cục-------------
TTF_Font * g_font_text = NULL;
TTF_Font * g_font_menu = NULL;
bool is_quit = false;
BaseObject win1, win2;
SDL_Event g_event1, g_event2;
Player1 player1;
Player2 player2;
BasePlayer *player = &player1;
Button back_button;
AutoPlayer autoPlayer;
TextObject markP1;
TextObject markP2;
int mark = 0;
int ret_menu = 0;
Ball ball;
bool is_finish_game = false;
int winner = 0;
Mix_Chunk* sound[3];
Mix_Music *music = NULL;
SDL_Surface * g_screen = NULL;
SDL_Surface * g_bkground_0 = NULL;
SDL_Surface * g_bkground_1 = NULL;
SDL_Surface * g_bkground = NULL;
SDL_Surface* g_img_menu = NULL;
SDL_Event g_event;
bool isAddMark = false;
//------------------Khai báo các hàm ------------------------------
void showWinner(SDL_Surface*& screen);
bool Init();
bool startGame();
void pause_game(SDL_Surface* screen, int& mode);
void restartGame();
void ExitGame();
void BackMenu(int &);
int ThreadGame(void * a);
//----------------------------------------------------------------

int main()
{

	if (Init() == false) {
		return 0;
	}

	if (startGame() == false)
	{
		return 0;
	}

	if (Mix_PlayingMusic() == 0)
	{
		//Play the music
		Mix_PlayMusic(music, -1);
	}

	ret_menu = ShowMenu(g_img_menu,g_screen, g_font_menu);

	if (ret_menu == 2)
	{
		is_quit = true;
	}
	if (ret_menu == 0)
	{
		g_bkground = g_bkground_0;
		mark = -1;
	}
	else {
		player = &autoPlayer;
		g_bkground = g_bkground_1;
	}

	SDL_Thread* ThreadBall;
	bool isClick = false;
	ThreadBall = SDL_CreateThread(ThreadGame, NULL);
	ball.Set_is_move(true);
	

	while (!is_quit)
	{
		SDL_CFunction::ApplySurface(g_bkground, g_screen, 0, 0);

		if (1 == ret_menu)
		{
			markP1.SetText(to_string(mark));
		}

		markP1.displayText(g_font_text, g_screen);
		markP2.displayText(g_font_text, g_screen);

		back_button.displayText(g_font_menu, g_screen);

		while (SDL_PollEvent(&g_event))
		{
			switch (g_event.type)
			{
			case SDL_MOUSEMOTION:
			{
				back_button.UpdateColorButton(g_font_menu,g_event, g_screen);
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				isClick = back_button.CheckFocusWithRect(g_event.button.x, g_event.button.y, back_button.GetRect());

				if (isClick)
				{
					// Quay lai menu
					BackMenu(ret_menu);
				}
				break;
			}
			case SDL_QUIT:
			{
				//Thoat
				is_quit = true;
				break;
			}
			}

			player2.HandleInputAction(g_event);
			player->HandleInputAction(g_event);
			
		}

		
		player->PredictDropPoint(ball.GetRect(), ball.Get_x_val(), ball.Get_y_val());
		player->HandleMove();
		player->show(g_screen);
		
		

		player2.HandleMove();
		player2.show(g_screen);

		ball.show(g_screen);

		if (is_finish_game)
		{
			showWinner(g_screen);

			if (ret_menu == 0 && !isAddMark)
			{
				markP1.SetText(to_string(player1.GetMark()));
				markP2.SetText(to_string(player2.GetMark()));
				isAddMark = true;
			}
			else if(ret_menu != 0)
			{
				int temp = stoi(markP2.GetText());

				if (mark > temp) {
					markP2.SetText(to_string(mark));
				}
				else
				{
					mark = 0;
				}
			}

			pause_game(g_screen, ret_menu);
		}

		if (SDL_Flip(g_screen) == -1) {
			return 0;
		}
	}
	SDL_WaitThread(ThreadBall,NULL);
	ExitGame();

	return 0;
}

// Tên hàm 	: Init
// Mô tả	: Khởi tạo các giá trị ban đầu
// Kiểu trả về  : bool : true nếu tất cả quá trình khởi tạo thành công
//						 false : nếu có bất cứ lỗi nào phát sinh
bool Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cerr << "SDL_Init() Failed: " <<
			SDL_GetError() << endl;
		return false;
	}

	SDL_WM_SetCaption("HOCKEY", "icon");
	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_SWSURFACE | SDL_DOUBLEBUF);

	if (g_screen == NULL) {
		return false;
	}
	//Khởi động font API
	if (TTF_Init() < 0)
	{
		cout << "Loi khoi tao TTF:" << TTF_GetError();
		return false;
	}

	// Khởi tạo để tải âm thanh
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		return false;
	}

	//----Khởi gán các giá trị ban đầu-------------
	sound[0] = Mix_LoadWAV("Music\\winSound.wav");
	sound[1] = Mix_LoadWAV("Music\\lose.wav");
	sound[2] = Mix_LoadWAV("Music\\ballSound.wav");

	music = Mix_LoadMUS("Music\\Vexento - We Are One (Original).mp3");

	if ( music == NULL )
	{
		cout << "cannot open file audio\n";
		return false;
	}

	markP1.SetColor(TextObject::RED_TEXT);
	markP1.SetRect(550, 200);
	markP1.SetText("0");

	markP2.SetColor(TextObject::RED_TEXT);
	markP2.SetRect(750, 200);
	markP2.SetText("0");
	//-----------------------------------------------

	return true;
}

// Tên hàm 	: startGame
// Mô tả	: Khởi gán các biến cần thiết cho chương trình
// Kiểu trả về  : bool 
bool startGame()
{
	bool checkLoadImg = false;

	//---------Khởi gán và tải các hình ảnh cần thiết-----------
	win1.SetRect(50, 100);
	checkLoadImg = win1.LoadImg("Photo\\player1win.png");
	if (checkLoadImg == false) {
		return false;
	}

	win2.SetRect(50, 100);
	checkLoadImg = win2.LoadImg("Photo\\player2win.png");
	if (checkLoadImg == false) {
		return false;
	}

	ball.SetRect(400, 300);
	checkLoadImg = ball.LoadImg("Photo\\Ball.png");

	if (checkLoadImg == false) {
		return false;
	}

	player1.SetRect(X_PLAYER, Y_PLAYER);
	checkLoadImg = player1.LoadImg("Photo\\player1.png");

	if (checkLoadImg == false) {
		return false;
	}

	player2.SetRect(X_PLAYER_2, Y_PLAYER_2);
	checkLoadImg = player2.LoadImg("Photo\\player2.png");

	if (checkLoadImg == false) {
		return false;
	}

	autoPlayer.SetRect(X_PLAYER, Y_PLAYER);
	checkLoadImg = autoPlayer.LoadImg("Photo\\player1.png");

	if (checkLoadImg == false) {
		return false;
	}

	//-------Tải hình nền ----------------------------
	g_bkground_0 = SDL_CFunction::LoadImage("Photo\\Bkground.png");
	g_bkground_1 = SDL_CFunction::LoadImage("Photo\\Bkground2.png");
	g_img_menu = SDL_CFunction::LoadImage("Photo\\menu.png");

	if (g_bkground_0 == NULL || g_bkground_1 == NULL|| g_img_menu== NULL) {
		cout << "Cannot load background!!" << endl;
		return false;
	}

	//----------Khởi tạo fone chữ -------------------
	g_font_text = TTF_OpenFont("comic.ttf", 70);
	g_font_menu = TTF_OpenFont("comic.ttf", 40);
	if (g_font_text == NULL)
	{
		return false;
	}

	//----------Khởi tạo vị trí nút back ------------
	back_button.SetRect(730, 620, 100, 60);
	back_button.SetText("Back");

	return true;
}

//-----------------------------------------------------------------------------------
// Tên hàm 	: pause_game
// Mô tả	: Dừng trò chơi và chờ thao tác của ngươi chơi khi kết thúc một lượt chơi
// Kiểu trả về  : void
// Tham số SDL_Surface*& screen : Biến trỏ đến cửa sổ người chơi
// Tham số int& mode : Chế độ chơi (chơi với máy hay 2 người chơi )
void pause_game(SDL_Surface*screen, int& mode)
{
	//-------- Dừng di chuyển thanh trượt và quả bóng --------
	ball.Set_is_move(false);
	player->SetIsMove(false);
	player2.SetIsMove(false);
	

	while (!is_quit)
	{
		while (SDL_PollEvent(&g_event))
		{
			switch (g_event.type)
			{
			case SDL_MOUSEMOTION:
			{
				back_button.UpdateColorButton(g_font_menu,g_event, g_screen);

				if (SDL_Flip(g_screen) == -1) {
					return;
				}
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				bool isClick = back_button.CheckFocusWithRect(g_event.button.x, g_event.button.y, back_button.GetRect());
				if (isClick)
				{
					BackMenu(mode);
					return;
				}
				break;
			}
			case SDL_QUIT:
			{
				// Thoat
				is_quit = true;
				return;
			}
			case SDL_KEYDOWN:
			{
				switch (g_event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
				{
					// Thoat
					is_quit = true;
					return;
				}
				case SDLK_SPACE:
				{
					//Chơi lại
					is_finish_game = false;
					restartGame();
					return;
				}
				}
			}
			}
		}
	}
}


// Tên hàm 	: showWinner
// Mô tả	:  Thông báo người chơi chiến thắng
// Kiểu trả về : void 
// Tham số SDL_Surface*& screen : Biến trỏ đến cửa sổ chương trình
void showWinner(SDL_Surface*& screen)
{
	if (winner == 1)// Người chơi 1 thắng
	{
		player->SetMark(player1.GetMark() + 1);
		win1.show(screen);
	}
	else // Người chơi 2 thắng
	{
		player2.SetMark(player2.GetMark() + 1);
		win2.show(screen);
	}
	if (SDL_Flip(screen) == -1) {
		return;
	}
}



// Tên hàm 	: restartGame
// Mô tả	: Khởi gán lại các giá trị ban đầu 
// Kiểu trả về  : void
void restartGame()
{
	//khởi tại lại vị trí ban đầu của thanh trượt và bóng
	player2.SetRect(X_PLAYER_2, Y_PLAYER_2);
	player->SetRect(X_PLAYER, Y_PLAYER);
	ball.SetRect(250, 350);

	// Tạo giá trị ngẫu nhiên cho x_val và y_val
	int x = 0, y = 0;
	std::random_device random_device;
	std::mt19937 random_engine(random_device());
	std::uniform_int_distribution<int> distribution(-5, 0);
	
	do {
		x = distribution(random_engine);
		y = distribution(random_engine);
		ball.Set_x_val(x);
		ball.Set_y_val(y);
	} while (x == 0 || y == 0);

	ball.Set_is_move(true);
	player1.SetIsMove(true);
	player2.SetIsMove(true);
	mark = 0;
	
	is_finish_game = false;
	isAddMark = false;
}



// Tên hàm 	: ThreadGame
// Mô tả	: Sử dụng khi tạo một thread khác cho đối tượng bóng
// Kiểu trả về  : int
// Tham số void *a : Đặt cho đúng cú pháp câu lệnh, thực tế biến này không được sử dụng
int ThreadGame(void *a)
{
	while (!is_quit)
	{
		if (ball.Get_is_move())
		{
			int t = ball.Get_speed();
			SDL_Delay(20-t);
			winner = ball.HandleMove(player->GetRect(), player2.GetRect(), is_finish_game,sound, mark);
		}
	}
	return 0;
}



// Tên hàm 	: ExitGame
// Mô tả	: Đóng các khởi tạo ban đầu, thu hồi bộ nhớ
// Kiểu trả về  : void
void ExitGame()
{
	SDL_FreeSurface(g_screen);
	SDL_FreeSurface(g_img_menu);
	SDL_FreeSurface(g_bkground_0);
	SDL_FreeSurface(g_bkground_1);

	g_bkground = g_bkground_0 = g_bkground_1 = NULL;

	for (int i = 0; i < 3; i++)
	{
		Mix_FreeChunk(sound[i]);
	}

	Mix_CloseAudio();
	TTF_CloseFont(g_font_text);
	TTF_CloseFont(g_font_menu);
	Mix_FreeMusic(music);
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
	return;
}



// Tên hàm 	: BackMenu
// Mô tả	: Quay lại màn hình menu
// Kiểu trả về  : void
// Tham số int& old_mod : Chế độ chơi cũ, dùng để xác định khi người chơi chọn chế độ chơi mới 
void BackMenu(int& old_mod)
{
	ball.Set_is_move(false);

	int curren_mode = ShowMenu(g_img_menu,g_screen, g_font_menu);

	if (old_mod == curren_mode)
	{
		// tiếp túc chế độ chơi cũ
	}
	else if (curren_mode == 2)
	{
		//Thoat chương trình
		is_quit = true;
	}
	else
	{
		//---------- Chọn chế độ chơi mới ----------
		// Đặt lại điểm người chơi
		player->SetMark(0);
		player2.SetMark(0);

		markP1.SetText("0");
		markP2.SetText("0");

		if (curren_mode == 0)
		{
			player1.SetMark(0);
			player2.SetMark(0);
			g_bkground = g_bkground_0;
			player = &player1;
		}
		else 
		{
			g_bkground = g_bkground_1;
			player = &autoPlayer;
			mark = 0;
		}
	
		old_mod = curren_mode;
		restartGame();
		//ret_menu = curren_mode;
	}

	back_button.SetColor(TextObject::BLACK_TEXT);
	//Bật trạng thái cho quả bóng chạy
	ball.Set_is_move(true);
}
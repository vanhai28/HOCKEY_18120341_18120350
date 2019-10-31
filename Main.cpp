
#include <iostream>
#include "Player1.h"
#include "Player2.h"
#include "AutoPlayer.h"
#include "Ball.h"
#include "Button.h"

#undef main
using namespace std;

//------------------- GLOBAL VARIABLE -------------
TTF_Font * g_font_text = NULL;
bool is_quit = false;
BaseObject win1, win2;
SDL_Event g_event1, g_event2;
Player1 player1;
Player2 player2;
Button back_button;
AutoPlayer autoPlayer;

PLAYER * player = &autoPlayer;
TextObject markP1;
TextObject markP2;
int mark = 0;
int ret_menu = 0;
Ball ball;
bool is_finish_game = false;
int winner = 0;
//------------------------------------------------
void showWinner(SDL_Surface*& screen);
bool Init();
bool startGame();
void pause_game(SDL_Surface*& screen, int& mode);
void restartGame();
void ExitGame();
void BackMenu(int &);
int ThreadGame(void * a);
Mix_Music *music = NULL;


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
	ret_menu = ShowMenu(g_screen, g_font_text);

	if (ret_menu == 2)
	{
		is_quit = true;
	}
	if (ret_menu == 0)
	{
		g_bkground = SDL_CFunction::LoadImage("Bkground.png");
		player = &player1;
		mark = -1;
	}
	SDL_Thread* thread0;
	bool isClick = false;
	int * value = NULL;
	thread0 = SDL_CreateThread(ThreadGame, NULL);
	ball.Set_is_move(true);

	TTF_Font *mark_font = TTF_OpenFont("comic.ttf", 70);

	while (!is_quit)
	{
		
		SDL_CFunction::ApplySurface(g_bkground, g_screen, 0, 0);

		if (1 == ret_menu)
		{
			markP1.SetText(to_string(mark));

		}

		markP1.creatText(mark_font, g_screen);
		markP2.creatText(mark_font, g_screen);

		back_button.creatText(g_font_text, g_screen);

		while (SDL_PollEvent(&g_event))
		{
			switch (g_event.type)
			{
			case SDL_MOUSEMOTION:
			{
				back_button.UpdateColorButton(g_event, g_screen);
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				isClick = back_button.CheckFocusWithRect(g_event.button.x, g_event.button.y, back_button.GetRect());

				if (isClick)
				{
					BackMenu(ret_menu);
				}
				break;
			}
			case SDL_QUIT:
			{
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

			if (ret_menu == 0)
			{
				markP1.SetText(to_string(player->GetMark()));
				markP2.SetText(to_string(player2.GetMark()));
			}
			else
			{
				int temp = stoi(markP2.GetText());

				if (mark > temp) {
					markP2.SetText(to_string(mark));
				}
				else mark = 0;
			}

			pause_game(g_screen, ret_menu);

			is_finish_game = false;
		}

		if (SDL_Flip(g_screen) == -1) {
			return 0;
		}
	}

	SDL_WaitThread(thread0, value);
	TTF_CloseFont(mark_font);
	ExitGame();

	return 0;
}

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
	//Initialize the truetype font API.
	if (TTF_Init() < 0)
	{
		cout << "Loi khoi tao TTF:" << TTF_GetError();
		return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		return false;
	}

	g_sound_player1 = Mix_LoadWAV("palyer2.wav");
	win = Mix_LoadWAV("winSound.wav");

	music = Mix_LoadMUS("Vexento - We Are One (Original).mp3");


	if (g_sound_player1 == NULL || music == NULL || win == NULL)
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



	return true;
}

bool startGame()
{
	bool checkLoadImg = false;
	win1.SetRect(100, 100);

	checkLoadImg = win1.LoadImg("player1win.png");
	if (checkLoadImg == false) {
		return false;
	}

	win2.SetRect(100, 100);

	checkLoadImg = win2.LoadImg("player2win.png");
	if (checkLoadImg == false) {
		return false;
	}

	ball.SetRect(400, 300);
	checkLoadImg = ball.LoadImg("Ball.png");

	if (checkLoadImg == false) {
		return false;
	}

	player1.SetRect(X_PLAYER, Y_PLAYER);
	checkLoadImg = player1.LoadImg("player1.png");

	if (checkLoadImg == false) {
		return false;
	}

	player2.SetRect(X_PLAYER_2, Y_PLAYER_2);

	checkLoadImg = player2.LoadImg("player2.png");

	if (checkLoadImg == false) {
		return false;
	}
	autoPlayer.SetRect(X_PLAYER, Y_PLAYER);

	checkLoadImg = autoPlayer.LoadImg("player1.png");

	if (checkLoadImg == false) {
		return false;
	}

	g_bkground = SDL_CFunction::LoadImage("Bkground2.png");
	if (g_bkground == NULL) {
		return false;
	}
	g_font_text = TTF_OpenFont("comic.ttf", 40);
	if (g_font_text == NULL)
	{
		return false;
	}

	back_button.SetRect(600, 600, 100, 60);
	back_button.SetText("Back");

	return true;
}

void pause_game(SDL_Surface*& screen, int& mode)
{

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
				back_button.UpdateColorButton(g_event, g_screen);

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
				is_quit = true;
				break;
			}
			case SDL_KEYDOWN:
			{
				switch (g_event.key.keysym.sym)
				{

				case SDLK_ESCAPE:
				{
					is_quit = true;
					return;
				}
				case SDLK_BACKSPACE:
				{
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


void showWinner(SDL_Surface*& screen)
{
	if (winner == 1) {
		player->SetMark(player->GetMark() + 1);
		win1.show(screen);
	}
	else {
		player2.SetMark(player2.GetMark() + 1);
		win2.show(screen);
	}
	if (SDL_Flip(screen) == -1) {
		return;
	}
}


void restartGame()
{
	player2.SetRect(X_PLAYER_2, Y_PLAYER_2);
	player1.SetRect(X_PLAYER, Y_PLAYER);

	ball.SetRect(400, 300);
	ball.Set_x_val(3);
	ball.Set_y_val(3);

	ball.Set_is_move(true);
	player->SetIsMove(true);
	player2.SetIsMove(true);

	if (1 == ret_menu)
	{
		g_bkground = SDL_CFunction::LoadImage("Bkground2.png");
		mark = 0;
	}
	else
	{
		g_bkground = SDL_CFunction::LoadImage("Bkground.png");
		mark = -1;
	}
}


int ThreadGame(void *a)
{
	while (!is_quit)
	{
		if (ball.Get_is_move())
		{
			SDL_Delay(20);
			ball.HandleMove(player->GetRect(), player2.GetRect(), is_finish_game, winner, g_sound_player1, mark);
		}
	}
	return 0;
}


void ExitGame()
{
	SDL_CFunction::CleanUp();
	SDL_Quit();
	TTF_Quit();

	TTF_CloseFont(g_font_text);
	

	Mix_FreeChunk(g_sound_player1);
	Mix_FreeChunk(win);
	Mix_FreeMusic(music);
	Mix_Quit();
	exit(1);
}


void BackMenu(int& old_mod)
{
	ball.Set_is_move(false);

	int mode_play = ShowMenu(g_screen, g_font_text);

	if (old_mod == mode_play)
	{
		// continue game
	}
	else if (mode_play == 2)
	{
		is_quit = true;
	}
	else
	{
		player->SetMark(0);
		player2.SetMark(0);

		markP1.SetText("0");
		markP2.SetText("0");

		if (mode_play == 0) {
			old_mod = mode_play;
			player = &player1;

			restartGame();
		}
		else {
			old_mod = mode_play;
			player = &autoPlayer;
			restartGame();
			mark = 0;
		}
		ret_menu = mode_play;
	}

	ball.Set_is_move(true);
}

#include <SDL.h>
#include "CommonFunction.h"
#include <SDL_ttf.h>
#include <iostream>
#include "BaseObject.h"
#include "Player1.h"
#include "Player2.h"
#include "Ball.h"
#include "TextObject.h"
#include <SDL_mixer.h>

#undef main
using namespace std;

//------------------- GLOBAL VARIABLE -------------
TTF_Font * g_font_text = NULL;
bool is_quit = false;
BaseObject win1, win2;
SDL_Event g_event1, g_event2;
Player1 player1;
Player2 player2;
Ball ball;
bool is_finish_game = false;
int winner = 0;
//------------------------------------------------
void showWinner(SDL_Surface*& screen);
bool Init();
bool startGame();
void pause_game(SDL_Surface*& screen);
void restartGame(); 
void ExitGame();

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
	TextObject text_object;
	text_object.SetRect(400, 400);
	text_object.SetColor(TextObject::BLACK_TEXT);
	text_object.SetText("in cho vui");
	text_object.creatText(g_font_text, g_screen);
	int ret_menu = SDL_CFunction::ShowMenu(g_screen, g_font_text);

	if (ret_menu == 1)
	{
		is_quit = true;
	}

	while (!is_quit)
	{
		
		if (Mix_PlayingMusic() == 0)
		{
			//Play the music
			Mix_PlayMusic(music, -1);
		}

		SDL_CFunction::ApplySurface(g_bkground, g_screen, 0, 0);
		//Mix_PlayChannel(-1, g_sound_player1, 0);
		while (SDL_PollEvent(&g_event))
		{
			if (g_event.type == SDL_QUIT) {
				is_quit = true;
				break;
			}

			if (g_event.type == SDL_KEYDOWN)
			{
				switch (g_event.key.keysym.sym)
					{
					case SDLK_SPACE:
					{
						pause_game(g_screen);
					}
					case SDLK_n:
					{
						
					}
				}
			}

			player2.HandleInputAction(g_event);
			player1.HandleInputAction(g_event);
		}

		player1.HandleMove();
		player1.show(g_screen);

		player2.HandleMove();
		player2.show(g_screen);

		ball.HandleMove(player1.GetRect(), player2.GetRect(), is_finish_game, winner,g_sound_player1);
		ball.show(g_screen);
	
		if(is_finish_game)
		{
			showWinner(g_screen);
			pause_game(g_screen);
		}

		if (SDL_Flip(g_screen) == -1) {
			return 0;
		}
	}
	ExitGame();
	
	Mix_FreeChunk(g_sound_player1);
	Mix_FreeChunk(win);
	Mix_FreeMusic(music);
	Mix_Quit();
	return 0;
}

bool Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING|| SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1) {
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
		cout<<"Loi khoi tao TTF:"<< TTF_GetError();
		return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		return false;
	}

	g_sound_player1 = Mix_LoadWAV("palyer2.wav");
	win = Mix_LoadWAV("winSound.wav");

	music = Mix_LoadMUS("Vexento - We Are One (Original).mp3");
	

	if ( g_sound_player1 == NULL || music == NULL|| win == NULL)
	{
		cout << "cannot open file audio\n";
		return false;
	}

	return true;
}

bool startGame()
{
	win1.SetRect(100, 100);
	bool load = win1.LoadImg("player1win.png");
	if (load == false) {
		return false;
	}
	win2.SetRect(100, 100);
	load = win2.LoadImg("player2win.png");
	if (load == false) {
		return false;
	}

	ball.SetRect(400, 300);
	bool loadImage_ball = ball.LoadImg("Ball.png");

	if (loadImage_ball == false) {
		return false;
	}

	player1.SetRect(X_PLAYER_1, Y_PLAYER_1);
	bool loadImage = player1.LoadImg("player1.png");

	if (loadImage == false) {
		return false;
	}

	player2.SetRect(X_PLAYER_2, Y_PLAYER_2);

	bool loadImage2 = player2.LoadImg("player1.png");

	if (loadImage2 == false) {
		return false;
	}

	g_bkground = SDL_CFunction::LoadImage("Bkground.png");
	if (g_bkground == NULL) {
		return false;
	}
	g_font_text = TTF_OpenFont("comic.ttf", 60);
	if (g_font_text == NULL)
	{
		return false;
	}
	return true;
}

void pause_game(SDL_Surface*& screen)
{
	while (!is_quit)
	{
		while (SDL_PollEvent(&g_event))
		{
			if (g_event.type == SDL_QUIT) {
				is_quit = true;
				break;
			}
			if (g_event.type == SDL_KEYDOWN)
			{
				switch (g_event.key.keysym.sym)
					{
					case SDLK_SPACE:
					{
						exit(1);
					}
					default:
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
void showWinner(SDL_Surface*& screen)
{
	if (winner == 1) {
		win1.show(screen);
	}
	else {
		win2.show(screen);
	}
	if (SDL_Flip(screen) == -1) {
		return;
	}
}
void restartGame()
{
	player2.SetRect(X_PLAYER_2, Y_PLAYER_2);
	player1.SetRect(X_PLAYER_1, Y_PLAYER_1);
	ball.SetRect(400, 300);
	ball.Set_x_val(3);
	ball.Set_y_val(3);
}

void ExitGame()
{
	SDL_CFunction::CleanUp();
	SDL_Quit();
	TTF_Quit();
	exit(1);
}
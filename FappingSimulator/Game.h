#pragma once
#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )
#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

#include "Entity.h"

#define WINDOW_WIDTH	1024
#define WINDOW_HEIGHT	768

#define MAX_KEYS		256

class Game
{
public:
	Game();
	~Game();

	bool Init();
	void Release();

	bool Input();
	bool Update();
	void Draw();

private:
	SDL_Window* Window;
	SDL_Renderer* Renderer;
	SDL_Surface* image;
	SDL_Texture* barf_texture;
	SDL_Texture* bars_texture;
	SDL_Texture* background_texture;
	SDL_Texture* character_texture;
	SDL_Texture* win_texture;

	Entity BarFrame, BarSquare;

	enum KEY_STATE { KEY_IDLE, KEY_DOWN, KEY_REPEAT, KEY_UP };
	KEY_STATE keys[MAX_KEYS];
};

#include "Game.h"

Game::Game() {}
Game::~Game() {}

bool Game::Init()
{
	//Initialize SDL with all subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	//Create our window: title, x, y, w, h, flags
	Window = SDL_CreateWindow("Fapping Simulator, B THE FA(P)STEST!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (Window == NULL)
	{
		SDL_Log("Unable to create window: %s", SDL_GetError());
		return false;
	}
	//Create a 2D rendering context for a window: window, device index, flags
	Renderer = SDL_CreateRenderer(Window, -1, 0);
	if (Renderer == NULL)
	{
		SDL_Log("Unable to create rendering context: %s", SDL_GetError());
		return false;
	}

	//Init variables
	BarFrame.Init(162, 600, 700, 100, 5);
	BarSquare.Init(170, 615, 130, 56, 10);
	
	IMG_Init(IMG_INIT_PNG);
	image = IMG_Load("bar.png");
	barf_texture = SDL_CreateTextureFromSurface(Renderer, image);
	SDL_FreeSurface(image);

	IMG_Init(IMG_INIT_PNG);
	image = IMG_Load("Ricardito.png");
	bars_texture = SDL_CreateTextureFromSurface(Renderer, image);
	SDL_FreeSurface(image);

	IMG_Init(IMG_INIT_PNG);
	image = IMG_Load("background.png");
	background_texture = SDL_CreateTextureFromSurface(Renderer, image);
	SDL_FreeSurface(image);

	IMG_Init(IMG_INIT_PNG);
	image = IMG_Load("win.png");
	win_texture = SDL_CreateTextureFromSurface(Renderer, image);
	SDL_FreeSurface(image);
	return true;
}

bool Game::Input()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)	return false;
	}

	SDL_PumpEvents();
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);
	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keyboard[i])
			keys[i] = (keys[i] == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
		else
			keys[i] = (keys[i] == KEY_REPEAT || keys[i] == KEY_DOWN) ? KEY_UP : KEY_IDLE;
	}
	return true;
}
bool Game::Update()
{
	//Read Input
	if (!Input())	return true;

	//Process Input
	int fx = 0, fy = 0, ffx = -1;//counter-move
	if (keys[SDL_SCANCODE_ESCAPE] == KEY_DOWN)	return true;
	if (keys[SDL_SCANCODE_SPACE] == KEY_DOWN) 
	{
		fx = 10;
		int x, y, w, h;
		BarSquare.GetRect(&x, &y, &w, &h);

	}
	
	//Logic
	//win
	if (BarSquare.GetX() > 687) {
		SDL_Rect rc;
		rc = { 200, 20, 600, 400 };
		SDL_RenderCopy(Renderer, win_texture, NULL, &rc);
		SDL_RenderPresent(Renderer);
		SDL_Delay(3000);
		BarSquare.Move(-51, 0);
	}
	//Player update
	if (BarSquare.GetX() > 170) {
		BarSquare.Move(ffx, fy);
	}
	if (BarSquare.GetX()<700 && BarSquare.GetX() > 169) {
		BarSquare.Move(fx, fy);
	}
	

	return false;
}
void Game::Release()
{
	SDL_DestroyTexture(background_texture);
	SDL_DestroyTexture(barf_texture);
	SDL_DestroyTexture(bars_texture);
	SDL_DestroyTexture(win_texture);
	//Clean up all SDL initialized subsystems
	SDL_Quit();
}

void Game::Draw()
{
	SDL_Rect rc;

	rc = { 0, 0, 1024, 768 };
	SDL_RenderCopy(Renderer, background_texture, NULL, &rc);
	//Draw player
	BarSquare.GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
	SDL_RenderCopy(Renderer, bars_texture, NULL, &rc);//square
	BarFrame.GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
	SDL_RenderCopy(Renderer, barf_texture, NULL, &rc);//frame


	//Update screen
	SDL_RenderPresent(Renderer);

	SDL_Delay(10);	// 1000/10 = 100 fps max
}
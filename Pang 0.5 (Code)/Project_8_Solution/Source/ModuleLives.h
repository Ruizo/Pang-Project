#ifndef __MODULELIVES_H__
#define __MODULELIVES_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class Lives : public Module
{
public:
	//Constructor
	Lives(bool startEnabled);

	//Destructor
	~Lives();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;

	iPoint position;
};

#endif
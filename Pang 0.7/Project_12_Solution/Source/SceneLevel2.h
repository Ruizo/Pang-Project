#ifndef __SCENE_LEVEL2_H__
#define __SCENE_LEVEL2_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneLevel2 : public Module
{
public:
	//Constructor
	SceneLevel2(bool startEnabled);

	//Destructor
	~SceneLevel2();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	// Disables the player and the enemies
	bool CleanUp();

public:

	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;

	int scoreFont = -1;
	char scoreText[10] = { "\0" };
};

#endif

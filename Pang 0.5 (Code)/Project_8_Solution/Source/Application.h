#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 16

class Module;
class ModuleWindow;//0
class ModuleInput;//1
class ModuleTextures;//2
class ModuleAudio;//3
class ModulePlayer;
class ScenePreIntro;
class SceneIntro;
class worldMap;
class SceneLevel1;
class SceneWin;
class SceneOver;
class ModuleParticles;
class ModuleCollisions;
class ModuleEnemies;
class ModuleFadeToBlack;
class ModuleRender;


class Application
{

public:

	//Constructor. Creates all necessary modules for the application
	Application();

	//Destructor. Removes all module objects
	~Application();

	//Initializes all modules
	bool Init();

	//Updates all modules (PreUpdate, Update and PostUpdate)
	Update_Status Update();

	//Releases all the application data
	bool CleanUp();

public:
	// An array to store all modules
	Module* modules[NUM_MODULES];

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;

	
	ModuleTextures* textures = nullptr;
	ModuleAudio* audio = nullptr;

	ModulePlayer* player = nullptr;

	ScenePreIntro* scenepreintro = nullptr;
	SceneIntro* sceneIntro = nullptr;
	worldMap* WorldMap = nullptr;
	SceneLevel1* sceneLevel_1 = nullptr;


	SceneWin* sceneWin = nullptr;
	SceneOver* sceneOver = nullptr;

	ModuleEnemies* enemies = nullptr;
	ModuleParticles* particles = nullptr;

	ModuleCollisions* collisions = nullptr;
	ModuleFadeToBlack* fade = nullptr;

	ModuleRender* render = nullptr;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__
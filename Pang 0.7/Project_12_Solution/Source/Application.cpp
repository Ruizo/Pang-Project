#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include"ScenePreIntro.h"
#include "SceneIntro.h"
#include "worldMap.h"
#include "SceneWin.h"
#include "death.h"
#include "SceneOver.h"


#include "SceneLevel1.h"
#include "SceneLevel2.h"
#include "SceneLevel3.h"
#include "SceneLevel4.h"
#include "SceneLevel5.h"
#include "SceneLevel6.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleDebugInfo.h"
#include "ModuleBoosters.h"
#include "ModuleFonts.h"
#include "ModuleRender.h"
#include "Vulcan.h"
#include "PowerWire.h"

Application::Application()
{
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen

	modules[0] =	window =		new ModuleWindow(true);
	modules[1] =	input =			new ModuleInput(true);
	modules[2] =	textures =		new ModuleTextures(true);
	modules[3] =	audio =			new ModuleAudio(true);

	modules[4] =	scenePreIntro =	new ScenePreIntro(false);
	modules[5] =    sceneIntro =    new SceneIntro(false);
	modules[6] =    WorldMap =      new worldMap(false);
	modules[7] =    sceneLevel_1 =  new SceneLevel1(false);
	modules[8] =    sceneLevel_2 =  new SceneLevel2(false);
	modules[9] =    sceneLevel_3 =  new SceneLevel3(false);
	modules[10] =   sceneLevel_4 =  new SceneLevel4(true);
	modules[11] =   sceneLevel_5 =  new SceneLevel5(false);
	modules[12] =   sceneLevel_6 =  new SceneLevel6(false);	//Gameplay scene starts disabled
	modules[13] = death = new Death(false);
	modules[14] =   sceneOver =     new SceneOver(false);
	modules[15] = sceneWin = new SceneWin(false);
	modules[16] =	player =		new ModulePlayer(false);	//Player starts disabled
	modules[17] =	particles =		new ModuleParticles(true);
	modules[18] =	enemies =		new ModuleEnemies(false);	//Enemies start disabled

	modules[19] =	collisions =	new ModuleCollisions(true);
	modules[20] =	fade =			new ModuleFadeToBlack(true);
	modules[21] =	fonts =			new ModuleFonts(true);
	modules[22]	=	debugInfo =		new ModuleDebugInfo(true);
	modules[23] = Boosters =		new ModuleBoosters(false);
	modules[24] = vulcanB =			new Vulcan(false);
	modules[25] = powerwireB =		new PowerWire(false);
	modules[26] =	render =		new ModuleRender(true);
}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		//Important: when deleting a pointer, set it to nullptr afterwards
		//It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;

	// All modules (active and disabled) will be initialized
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Init();

	// Only active modules will be 'started'
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

Update_Status Application::Update()
{
	Update_Status ret = Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : Update_Status::UPDATE_CONTINUE;

	return ret;
}
 
bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;

	return ret;
}

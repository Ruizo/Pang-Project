#ifndef __MODULE_BOOSTERS_H__
#define __MODULE_BOOSTERS_H__

#include "Module.h"

#define MAX_BOOSTERS 100

enum class Booster_Type
{
	NO_TYPE,
	DOUBLEWIRE,
	INVINCIBLE,
	STOPTIME,
	SLOWTIME, 
	VULCAN,
	POWERWIRE,
	DYNAMITE,

};

struct BoosterSpawnpoint
{
	Booster_Type type = Booster_Type::NO_TYPE;
	int x, y;
};

class Booster;
struct SDL_Texture;

class ModuleBoosters : public Module
{
public:
	// Constructor
	ModuleBoosters(bool startEnabled);

	// Destructor
	~ModuleBoosters();

	// Called when the module is activated
	// Loads the necessary textures for the Boosters
	bool Start() override;

	// Called at the middle of the application loop
	// Handles all Boosters logic and spawning/despawning
	Update_Status Update() override;

	// Called at the end of the application loop
	// Iterates all the Boosters and draws them
	Update_Status PostUpdate() override;

	// Called on application exit
	// Destroys all active Boosters left in the array
	bool CleanUp() override;

	// Called when an enemi collider hits another collider
	// The Booster is destroyed and an explosion particle is fired
	void OnCollision(Collider* c1, Collider* c2) override;

	// Add an Booster into the queue to be spawned later
	bool AddBooster(Booster_Type type, int x, int y);

	// Iterates the queue and checks for camera position
	void HandleBoostersSpawn();

	// Destroys any Boosters that have moved outside the camera limits
	void HandleBoostersDespawn();

	//
	bool surface = false;

	int c = 0;

	bool stoptime = false;

	bool slowtime = false;


	int tempSt = 0;
	int tempSl = 0;


private:
	// Spawns a new Booster using the data from the queue
	void SpawnBooster(const BoosterSpawnpoint& info);

private:
	// A queue with all spawn points information
	BoosterSpawnpoint spawnQueue[MAX_BOOSTERS];

	// All spawned Boosters in the scene
	Booster* Boosters[MAX_BOOSTERS] = { nullptr };

	// The Boosters sprite sheet
	SDL_Texture* texture = nullptr;

	// The audio fx for destroying an Booster
	int BoosterDestroyedFx = 0;
};

#endif // __MODULE_Boosters_H__

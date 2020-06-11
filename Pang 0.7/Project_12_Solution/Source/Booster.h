#ifndef __BOOSTER_H__
#define __BOOSTER_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Booster
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Booster(int x, int y);

	// Destructor
	virtual ~Booster();

	// Returns the Booster's collider
	const Collider* GetCollider() const;

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModuleEnemies' Update
	virtual void Draw();

	// Collision response
	// Triggers an animation and a sound fx
	virtual void OnCollision(Collider* collider);

public:

	float grav = 0.1f;

	float B_Vy = 0.05f;

	float B_Vx = 1.0f;

	int posy = position.y;


	// The current position in the world
	iPoint position;

	// The Booster's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	// The Booster's collider
	Collider* collider = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;
};

#endif // __Booster_H__

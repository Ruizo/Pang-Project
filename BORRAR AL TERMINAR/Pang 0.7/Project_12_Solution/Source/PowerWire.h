#ifndef __POWERWIRE_H__
#define __POWERWIRE_H__

#include "Module.h"

#include "Globals.h"
#include "PowerWireP.h"
#include "Collider.h"

#define MAX_ACTIVE_PARTICLES 100

struct SDL_Texture;
struct Collider;

class PowerWire : public Module
{
public:
	// Constructor
	// Initializes all the particles in the array to nullptr
	PowerWire(bool startEnabled);

	//Destructor
	~PowerWire();

	// Called when the module is activated
	// Loads the necessary textures for the particles
	bool Start() override;

	// Called at the beginning of the application loop
	// Removes all particles pending to delete
	Update_Status PreUpdate() override;

	// Called at the middle of the application loop
	// Iterates all the particles and calls its Update()
	// Removes any "dead" particles
	Update_Status Update() override;

	// Called at the end of the application loop
	// Iterates all the particles and draws them
	Update_Status PostUpdate() override;

	// Called on application exit
	// Destroys all active particles left in the array
	bool CleanUp() override;

	// Called when a particle collider hits another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	// Creates a new particle and adds it to the array
	// Param particle	- A template particle from which the new particle will be created
	// Param x, y		- Position x,y in the screen (upper left axis)
	// Param delay		- Delay time from the moment the function is called until the particle is displayed in screen
	PowerWireP* AddParticle(const PowerWireP& particle, int x, int y, Collider::Type colliderType = Collider::Type::NONE, uint delay = 0);

	inline uint GetParticlesCount() const { return particlesCount; };

public:
	//Template particle for an explosion
	PowerWireP explosion;

	//Template particle for a laser
	PowerWireP powerwire;

	bool yes = false;

	Animation* currentAnimation = nullptr;
	Animation idleAnim;

private:
	// Particles spritesheet loaded into an SDL Texture
	SDL_Texture* texture = nullptr;

	// An array to store and handle all the particles
	PowerWireP* particles[MAX_ACTIVE_PARTICLES] = { nullptr };

	// Total amount of particles laoded into the array
	uint particlesCount = 0;
};

#endif // !__PowerWire_H__

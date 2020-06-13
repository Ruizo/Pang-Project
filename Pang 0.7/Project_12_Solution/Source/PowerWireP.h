#ifndef __POWERWIREP_H__
#define __POWERWIREP_H__
#include "Animation.h"
#include "p2Point.h"

struct Collider;

struct PowerWireP
{
public:
	// Constructor
	PowerWireP();

	// Copy constructor
	PowerWireP(const PowerWireP& p);

	// Destructor
	~PowerWireP();

	// Called in ModulePowerWirePs' Update
	// Handles the logic of the PowerWireP
	// Returns false when the PowerWireP reaches its lifetime
	bool Update();

	// Sets flag for deletion and for the collider aswell
	void SetToDelete();

public:
	// Defines the position in the screen
	iPoint position;

	// Defines the speed at which the PowerWireP will move (pixels per second)
	iPoint speed;

	// A set of rectangle sprites
	Animation anim;

	// Defines wether the PowerWireP is alive or not
	// PowerWirePs will be set to not alive until "spawnTime" is reached
	bool isAlive = false;

	// Defines the amout of frames this PowerWireP has been active
	// Negative values mean the PowerWireP is waiting to be activated
	int frameCount = 0;

	// Defines the total amount of frames during which the PowerWireP will be active
	uint lifetime = 0;

	// The PowerWireP's collider
	Collider* collider = nullptr;

	// A flag for the PowerWireP removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;
};

#endif //__PowerWireP_H__

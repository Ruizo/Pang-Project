#ifndef _BREAKABLE_PLATFORM_H_
#define _BREAKABLE_PLATFORM_H_

#include "Enemy.h"

class BreakablePlatform : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	BreakablePlatform(int x, int y);

	void Update() override;

	void OnCollision(Collider* collider);


private:

	// The original spawning position. The wave will be calculated from that
	int spawn_y = 0;

	// The total height of the wave
	int waveHeight = 15;

	// The enemy animation
	Animation flyAnim;
};



#endif 
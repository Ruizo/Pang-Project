#ifndef _Balls_H
#define _Balls_H

#include "Enemy.h"

class Balls : public Enemy
{
public:
	p2Point<float> position1;
	p2Point<float> speed;

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Balls(int x, int y);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;

	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;



private:
	// The position (as ratio) in the wave at a specific moment
	float waveRatio = 0.0f;

	// The speed at which the wave ratio is increased
	float waveRatioSpeed = 0.05f;

	// The original spawning position. The wave will be calculated from that
	int spawn_y = 0;

	// The total height of the wave
	int waveHeight = 15;

	// The enemy animation
	Animation flyAnim;


};

#endif // __ENEMY_REDBIRD_H__
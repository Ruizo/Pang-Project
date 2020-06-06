#ifndef _BALLS_H_
#define _BALLS_H_

#include "Enemy.h"

class Balls : public Enemy
{
public:
	
	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Balls(int x, int y);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;

	void OnCollision(Collider* collider) override;


private:
	
	// The original spawning position. The wave will be calculated from that
	int spawn_y = 0;

	// The total height of the wave
	int waveHeight = 15;

	// The enemy animation
	Animation flyAnim;
};



#endif // _BALLS_H
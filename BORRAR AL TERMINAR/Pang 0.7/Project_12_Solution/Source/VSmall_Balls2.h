#ifndef _VSMALL_BALLS2_H_
#define _VSMALL_BALLS2_H_

#include "Enemy.h"
#include "ModuleEnemies.h"

class VSmall_Balls2 : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	VSmall_Balls2(int x, int y);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;
	void OnCollision(Collider* collider);

private:
	enum class ENEMY_TYPE;
	int spawn = 0;
	// The original spawning position. The wave will be calculated from that
	int spawn_y = 0;

	// The total height of the wave
	int waveHeight = 15;

	// The enemy animation
	Animation flyAnim;
};

#endif // _SMALL_BALLS2_H
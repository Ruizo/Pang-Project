#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"

#define MAX_LISTENERS 100

class Module;

struct Collider
{
	enum Type
	{
		NONE = -1,
		WALL1,
		WALL2,
		WALL3,
		WALL4,
		PLAYER,
		ENEMY,
		PLAYER_SHOT,
		BPLATFORM,
		BPLATFORMUp,
		BPLATFORMDown,
		BPLATFORMRight,
		BPLATFORMLeft,
		BOOSTERS,
		STAIRS,
		ELEVATOR,
		VULCAN,
		POWERWIRE,
		DYNAMITE,

		MAX
	};

	//Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);

	void SetPos(int x, int y);

	bool Intersects(const SDL_Rect& r) const;

	void AddListener(Module* listener);

	//Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	Module* listener = nullptr;
	Module* listeners[MAX_LISTENERS] = { nullptr };
};


#endif // !__COLLIDER_H__


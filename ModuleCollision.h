#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#include <list>
#include <map>
#include <functional>
#include "Module.h"
#include "MovementKeys.h"

enum CollisionType {
	CENEMY,
	CENEMY_ATTACK,
	CWALL,
	CPLAYER,
	CPLAYER_ATTACK,
	CDESTRUCTIBLE,
	CTRIGGER
};

struct Collider
{
	SDL_Rect rect = { 0,0,0,0 };
	bool to_delete = false;
	CollisionType type;
	std::function<void(std::map<MOVEMENTKEY, bool>, CollisionType)> OnCollision;

	Collider(SDL_Rect rectangle, std::function<void(std::map<MOVEMENTKEY, bool>, CollisionType)> OnCollision) :
		rect(rectangle), OnCollision(OnCollision)
	{

	}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(const Collider & c) const;
};

class ModuleCollision : public Module
{
public:

	ModuleCollision();
	~ModuleCollision();

	update_status PreUpdate();
	update_status Update();

	bool CleanUp();

	Collider * AddCollider(const SDL_Rect & rect, CollisionType type, std::function<void(std::map<MOVEMENTKEY, bool>, CollisionType)> onCollision);

	bool CheckCollidingTypes(CollisionType type, CollisionType otherType);

	void DebugDraw();

private:

	std::map<std::pair<CollisionType, CollisionType>, bool> collisionMatrix;
	std::list<Collider*> colliders;
};

#endif // __ModuleCollision_H__
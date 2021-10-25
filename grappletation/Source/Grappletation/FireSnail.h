#pragma once

#include "Entity.h"
#include <list>

class Tile;
class Renderer;
class SoundManager;
class AnimatedSprite;

class FireSnail : public Entity
{
public:
	FireSnail();
	~FireSnail();
	bool Initialise(Renderer& renderer);
	void Process(float deltaTime, SoundManager& soundManager);
	void Start(std::list<Tile*> tiles);
protected:
private:
	std::list<Tile*> CheckCollisions();
public:
	enum SnailStates
	{
		FALLING,
		PATROL,
	};
protected:
private:
	int direction;
	std::list<Tile*> tiles;
	const int GRAVITY = 1000;
	const int MOVEMENTSPEED = 10;
	const float FRAMEDURATION = 0.1;
	SnailStates snailState;
	float timeElapsed;
	const float GAMETICK = 1;
};


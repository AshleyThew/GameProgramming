#pragma once

#include "Entity.h"
#include "Sprite.h"
#include <list>
#include <map>
#include <string>

class Tile;
class Renderer;
class SoundManager;
class AnimatedSprite;
class ParticleSystem;

class FireFly : public Entity
{
public:
	FireFly();
	~FireFly();
	bool Initialise(Renderer& renderer);
	void Process(float deltaTime, SoundManager& soundManager, Vector2 playerLocation);
	void Draw(Renderer& renderer);
	void Start(std::list<Tile*> tiles, Vector2 gridSize, Vector2 startingPosition);
	void DebugDraw();
	void DebugDraw(float angle);

protected:
private:
	bool SendRay(Vector2 destination);
public:
protected:
private:
	std::map<std::string, bool> tileMap;
	std::list<Tile*> tileList;
	const int MOVEMENTSPEED = 10;
	const float FRAMEDURATION = 0.05f;
	const float MAXVELOCITY = 10;
	std::list<Vector2> colliderPositions;
	float tileSize;
	Sprite* marker;
	ParticleSystem* particleSystem;
};


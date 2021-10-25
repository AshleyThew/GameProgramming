#pragma once
#include "Vector2.h"

class Sprite;
class Renderer;

class LocationMaster
{
public:
	LocationMaster();
	~LocationMaster();
	bool Initialise(Renderer& renderer, float tileSize);
	void Process(float deltaTime);
	void Draw(Renderer& renderer);
	void DebugDraw();
private:
protected:
public:
protected:
private:
	int x1;
	int y1;
	int x2;
	int y2;
	Sprite* sprite;
	float tileSize;
};


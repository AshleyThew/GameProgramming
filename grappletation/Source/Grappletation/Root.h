#pragma once

#include "Entity.h"
#include "Tile.h"
#include <list>
class Renderer;

class Root : public Entity
{
public:
	Root();
	~Root();
	bool Initialise(Renderer &renderer);
	bool isColliding();
	void SetAlive(int x, int y, float scale);
protected:
private:
public:
protected:
private:
	bool colliding;
};


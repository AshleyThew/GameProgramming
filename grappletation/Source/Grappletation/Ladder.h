#pragma once

#include "Entity.h"

class Renderer;
class Vector2;

class Ladder : public Entity
{
public:
	Ladder(int x, int y);
	~Ladder();
	virtual bool Initialise(Renderer& renderer, int ladderType, float scale);
	Vector2 GetID();
protected:
private:
public:
protected:
private:
	Vector2 id;
};


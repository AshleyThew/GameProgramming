#pragma once

#include "Entity.h"

class Gem : public Entity
{
public:
	Gem(int x, int y);
	~Gem();
	virtual bool Initialise(Renderer& renderer, const char* gemType, float scale);
	virtual void Process(float deltaTime);
	virtual void Draw(Renderer& renderer);
	bool GetCollected();
	void SetCollected();
	void Reset();
	Vector2 GetID();
protected:
private:
public:
protected:
private:
	bool collected;
	Vector2 id;
};


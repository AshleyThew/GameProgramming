#pragma once

#include "Entity.h"

class Renderer;
class SoundManager;
class InputSystem;
class Sprite;

class Coin : public Entity
{
public:
	Coin();
	~Coin();
	bool Initialise(Renderer& renderer);
	void SetTransform(Vector2 position, float scale);
protected:
private:
public:
protected:
private:
};


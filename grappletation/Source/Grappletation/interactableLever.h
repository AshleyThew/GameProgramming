#pragma once

#include "Entity.h"
#include <vector>

class Renderer;
class Sprite;
class InputSystem;
class Door;

class interactableLever : public Entity
{
public:
	interactableLever(int x, int y);
	~interactableLever();
	virtual bool Initialise(Renderer& renderer, int rotation, float scale);
	virtual void Process(float deltaTime, InputSystem& inputSystem);
	virtual void Draw(Renderer& renderer);
	void SetPressed(bool pressed);
	void SetAttachedDoor(Door* attactedDoor);
	Vector2 GetID();
protected:
private:
	void PlayAnimation(float deltaTime);
public:
protected:
private:
	Sprite* leverHead;
	bool pressed;
	Vector2 id;
	float currentAnimationFrame;
	const float MOVEMENTSPEED = 10;
	std::vector<Door*> attachedDoors;
};


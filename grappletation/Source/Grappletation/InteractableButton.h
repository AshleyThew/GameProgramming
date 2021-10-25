#pragma once
#include "Entity.h"
#include <vector>

class Renderer;
class InputSystem;
class Sprite;
class Door;

class InteractableButton : public Entity
{
public:
	InteractableButton(int x, int y);
	~InteractableButton();
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
	Vector2 id;
	float currentAnimationFrame; //From 0 to 1, 0 is not pressed and 1 is pressed
	Sprite* buttonHead;
	float timeElapsed;
	float const MOVEMENTSPEED = 5;
	bool pressed;
	Vector2 MAXDISTANCE;
	std::vector<Door*> attachedDoors;
};


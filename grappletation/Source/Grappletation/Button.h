#pragma once

#include "Vector2.h"

class Renderer;
class SoundManager;
class InputSystem;
class Sprite;

class Button
{
public:
	Button();
	~Button();
	bool Initialise(Renderer& renderer, const char* spriteLocation);
	bool Process(float deltaTime, InputSystem& inputSystem);
	void Draw(Renderer& renderer);
	void SetTransform(int x, int y, float scale);
	void SetPressed(bool pressed);
	void SetSprite(Sprite * newSprite);
	Sprite* GetSprite();
	bool GetCursorHover();
	bool GetMousePressed();
	float GetDefaultScale();
	void setToggleable();
	void setCursorHover(bool hover);
protected:
private:
public:
	bool cursorHover;
	bool toggleable;
	float timer;
	Sprite* sprite;
protected:
	bool mousePressed;
	bool controllerPressed;
private:
	Vector2 topLeftBound;
	Vector2 bottomRightBound;
	float defaultScale;
};


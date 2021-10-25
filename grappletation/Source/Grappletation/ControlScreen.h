#pragma once

#ifndef __CONTROLSCREEN_H__
#define __CONTROLSCREEN_H__

#include "renderer.h"
#include "inputsystem.h"
#include "button.h"
#include "sprite.h"

class ControlScreen
{
public:
	ControlScreen();
	~ControlScreen();
	bool Initialise(Renderer& renderer);
	void Process(float deltaTime, InputSystem& inputSystem);
	void Draw(Renderer& renderer);
	bool GetControlType();
	bool GetCursorHover();
protected:



private:

public:
	bool gotoMain;
	bool keyboardActive;
	bool hasSwitched;
protected:
	Sprite* ControlsPanel;
	Sprite* ButtonHighlight;
	Button* GoBack;
private:
};
#endif // __CONTROLSCREEN_H__

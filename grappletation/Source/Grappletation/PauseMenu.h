#pragma once
// COMP710 GP Framework 2021
#ifndef __PAUSEMENU_H__
#define __PAUSEMENU_H__

#include "renderer.h"
#include "button.h"
#include "inputsystem.h"
#include "sprite.h"

class PauseMenu 
{
public:
	PauseMenu();
	virtual ~PauseMenu();
	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime, InputSystem& inputSystem);
	virtual void Draw(Renderer& renderer);
protected:

private:

public:
	bool isActive;

protected:
	Sprite* pausePanel;
	Sprite* pauseText;
	Button* quit;
	Sprite* highlight;
private:
};
#endif // __PAUSEMENU_H__

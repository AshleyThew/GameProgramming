#pragma once
// COMP710 GP Framework 2021
#ifndef __CHECKBOX_H__
#define __CHECKBOX_H__

#include "renderer.h"
#include "button.h"
#include "inputsystem.h"
#include "sprite.h"

class Checkbox : public Button
{
public:
	Checkbox();
	virtual ~Checkbox();
	virtual bool Initialise(Renderer& renderer, bool isActive);
	virtual void Process(float deltaTime, InputSystem& inputSystem);
	virtual void Draw(Renderer& renderer);

protected:

private:

public:
	bool toSwitch;
	bool checked;
	bool mousePressed;

protected:

private:
};
#endif // __CHECKBOX_H__

#pragma once
#ifndef __INPUTTEST_H__
#define __INPUTTEST_H__

#include "scene.h"
#include "InputSystem.h"

class Renderer;

class InputTest : public Scene
{
public:
	InputTest();
	~InputTest();

	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime);
	virtual void Draw(Renderer& renderer);
	virtual void DebugDraw();

protected:

private:

public:

protected:

private:
};

#endif //__INPUTTEST_H__


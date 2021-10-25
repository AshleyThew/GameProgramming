#pragma once
// COMP710 GP Framework 2021
#ifndef __SLIDER_H__
#define __SLIDER_H__

#include "renderer.h"
#include "button.h"
#include "inputsystem.h"
#include "sprite.h"

class Slider : public Button
{
public:
	Slider();
	virtual ~Slider();
	virtual bool Initialise(Renderer& renderer, bool isActive);
	virtual void Process(float deltaTime, InputSystem& inputSystem);
	virtual void Draw(Renderer& renderer);
	virtual void MoveSlider();

protected:

private:

public:

	Sprite* sliderbar;

protected:

private:
};
#endif // __SLIDER_H__
#pragma once

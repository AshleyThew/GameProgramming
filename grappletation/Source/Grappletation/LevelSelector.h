#pragma once
// COMP710 GP Framework 2021
#ifndef __LEVELSELECTOR_H__
#define __LEVELSELECTOR_H__
// Local includes:
#include "vector2.h"
#include "entity.h"
#include "animatedsprite.h"
#include "renderer.h"
#include "inputsystem.h"
#include "button.h"

class LevelSelector
{
public:
	LevelSelector();
	~LevelSelector();
	bool Initialise(Renderer& renderer);
	void Process(float deltaTime, InputSystem& inputSystem);
	void Draw(Renderer& renderer);
	bool SaveUserSettings();

protected:

private:

public:
	bool toReset;
	bool gotoMain;
	bool mouseShowing;
protected:
	Sprite* OptionsText;
	Sprite* Panel;

	Button* StartLevel;
	Button* GoBack;
	Sprite* SaveSettingsHighlight;
	Sprite* GoBackHighlight;

private:
};
#endif // __LEVELSELECTOR_H__

#pragma once

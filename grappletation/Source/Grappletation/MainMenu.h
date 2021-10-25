// COMP710 GP Framework 2021
#ifndef __MAINMENU_H__
#define __MAINMENU_H__
// Local includes:
#include "vector2.h"
#include "entity.h"
// Forward declarations:
#include "animatedsprite.h"
#include "renderer.h"
#include "inputsystem.h"
#include "button.h"
#include "optionsmenu.h"
#include "levelselector.h"
#include "SettingLoader.h"
#include "controlscreen.h"

// Forward declarations:

// Class declaration:
class MainMenu
{
	// Member methods:
public:
	MainMenu();
	~MainMenu();
	bool Initialise(Renderer& renderer);
	void Process(float deltaTime, InputSystem& inputSystem);
	void Draw(Renderer& renderer);

	bool IsCollidingWith(Sprite * buttonSprite, Sprite * mouseLoc);
protected:

private:

public:
	bool isActive;
	bool toReset;
	bool gotoMain;
	bool levelSelectActive;
	bool optionActive;
	bool controlactive;
	int selectButtonIndex;
	OptionsMenu* OptionMenu;
	LevelSelector* LevelSelect;
	ControlScreen* ControlPanel;
protected:
	SettingLoader* gameSettings;
	Button* CurrentlySelected;
	Sprite* blackBackground;
	Sprite* GameLogo;
	Button* Start;
	Button* Options;
	Button* Quit;
	Button* Controls;
	Sprite* GameInfo;
	Sprite* CompanyInfo;
	Sprite* ButtonHighlight;
private:
};
#endif // __MAINMENU_H__

#pragma once



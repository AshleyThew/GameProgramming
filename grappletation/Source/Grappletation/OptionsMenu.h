#pragma once
// COMP710 GP Framework 2021
#ifndef __OPTIONSMENU_H__
#define __OPTIONSMENU_H__
// Local includes:
#include "vector2.h"
#include "entity.h"
// Forward declarations:
#include "animatedsprite.h"
#include "renderer.h"
#include "inputsystem.h"
#include "button.h"
#include "checkbox.h"
#include "slider.h"

class OptionsMenu
{
public:
	OptionsMenu();
	~OptionsMenu();
	bool Initialise(Renderer& renderer);
	void Process(float deltaTime, InputSystem& inputSystem);
	void Draw(Renderer& renderer);
	bool SaveUserSettings();
	float GetVolume();
	bool GetFullScreen();
	bool GetSoundToggled();
	void SetVolume(float volume);
	void SetFullscreen(float volume);
	void SetSoundToggled(float volume);

protected:

private:

public:
	bool saveSettings;
	bool toReset;
	bool gotoMain;
	bool mouseShowing;
protected:
	float volumeLevel;
	bool fullscreen;
	bool soundon;
	Sprite* OptionsText;
	Sprite* Panel;
	Sprite* SoundText;
	Button* SaveSettings;
	Button* GoBack;
	Sprite* SaveSettingsHighlight;
	Sprite* GoBackHighlight;
	Checkbox* SoundEnabled;
	Sprite* FullScreenText;
	Checkbox* FullScreenEnabled;
	Sprite* VolumeText;
	Slider* soundSlider;
private:
};
#endif // __OPTIONSMENU_H__

#pragma once

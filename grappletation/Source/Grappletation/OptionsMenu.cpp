
#include "optionsmenu.h"
#include "logmanager.h"
#include "button.h"
#include "slider.h"
#include <sstream>
#include <fstream>
#include <iostream>
using std::cerr;
using std::endl;

OptionsMenu::OptionsMenu()
	: 
	volumeLevel(0.0f),
	fullscreen(false),
	soundon(false)
{
}

OptionsMenu::~OptionsMenu()
{
	delete OptionsText;
	OptionsText = 0;
	delete Panel;
	Panel = 0;
	delete SoundText;
	SoundText = 0;
	delete SaveSettings;
	SaveSettings = 0;
	delete GoBack;
	GoBack = 0;
	delete SaveSettingsHighlight;
	SaveSettingsHighlight = 0;
	delete GoBackHighlight;
	GoBackHighlight = 0;
	delete SoundEnabled;
	SoundEnabled = 0;
	delete FullScreenText;
	FullScreenText = 0;
	delete FullScreenEnabled;
	FullScreenEnabled = 0;
	delete VolumeText;
	VolumeText = 0;
	delete soundSlider;
	soundSlider = 0;
}

bool OptionsMenu::Initialise(Renderer & renderer)
{
	gotoMain = false;

	SoundEnabled = new Checkbox();
	SoundEnabled->Initialise(renderer, GetSoundToggled());
	SoundEnabled->SetTransform(renderer.GetWidth() / 2 + 92, renderer.GetHeight() / 2 + 20.0f, 1.0f);

	FullScreenEnabled = new Checkbox();
	FullScreenEnabled->Initialise(renderer, GetFullScreen());
	FullScreenEnabled->SetTransform(renderer.GetWidth() / 2 + 115, renderer.GetHeight() / 2 - 30, 1.0f);

	SaveSettings = new Button();
	SaveSettings->setToggleable();
	renderer.CreateStaticText("Save", 28);
	SaveSettings->SetSprite(renderer.CreateSprite("Save"));
	SaveSettings->SetTransform(renderer.GetWidth() / 2 - 100.0f, renderer.GetHeight() / 2 + 380.0f, 1.0f);

	GoBack = new Button();
	GoBack->setToggleable();
	renderer.CreateStaticText("Go Back", 28);
	GoBack->SetSprite(renderer.CreateSprite("Go Back"));
	GoBack->SetTransform(renderer.GetWidth() / 2 + 100.0f, renderer.GetHeight() / 2 + 380.0f, 1.0f);
	
	soundSlider = new Slider();
	soundSlider->Initialise(renderer, false);
	soundSlider->SetTransform(renderer.GetWidth() / 2, renderer.GetHeight() / 2 + 120.0f, 4.0f);

	soundSlider->sliderbar->SetX(soundSlider->GetSprite()->GetX());
	soundSlider->sliderbar->SetY(soundSlider->GetSprite()->GetY());

	renderer.CreateStaticText("Game Options", 48);
	OptionsText = renderer.CreateSprite("Game Options");
	OptionsText->SetX(renderer.GetWidth() / 2);
	OptionsText->SetY(renderer.GetHeight() / 2 - 160.0f);

	renderer.CreateStaticText("Sound  Enabled", 28);
	SoundText = renderer.CreateSprite("Sound  Enabled");
	SoundText->SetX(renderer.GetWidth() / 2 - 20);
	SoundText->SetY(renderer.GetHeight() / 2 + 20.0f);

	renderer.CreateStaticText("Fullscreen  Enabled", 28);
	FullScreenText = renderer.CreateSprite("Fullscreen  Enabled");
	FullScreenText->SetX(renderer.GetWidth() / 2 - 20);
	FullScreenText->SetY(renderer.GetHeight() / 2 - 30);

	renderer.CreateStaticText("Sound  Level", 28);
	VolumeText = renderer.CreateSprite("Sound  Level");
	VolumeText->SetX(renderer.GetWidth() / 2);
	VolumeText->SetY(renderer.GetHeight() / 2 + 70);

	Panel = renderer.CreateSprite("sprites\\menu\\optionspanel.png");
	Panel->SetX(renderer.GetWidth() / 2);
	Panel->SetY(renderer.GetHeight() / 2 + 120);
	Panel->SetScale(3.0f);
	
	SaveSettingsHighlight = renderer.CreateSprite("sprites\\menu\\buttonhighlight.png");
	SaveSettingsHighlight->SetX(SaveSettings->GetSprite()->GetX());
	SaveSettingsHighlight->SetY(SaveSettings->GetSprite()->GetY());

	GoBackHighlight = renderer.CreateSprite("sprites\\menu\\buttonhighlight.png");
	GoBackHighlight->SetX(GoBack->GetSprite()->GetX());
	GoBackHighlight->SetY(GoBack->GetSprite()->GetY());

	soundSlider->SetTransform(volumeLevel + 882.0f, soundSlider->GetSprite()->GetY(), 4.0f);

	return false;
}

void OptionsMenu::Process(float deltaTime, InputSystem& inputSystem)
{
	GoBack->Process(deltaTime, inputSystem);
	SaveSettings->Process(deltaTime, inputSystem);
	SoundEnabled->Process(deltaTime, inputSystem);
	SoundText->Process(deltaTime);
	FullScreenEnabled->Process(deltaTime, inputSystem);
	FullScreenText->Process(deltaTime);
	soundSlider->Process(deltaTime, inputSystem);
	VolumeText->Process(deltaTime);
	if (SaveSettings->GetMousePressed()) {
		SaveUserSettings();
	}

	if (GoBack->GetMousePressed() || inputSystem.GetKeyState(SDL_SCANCODE_ESCAPE)) {
		gotoMain = true;
	}
}

void OptionsMenu::Draw(Renderer & renderer)
{
	Panel->Draw(renderer);
	OptionsText->Draw(renderer);
	GoBackHighlight->Draw(renderer);
	SaveSettingsHighlight->Draw(renderer);
	GoBack->Draw(renderer);

	SoundEnabled->Draw(renderer);
	SoundText->Draw(renderer);
	FullScreenEnabled->Draw(renderer);
	FullScreenText->Draw(renderer);
	VolumeText->Draw(renderer);
	soundSlider->Draw(renderer);
	SaveSettings->Draw(renderer);
}

bool OptionsMenu::SaveUserSettings()
{
	if (fullscreen) {
		if (!FullScreenEnabled->checked) {
			fullscreen = false;
		}
	}
	else{
		if (FullScreenEnabled->checked) {
			fullscreen = true;
		}
	}

	if (soundon) {
		if (!SoundEnabled->checked) {
			soundon = false;
		}
	}
	else{
		if (SoundEnabled->checked) {
			soundon = true;
		}
	}

	volumeLevel = soundSlider->GetSprite()->GetX() - 500;
	
	std::ofstream outfile("gamesettings.ini");

	if (fullscreen) {
		outfile << "Fullscreen = true" << endl;
	}
	else {
		outfile << "Fullscreen = false" << endl;
	}

	if (soundon) {
		outfile << "SoundEnabled = true" << endl;
	}
	else {
		outfile << "SoundEnabled = false" << endl;
	}

	std::string temp = "Volume = ";
	temp += std::to_string(volumeLevel - 384.0f);

	outfile << temp << endl;

	return false;
}

float OptionsMenu::GetVolume()
{
	return volumeLevel;
}

bool OptionsMenu::GetFullScreen()
{
	return fullscreen;
}

bool OptionsMenu::GetSoundToggled()
{
	return soundon;
}

void OptionsMenu::SetVolume(float volume)
{
	volumeLevel = volume;
}

void OptionsMenu::SetFullscreen(float fullscreentoggle)
{
	fullscreen = fullscreentoggle;
}

void OptionsMenu::SetSoundToggled(float soundtoggle)
{
	soundon = soundtoggle;
}
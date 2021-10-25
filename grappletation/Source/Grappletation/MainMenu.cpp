#include "mainmenu.h"
#include "logmanager.h"
#include "Game.h"
#include "XboxController.h"

class ControlScreen;

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
	delete OptionMenu;
	OptionMenu = 0;
	delete LevelSelect;
	LevelSelect = 0;
	delete ControlPanel;
	ControlPanel = 0;

	delete gameSettings;
	gameSettings = 0;
	delete blackBackground;
	blackBackground = 0;
	delete GameLogo;
	GameLogo = 0;
	delete Start;
	Start = 0;
	delete Options;
	Options = 0;
	delete Quit;
	Quit = 0;
	delete Controls;
	Controls = 0;
	delete GameInfo;
	GameInfo = 0;
	delete CompanyInfo;
	CompanyInfo = 0;
	delete ButtonHighlight;
	ButtonHighlight = 0;
}

bool MainMenu::Initialise(Renderer & renderer)
{
	selectButtonIndex = 1;
	CurrentlySelected = new Button();
	gameSettings = new SettingLoader();
	gameSettings->LoadSettings();
	controlactive = false;

	renderer.SetClearColour(0.2f, 0.2f, 0.2f);
	isActive = true;
	LogManager::GetInstance().Log("start of Initialise");
	OptionMenu = new OptionsMenu();
	OptionMenu->SetFullscreen(gameSettings->GetValueAsBoolean("Fullscreen"));
	OptionMenu->SetSoundToggled(gameSettings->GetValueAsBoolean("SoundEnabled"));
	OptionMenu->SetVolume(gameSettings->GetValueAsFloat("Volume"));
	OptionMenu->Initialise(renderer);
	optionActive = false;

	LevelSelect = new LevelSelector();
	LevelSelect->Initialise(renderer);
	levelSelectActive = false;

	float middleHeight = (renderer.GetHeight() / 2);
	float middleWidth = (renderer.GetWidth() / 2);

	toReset = false;
	gotoMain = false;

	blackBackground = renderer.CreateSprite("sprites\\menu\\blackbackground.png");
	GameLogo = renderer.CreateSprite("sprites\\menu\\grappletation.png");

	ButtonHighlight = renderer.CreateSprite("sprites\\menu\\buttonhighlight.png");
	ButtonHighlight->SetX(middleWidth);
	ButtonHighlight->SetY(middleHeight);
	ButtonHighlight->SetScale(1.3f);

	LogManager::GetInstance().Log("middle");

	renderer.CreateStaticText("Grappletation - Developed by COMP610 2021 Students.", 12);
	CompanyInfo = renderer.CreateSprite("Grappletation - Developed by COMP610 2021 Students.");
	CompanyInfo->SetX((renderer.GetWidth() - CompanyInfo->GetWidth() / 2) - 2.0f);
	CompanyInfo->SetY(renderer.GetHeight() - 12.0f);

	renderer.CreateStaticText("Grappletation_version_0.1", 12);
	GameInfo = renderer.CreateSprite("Grappletation_version_0.1");
	GameInfo->SetX(GameInfo->GetWidth() / 2 + 2.0);
	GameInfo->SetY(renderer.GetHeight() - 12.0f);

	Start = new Button();
	Start->setToggleable();
	renderer.CreateStaticText("Start", 44);
	Start->SetSprite(renderer.CreateSprite("Start"));
	Start->SetTransform(middleWidth, middleHeight, 1.0f);

	Options = new Button();
	Options->setToggleable();
	renderer.CreateStaticText("Options", 44);
	Options->SetSprite(renderer.CreateSprite("Options"));
	Options->SetTransform(middleWidth, middleHeight + 100, 1.0f);

	Controls = new Button();
	Controls->setToggleable();
	renderer.CreateStaticText("Controls", 44);
	Controls->SetSprite(renderer.CreateSprite("Controls"));
	Controls->SetTransform(middleWidth, middleHeight + 200, 1.0f);

	ControlPanel = new ControlScreen();
	ControlPanel->Initialise(renderer);

	Quit = new Button();
	Quit->setToggleable();
	renderer.CreateStaticText("Exit", 44);
	Quit->SetSprite(renderer.CreateSprite("Exit"));
	Quit->SetTransform(middleWidth, middleHeight + 300, 1.0f);

	GameLogo->SetX(middleWidth);
	GameLogo->SetY(200);
	GameLogo->SetScale(1.2f);

	blackBackground->SetX(840);
	blackBackground->SetY(300);
	blackBackground->SetAlpha(0.80f);
	blackBackground->SetScale(5.0f);

	CurrentlySelected = Start;

return false;
}

void MainMenu::Process(float deltaTime, InputSystem& inputSystem)
{
	Vector2 mouse = inputSystem.GetMousePosition();
	inputSystem.ShowMouseCursor(true);

	if ( inputSystem.GetKeyState(SDL_SCANCODE_S) == BS_PRESSED || inputSystem.GetKeyState(SDL_SCANCODE_DOWN) == BS_PRESSED) {
		if (selectButtonIndex < 4) {
			selectButtonIndex++;

			if (selectButtonIndex == 2) {
				CurrentlySelected = Options;
				Options->setCursorHover(true);
			}
			else if (selectButtonIndex == 3) {
				CurrentlySelected = Controls;
				Controls->setCursorHover(true);
			}
			else {
				CurrentlySelected = Quit;
				Quit->setCursorHover(true);
			}

			CurrentlySelected->setCursorHover(true);
			ButtonHighlight->SetY(CurrentlySelected->GetSprite()->GetY());
		}
	}

	if (inputSystem.GetKeyState(SDL_SCANCODE_W) == BS_PRESSED || inputSystem.GetKeyState(SDL_SCANCODE_UP) == BS_PRESSED) {
		if (selectButtonIndex > 1) {
			selectButtonIndex--;

			if (selectButtonIndex == 1) {
				CurrentlySelected = Start;
				Start->setCursorHover(true);
			}
			else if (selectButtonIndex == 2) {
				CurrentlySelected = Options;
				Options->setCursorHover(true);
			}
			else {
				CurrentlySelected = Controls;
				Controls->setCursorHover(true);
			}
			CurrentlySelected->setCursorHover(true);
			ButtonHighlight->SetY(CurrentlySelected->GetSprite()->GetY());
		}
			
	}
	
	if (optionActive) {
		OptionMenu->Process(deltaTime, inputSystem);
		if (OptionMenu->gotoMain) {
			optionActive = false;
			OptionMenu->gotoMain = false;
		}
	}
	else if (levelSelectActive) {
		LevelSelect->Process(deltaTime, inputSystem);
		if (LevelSelect->gotoMain) {
			levelSelectActive = false;
			LevelSelect->gotoMain = false;
		}
	}
	else if (controlactive) {
		ControlPanel->Process(deltaTime, inputSystem);
		if (ControlPanel->gotoMain) {
			controlactive = false;
			ControlPanel->gotoMain = false;
		}
	}
	else {

		if (Start->GetCursorHover()) {
			CurrentlySelected = Start;
			ButtonHighlight->SetY(Start->GetSprite()->GetY());
			selectButtonIndex = 1;
		}
		if (Options->GetCursorHover()) {
			CurrentlySelected = Start;
			ButtonHighlight->SetY(Options->GetSprite()->GetY());
			selectButtonIndex = 2;
		}
		if (Quit->GetCursorHover()) {
			CurrentlySelected = Start;
			ButtonHighlight->SetY(Quit->GetSprite()->GetY());
			selectButtonIndex = 4;
		}
		if (Controls->GetCursorHover()) {
			CurrentlySelected = Start;
			ButtonHighlight->SetY(Controls->GetSprite()->GetY());
			selectButtonIndex = 3;
		}

		Start->Process(deltaTime, inputSystem);
		Options->Process(deltaTime, inputSystem);
		Quit->Process(deltaTime, inputSystem);
		Controls->Process(deltaTime, inputSystem);

		if (selectButtonIndex == 1 && (Start->GetMousePressed() || inputSystem.GetKeyState(SDL_SCANCODE_E) == BS_PRESSED || inputSystem.GetKeyState(SDL_SCANCODE_SPACE) == BS_PRESSED)) {
			levelSelectActive = true;
			isActive = false;
		}

		if (selectButtonIndex == 2 && (Options->GetMousePressed() || inputSystem.GetKeyState(SDL_SCANCODE_E) == BS_PRESSED || inputSystem.GetKeyState(SDL_SCANCODE_SPACE) == BS_PRESSED)) {
			optionActive = true;
		}

		if (selectButtonIndex == 4 && (Quit->GetMousePressed() || inputSystem.GetKeyState(SDL_SCANCODE_E) == BS_PRESSED || inputSystem.GetKeyState(SDL_SCANCODE_SPACE) == BS_PRESSED)) {
			Game::GetInstance().Quit();
		}

		if (selectButtonIndex == 3 && (Controls->GetMousePressed() || inputSystem.GetKeyState(SDL_SCANCODE_E) == BS_PRESSED || inputSystem.GetKeyState(SDL_SCANCODE_SPACE) == BS_PRESSED)) {
			controlactive = true;
		}
	}
	ButtonHighlight->Process(deltaTime);
}

void MainMenu::Draw(Renderer & renderer)
{
	blackBackground->Draw(renderer);
	ButtonHighlight->Draw(renderer);
	Start->Draw(renderer);
	Options->Draw(renderer);
	Quit->Draw(renderer);
	Controls->Draw(renderer);
	GameLogo->Draw(renderer);
	GameInfo->Draw(renderer);
	CompanyInfo->Draw(renderer);

	if (optionActive) {
		OptionMenu->Draw(renderer);
	}
	if (levelSelectActive) {
		LevelSelect->Draw(renderer);
	}
	if (controlactive) {
		ControlPanel->Draw(renderer);
	}
}
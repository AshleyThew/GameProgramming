#include "controlscreen.h"

ControlScreen::ControlScreen()
	: gotoMain(false)
{
}

ControlScreen::~ControlScreen()
{
	delete ControlsPanel;
	ControlsPanel = 0;
	delete ButtonHighlight;
	ButtonHighlight = 0;
	delete GoBack;
	GoBack = 0;
}

bool ControlScreen::Initialise(Renderer & renderer)
{
	gotoMain = false;
	hasSwitched = true;

	keyboardActive = true;
	ControlsPanel = renderer.CreateSprite("sprites\\menu\\keyboardcontrols.png");

	ControlsPanel->SetX(renderer.GetWidth() / 2);
	ControlsPanel->SetY(renderer.GetHeight() / 2 + 60);
	ControlsPanel->SetScale(1.0f);

	GoBack = new Button();
	GoBack->setToggleable();
	renderer.CreateStaticText("Go Back", 28);
	GoBack->SetSprite(renderer.CreateSprite("Go Back"));
	GoBack->SetTransform(renderer.GetWidth() / 2 + 800.0f, renderer.GetHeight() / 2 + 400.0f, 1.5f);

	ButtonHighlight = renderer.CreateSprite("sprites\\menu\\buttonhighlight.png");
	ButtonHighlight->SetScale(1.5f);
	ButtonHighlight->SetX(GoBack->GetSprite()->GetX());
	ButtonHighlight->SetY(GoBack->GetSprite()->GetY());

	return false;
}

void ControlScreen::Process(float deltaTime, InputSystem & inputSystem)
{
	GoBack->Process(deltaTime, inputSystem);

	if (inputSystem.GetNumberOfControllersAttached() > 0 && keyboardActive) {
		keyboardActive = false;
		hasSwitched = false;
	}
	else if(!keyboardActive){
		keyboardActive = true;
		hasSwitched = false;
	}


	if (GoBack->GetMousePressed() || inputSystem.GetKeyState(SDL_SCANCODE_ESCAPE)) {
		gotoMain = true;
	}
}

void ControlScreen::Draw(Renderer & renderer)
{
	if (!hasSwitched) {
		hasSwitched = true;
		if (keyboardActive) {
			ControlsPanel = renderer.CreateSprite("sprites\\menu\\keyboardcontrols.png");
			ControlsPanel->SetX(renderer.GetWidth() / 2);
			ControlsPanel->SetY(renderer.GetHeight() / 2 + 100);
			ControlsPanel->SetScale(1.5f);
		}
		else {
			ControlsPanel = renderer.CreateSprite("sprites\\menu\\gamecontroller.png");
			ControlsPanel->SetX(renderer.GetWidth() / 2);
			ControlsPanel->SetY(renderer.GetHeight() / 2 + 100);
			ControlsPanel->SetScale(1.5f);
		}
	}
	ControlsPanel->Draw(renderer);
	ButtonHighlight->Draw(renderer);
	GoBack->Draw(renderer);
}

bool ControlScreen::GetControlType()
{
	return false;
}

bool ControlScreen::GetCursorHover() {
	return GoBack->GetCursorHover();
}

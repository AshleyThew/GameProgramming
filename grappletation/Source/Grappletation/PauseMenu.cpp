#include "PauseMenu.h"
#include "Game.h"

PauseMenu::PauseMenu()
	: isActive(false)
{

}

PauseMenu::~PauseMenu()
{
	delete pausePanel;
	pausePanel = 0;
	delete pauseText;
	pauseText = 0;
	delete quit;
	quit = 0;
	delete highlight;
	highlight = 0;
}

bool PauseMenu::Initialise(Renderer & renderer)
{
	pausePanel = renderer.CreateSprite("sprites\\menu\\blackbackground.png");
	pausePanel->SetX(renderer.GetWidth() / 2);
	pausePanel->SetY(renderer.GetHeight() / 2);
	pausePanel->SetScale(5.0f);
	pausePanel->SetAlpha(0.6f);

	renderer.CreateStaticText("Game Paused", 40);
	pauseText = renderer.CreateSprite("Game Paused");
	pauseText->SetX(renderer.GetWidth() / 2);
	pauseText->SetY(renderer.GetHeight() / 2 - 300.0f);

	quit = new Button();
	quit->setToggleable();
	renderer.CreateStaticText("Quit Game", 28);
	quit->SetSprite(renderer.CreateSprite("Quit Game"));
	quit->SetTransform(renderer.GetWidth() / 2, renderer.GetHeight() / 2 + 280.0f, 1.0f);

	highlight = renderer.CreateSprite("sprites\\menu\\buttonhighlight.png");
	highlight->SetX(quit->GetSprite()->GetX());
	highlight->SetY(quit->GetSprite()->GetY());

	return false;
}

void PauseMenu::Process(float deltaTime, InputSystem & inputSystem)
{
	pauseText->Process(deltaTime);
	pausePanel->Process(deltaTime);
	quit->Process(deltaTime, inputSystem);

	if (quit->GetMousePressed()) {
		Game::GetInstance().Quit();
	}
}

void PauseMenu::Draw(Renderer & renderer)
{
	pausePanel->Draw(renderer);
	pauseText->Draw(renderer);
	highlight->Draw(renderer);
	quit->Draw(renderer);
}

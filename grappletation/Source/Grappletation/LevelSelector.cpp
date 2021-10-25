
#include "levelselector.h"

LevelSelector::LevelSelector()
{
}

LevelSelector::~LevelSelector()
{
	delete OptionsText;
	OptionsText = 0;
	delete Panel;
	Panel = 0;
	delete StartLevel;
	StartLevel = 0;
	delete GoBack;
	GoBack = 0;
	delete SaveSettingsHighlight;
	SaveSettingsHighlight = 0;
	delete GoBackHighlight;
	GoBackHighlight = 0;
}

bool LevelSelector::Initialise(Renderer & renderer)
{
	StartLevel = new Button();
	StartLevel->setToggleable();
	renderer.CreateStaticText("Start Level", 28);
	StartLevel->SetSprite(renderer.CreateSprite("Start Level"));
	StartLevel->SetTransform(renderer.GetWidth() / 2 - 100.0f, renderer.GetHeight() / 2 + 185.0f, 1.0f);

	GoBack = new Button();
	GoBack->setToggleable();
	renderer.CreateStaticText("Go Back", 28);
	GoBack->SetSprite(renderer.CreateSprite("Go Back"));
	GoBack->SetTransform(renderer.GetWidth() / 2 + 100.0f, renderer.GetHeight() / 2 + 185.0f, 1.0f);

	renderer.CreateStaticText("Level Select", 42);
	OptionsText = renderer.CreateSprite("Level Select");
	OptionsText->SetX(renderer.GetWidth() / 2);
	OptionsText->SetY(renderer.GetHeight() / 2 - 160.0f);

	Panel = renderer.CreateSprite("sprites\\menu\\levelselecter.png");
	Panel->SetX(renderer.GetWidth() / 2);
	Panel->SetY(renderer.GetHeight() / 2 + 20);
	Panel->SetScale(3.0f);

	SaveSettingsHighlight = renderer.CreateSprite("sprites\\menu\\buttonhighlight.png");
	SaveSettingsHighlight->SetX(StartLevel->GetSprite()->GetX());
	SaveSettingsHighlight->SetY(StartLevel->GetSprite()->GetY());
	SaveSettingsHighlight->SetScale(1.15f);

	GoBackHighlight = renderer.CreateSprite("sprites\\menu\\buttonhighlight.png");
	GoBackHighlight->SetX(GoBack->GetSprite()->GetX());
	GoBackHighlight->SetY(GoBack->GetSprite()->GetY());
	GoBackHighlight->SetScale(1.15f);

	return false;
}

void LevelSelector::Process(float deltaTime, InputSystem& inputSystem)
{
	GoBack->Process(deltaTime, inputSystem);
	StartLevel->Process(deltaTime, inputSystem);

	if (StartLevel->GetMousePressed()) {
		SaveUserSettings();
	}

	if (GoBack->GetMousePressed()) {
		gotoMain = true;
	}
}

void LevelSelector::Draw(Renderer & renderer)
{
	Panel->Draw(renderer);
	OptionsText->Draw(renderer);
	GoBackHighlight->Draw(renderer);
	SaveSettingsHighlight->Draw(renderer);
	GoBack->Draw(renderer);
	StartLevel->Draw(renderer);
}

bool LevelSelector::SaveUserSettings()
{
	return false;
}




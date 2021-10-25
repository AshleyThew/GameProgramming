// COMP710 Steffan Hooper
// This include:
#include "SceneGrappletation.h"

// Local includes:
#include "renderer.h"
#include "imgui.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "Player.h"
#include "grappleplayer.h"
#include "bullet.h"
#include "Gem.h"
#include "portalplayer.h"

// Library includes:
#include <cassert>
#include <cstdlib>

SceneGrappletation::SceneGrappletation()
	: level(0)
	, m_curCharacter(0)
	, turretmode(0)
{

}

SceneGrappletation::~SceneGrappletation()
{
	delete level;
	level = 0;

	delete menu;
	menu = 0;

	delete pause;
	pause = 0;

	delete m_characters[0];
	delete m_characters[1];
	m_characters[0] = 0;
	m_characters[1] = 0;

}

bool
SceneGrappletation::Initialise(Renderer& renderer)
{
	menu = new MainMenu();
	menu->Initialise(renderer);
	pause = new PauseMenu();
	pause->Initialise(renderer);
	level = new LevelManager();
	level->Initialise(renderer);

	Player* portalCharacter = new PortalPlayer();
	portalCharacter->Initialise(renderer);

	Player* grappleCharacter = new GrapplePlayer();
	grappleCharacter->Initialise(renderer);

	m_characters[0] = portalCharacter;
	m_characters[1] = grappleCharacter;

	StartLevel();

	i = 0;
	return true;
}

void
SceneGrappletation::StartLevel()
{
	SceneGrappletation* scene = this;

	Player* portalCharacter = m_characters[0];
	portalCharacter->SetScale(level->GetLevelScale() / 1.5);
	portalCharacter->Start(scene);
	portalCharacter->SetPosition(level->GetPortalGunnerStartLocation().x, level->GetPortalGunnerStartLocation().y + 10);

	Player* grappleCharacter = m_characters[1];
	grappleCharacter->SetScale(level->GetLevelScale() / 1.5);
	grappleCharacter->SetSelected(true);
	grappleCharacter->Start(scene);
	grappleCharacter->SetPosition(level->GetGrapplerStartLocation().x, level->GetGrapplerStartLocation().y + 10);

	level->ResetAllLevels();
}

void
SceneGrappletation::Process(float deltaTime, InputSystem& inputSystem, SoundManager& soundManager)
{
	menu->Process(deltaTime, inputSystem);

	if (!menu->isActive) {
		if (inputSystem.GetKeyState(SDL_SCANCODE_ESCAPE) == BS_PRESSED)
		{
			if (pause->isActive) {
				pause->isActive = false;
			}
			else {
				pause->isActive = true;
			}
		}

		if (!pause->isActive) {

			level->Process(deltaTime, inputSystem, soundManager);

			m_characters[0]->Process(deltaTime, inputSystem, soundManager);
			m_characters[1]->Process(deltaTime, inputSystem, soundManager);



			XboxController* controller = NULL;
			if (inputSystem.GetNumberOfControllersAttached())
			{
				controller = inputSystem.GetController(0);
			}

			ButtonState aKeyboardState = inputSystem.GetKeyState(SDL_SCANCODE_A);
			if (aKeyboardState == BS_PRESSED || (controller != NULL && controller->GetButtonState(SDL_CONTROLLER_BUTTON_Y) == BS_PRESSED))
			{
				m_characters[0]->SetSelected(!m_characters[0]->GetSelected());
				m_characters[1]->SetSelected(!m_characters[1]->GetSelected());
			}

			std::vector<Gem*> gems = level->GetAllGems();

			int gemCount = 0;

			for (std::vector<Gem*>::iterator itGem = gems.begin(); itGem != gems.end(); itGem++)
			{
				Gem*& gem = *itGem;
				if (gem->GetCollected())
				{
					gemCount++;
				}
			}

			if (gemCount == gems.size())
			{
				if (level->GetLevel() == 2)
				{
					level->SetLevel(0);
					menu->isActive = true;
				}
				else
				{
					level->SetLevel(level->GetLevel() + 1);
				}
				StartLevel();
			}
		}
	}
}

void
SceneGrappletation::Draw(Renderer& renderer)
{
	if (!menu->isActive)
	{
		level->Draw(renderer);
		m_characters[0]->Draw(renderer);
		m_characters[1]->Draw(renderer);
	}
	else if(menu->isActive)
	{
		menu->Draw(renderer);
	}

	if (pause->isActive) {
		pause->Draw(renderer);
	}
}

void
SceneGrappletation::DebugDraw()
{
	ImGui::Text("Grappletation Scene");

	static float fontScale = 1.5f;

	ImGui::SliderFloat("Font scale", &fontScale, 0.01f, 2.0f);

	ImGui::SetWindowFontScale(fontScale);

	m_characters[0]->DebugDraw();
	m_characters[1]->DebugDraw();

	level->DebugDraw();


	//ImGui::InputInt("turret current mode", &turretmode);
}

LevelManager*
SceneGrappletation::GetLevelManager()
{
	return level;
}

// COMP710 GP Framework 2021
// This include:
#include "scenecontrols.h"
// Local includes:
#include "renderer.h"
#include "sprite.h"
#include "game.h"
#include "logmanager.h"
#include "xboxcontroller.h"
#include "imgui/imgui.h"
// Library includes:
#include <cassert>
SceneControls::SceneControls()
	: m_opacity(1.0f)
{
}
SceneControls::~SceneControls()
{
	delete m_controls;
	m_controls = 0;
}

bool
SceneControls::Initialise(Renderer& renderer)
{
	m_controls = renderer.CreateSprite("sprites\\controls.png");
	const int SCREEN_WIDTH = renderer.GetWidth();
	const int SCREEN_HEIGHT = renderer.GetHeight();
	m_controls->SetX(SCREEN_WIDTH / 2);
	m_controls->SetY(SCREEN_HEIGHT / 2);
	m_controls->SetScale(0.5f);

	renderer.SetClearColour(0, 0, 0);

	return true;
}

void
SceneControls::Process(float deltaTime)
{

}

void
SceneControls::Draw(Renderer& renderer)
{
	m_controls->Draw(renderer);
}

void
SceneControls::ProcessInput(InputSystem& inputSystem)
{
	int leftResult = inputSystem.GetMouseButtonState(SDL_BUTTON_LEFT);
	XboxController* controller = inputSystem.GetController(0);
	ButtonState xboxA = controller->GetButtonState(SDL_CONTROLLER_BUTTON_A);

	if (leftResult == BS_PRESSED || xboxA == BS_PRESSED)
	{
		Game::GetInstance().StartGame();
	}
}

void
SceneControls::DebugDraw()
{
	ImGui::Text("Scene Controls");
}
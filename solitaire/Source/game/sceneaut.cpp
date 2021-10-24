// COMP710 GP Framework 2021
// This include:
#include "sceneaut.h"
// Local includes:
#include "renderer.h"
#include "sprite.h"
#include "game.h"
#include "logmanager.h"
#include "imgui/imgui.h"
// Library includes:
#include <cassert>
SceneAUT::SceneAUT()
	: m_opacity(1.0f),
	m_totalTime(0.0f)
{
}
SceneAUT::~SceneAUT()
{
	delete m_autLogo;
	m_autLogo = 0;

	delete m_autText;
	m_autText = 0;
}

bool
SceneAUT::Initialise(Renderer& renderer)
{
	m_autLogo = renderer.CreateSprite("sprites\\aut-logo-block.png");
	const int SCREEN_WIDTH = renderer.GetWidth();
	const int SCREEN_HEIGHT = renderer.GetHeight();
	m_autLogo->SetX(SCREEN_WIDTH / 2);
	m_autLogo->SetY(SCREEN_HEIGHT / 2);
	//m_autLogo->SetAngle(180);
	m_autLogo->SetScale(0.5f);

	renderer.SetClearColour(0, 0, 0);

	m_autText = renderer.CreateStaticText("Solitaire Universe", 65);

	m_autText->SetX(SCREEN_WIDTH / 2);
	m_autText->SetY(SCREEN_HEIGHT / 2 + m_autLogo->GetHeight() / 2 + m_autText->GetHeight() / 2);

	return true;
}

void
SceneAUT::Process(float deltaTime)
{
	m_totalTime += deltaTime;
	if (m_totalTime > 10.0f) {
		Game::GetInstance().MainMenu();
	}
}

void
SceneAUT::Draw(Renderer& renderer)
{
	m_autLogo->Draw(renderer);
	m_autText->Draw(renderer);
}

void
SceneAUT::ProcessInput(InputSystem& inputSystem)
{

}

void
SceneAUT::DebugDraw()
{
	ImGui::Text("Scene AUT");
}
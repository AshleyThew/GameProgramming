// COMP710 GP Framework 2021
// This include:
#include "game.h"
// Library includes:
#include "sceneaut.h"
#include "scenecontrols.h"
#include "scenesolitaire.h"
#include "renderer.h"
#include "logmanager.h"
#include "xboxcontroller.h"
#include "inputsystem.h"
#include "imgui/imgui_impl_sdl.h"
#include <string>
#include <algorithm>
// Static Members:
Game* Game::sm_pInstance = 0;
Game&
Game::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new Game();
	}
	return (*sm_pInstance);
}
void
Game::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}
Game::Game()
	: m_pRenderer(0)
	, m_fElapsedSeconds(0)
	, m_fExecutionTime(0)
	, m_bLooping(true)
	, m_iCurrentScene(0)
{
}
Game::~Game()
{
	delete m_pRenderer;
	m_pRenderer = 0;
	for (size_t index = 0; index < m_scenes.size(); index++)
	{
		delete m_scenes[index];
		m_scenes[index] = 0;
	}
	delete m_pInputSystem;
	m_pInputSystem = 0;
}
void
Game::Quit()
{
	m_bLooping = false;
}
bool
Game::Initialise()
{
	int bbWidth = 1120;
	int bbHeight = 900;
	m_pRenderer = new Renderer();
	if (!m_pRenderer->Initialise(true, bbWidth, bbHeight))
	{
		LogManager::GetInstance().Log("Renderer failed to initialise!");
		return false;
	}
	bbWidth = m_pRenderer->GetWidth();
	bbHeight = m_pRenderer->GetHeight();
	m_iLastTime = SDL_GetPerformanceCounter();
	m_pRenderer->SetClearColour(0, 255, 255);

	Scene* pScene1 = 0;
	pScene1 = new SceneAUT();
	pScene1->Initialise(*m_pRenderer);
	m_scenes.push_back(pScene1);

	Scene* pScene2 = 0;
	pScene2 = new SceneControls();
	pScene2->Initialise(*m_pRenderer);
	m_scenes.push_back(pScene2);

	Scene* pScene3 = 0;
	pScene3 = new SceneSolitaire();
	pScene3->Initialise(*m_pRenderer);
	m_scenes.push_back(pScene3);

	m_pInputSystem = new InputSystem();
	m_pInputSystem->Initialise();
	m_pInputSystem->ShowMouseCursor(true);
	return true;
}

bool
Game::DoGameLoop()
{
	const float stepSize = 1.0f / 60.0f;
	// TODO: Process input here!
	m_pInputSystem->ProcessInput();
	ProcessInput();
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		continue;
	}
	if (m_bLooping)
	{
		Uint64 current = SDL_GetPerformanceCounter();
		float deltaTime = (current - m_iLastTime) / static_cast<float>(SDL_GetPerformanceFrequency());
		m_iLastTime = current;
		m_fExecutionTime += deltaTime;
		Process(deltaTime);
		SDL_Event event;
		while (SDL_PollEvent(&event) != 0)
		{
			ImGuiIO& io = ImGui::GetIO();
			ImGui_ImplSDL2_ProcessEvent(&event);
		}
#ifdef USE_LAG
		m_fLag += deltaTime;
		int innerLag = 0;
		while (m_fLag >= stepSize)
		{
			Process(stepSize);
			m_fLag -= stepSize;
			++m_iUpdateCount;
			++innerLag;
		}
#endif //USE_LAG
		Draw(*m_pRenderer);
	}


	return m_bLooping;
}

void Game::ProcessInput()
{
	m_scenes[m_iCurrentScene]->ProcessInput(*m_pInputSystem);

	XboxController* controller = m_pInputSystem->GetController(0);
	ButtonState xboxSelect = controller->GetButtonState(SDL_CONTROLLER_BUTTON_BACK);

	if (xboxSelect == BS_PRESSED) {
		ToggleDebugWindow();
	}

	if (m_bShowDebugWindow) {
		ButtonState xboxDpadLeft = controller->GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_LEFT);
		if (xboxDpadLeft == BS_PRESSED) {
			m_iCurrentScene--;
			if (m_iCurrentScene < 0) {
				m_iCurrentScene = 0;
			}
		}
		ButtonState xboxDpadRight = controller->GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
		if (xboxDpadRight == BS_PRESSED) {
			m_iCurrentScene++;
			int max = m_scenes.size() - 1;
			if (m_iCurrentScene > max) {
				m_iCurrentScene = max;
			}
		}
	}

	float max = 32768;
	float dead = 0.2f;
	float deadZones = max * dead;

	float stickX = controller->GetLeftStick().x;
	float stickY = controller->GetLeftStick().y;

	float modX = 0;
	float modY = 0;
	
	if (stickX < -deadZones || stickX > deadZones)
	{
		m_controllerRamp.x = std::min(m_controllerRamp.x + 0.001f, 2.0f);
		modX = stickX / max * m_controllerRamp.x;
	}
	else
	{
		m_controllerRamp.x = 1;
	}

	if (stickY < -deadZones || stickY > deadZones) 
	{
		m_controllerRamp.y = std::min(m_controllerRamp.y + 0.001f, 2.0f);
		modY = stickY / max * m_controllerRamp.y;
	}
	else
	{
		m_controllerRamp.y = 1;
	}

	if (modX != 0.0 || modY != 0.0)
	{
		m_pInputSystem->SetMouseRelative(modX, modY);
	}
}

void
Game::Process(float deltaTime)
{
	ProcessFrameCounting(deltaTime);
	// TODO: Add game objects to process here!
	m_scenes[m_iCurrentScene]->Process(deltaTime);
}

void
Game::Draw(Renderer& renderer)
{
	++m_iFrameCount;
	renderer.Clear();
	// TODO: Add game objects to draw here!
	m_scenes[m_iCurrentScene]->Draw(renderer);
	DebugDraw();
	renderer.Present();
}
void
Game::ProcessFrameCounting(float deltaTime)
{
	// Count total simulation time elapsed:
	m_fElapsedSeconds += deltaTime;
	// Frame Counter:
	if (m_fElapsedSeconds > 1.0f)
	{
		m_fElapsedSeconds -= 1.0f;
		m_iFPS = m_iFrameCount;
		m_iFrameCount = 0;
	}
}

void
Game::DebugDraw()
{
	if (!m_bShowDebugWindow) {
		return;
	}

	bool open = true;
	ImGui::Begin("Debug Window", &open, ImGuiWindowFlags_MenuBar);
	ImGui::Text("COMP710 GP Framework (%s)", "2021, S2");
	ImGui::Text("%d", m_iFPS);

	XboxController* controller = m_pInputSystem->GetController(0);
	ImGui::Text("Controller X: %f Y: %f",controller->GetLeftStick().x, controller->GetLeftStick().y);

	float max = 32768;
	float dead = 0.1f;
	float deadZones = max * dead;

	float stickX = controller->GetLeftStick().x;
	float stickY = controller->GetLeftStick().y;

	float modX = 0;
	float modY = 0;

	if (stickX < -deadZones || stickX > deadZones)
	{
		modX = stickX / max * m_controllerRamp.x;
	}
	if (stickY < -deadZones || stickY > deadZones)
	{
		modY = stickY / max * m_controllerRamp.y;
	}

	ImGui::Text("Test X: %f Y: %f", modX, modY);
	ImGui::Text("Ramp X: %f Y: %f", m_controllerRamp.x, m_controllerRamp.y);

	if (ImGui::Button("Quit"))
	{
		Quit();
	}
	ImGui::SliderInt("Active scene", &m_iCurrentScene, 0, m_scenes.size() - 1, "%d");
	m_scenes[m_iCurrentScene]->DebugDraw();
	ImGui::End();
}

void
Game::ToggleDebugWindow()
{
	m_bShowDebugWindow = !m_bShowDebugWindow;
}

void
Game::MainMenu()
{
	m_iCurrentScene = 1;
}

void
Game::StartGame()
{
	m_iCurrentScene = 2;
	SceneSolitaire* scene = (SceneSolitaire*)m_scenes[m_iCurrentScene];
	scene->CreateGame(*m_pRenderer);
}

void
Game::PauseMenu()
{
	m_iCurrentScene = 3;
}
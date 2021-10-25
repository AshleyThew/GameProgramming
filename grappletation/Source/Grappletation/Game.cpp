// COMP710 GP Framework 2021
// This include:
#include "game.h"
// Library includes:
#include "renderer.h"
#include "logmanager.h"
#include "sprite.h"
#include "scene.h"
#include "scenegrappletation.h"
#include "InputSystem.h"
#include "SoundManager.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
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
	, m_bLooping(true)
	, m_pInputSystem(0)
{
}
Game::~Game()
{
	delete m_pRenderer;
	m_pRenderer = 0;
	delete m_pInputSystem;
	m_pInputSystem = 0;
	delete soundManager;
	soundManager = 0;

	for(int i = 0; i < m_scenes.size(); i++)
	{
		delete m_scenes.at(i);
		m_scenes.at(i) = 0;
	}
}
void
Game::Quit()
{
	m_bLooping = false;
}
bool
Game::Initialise()
{
	int bbWidth = 1920;
	int bbHeight = 1080;
	m_pRenderer = new Renderer();
	// WINDOWED = true, FULLSCREEN = false:
	if (!m_pRenderer->Initialise(true, bbWidth, bbHeight))
	{
		LogManager::GetInstance().Log("Renderer failed to initialise!");
		return false;
	}
	bbWidth = m_pRenderer->GetWidth();
	bbHeight = m_pRenderer->GetHeight();
	m_iLastTime = SDL_GetPerformanceCounter();
	m_pRenderer->SetClearColour(200, 200, 200);

	m_pInputSystem = new InputSystem();
	m_pInputSystem->Initialise();

	soundManager = new SoundManager();
	soundManager->Initialise();
	
	Scene* pScene = 0;
	pScene = new SceneGrappletation();
	pScene->Initialise(*m_pRenderer);
	m_scenes.push_back(pScene);

	pScene = 0;
	m_iCurrentScene = 0;

	return true;
}
bool
Game::DoGameLoop()
{
	const float stepSize = 1.0f / 60.0f;
	// TODO: Process input here!

	m_pInputSystem->ProcessInput();
	soundManager->Process();

	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplSDL2_ProcessEvent(&event);
	}
	if (m_bLooping)
	{
		Uint64 current = SDL_GetPerformanceCounter();
		float deltaTime = (current - m_iLastTime) / static_cast<float>(SDL_GetPerformanceFrequency());
		m_iLastTime = current;
		m_fExecutionTime += deltaTime;
		Process(deltaTime);

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
void
Game::Process(float deltaTime)
{
	ProcessFrameCounting(deltaTime);
	m_scenes[m_iCurrentScene]->Process(deltaTime, *m_pInputSystem, *soundManager);
}
void
Game::Draw(Renderer& renderer)
{
	++m_iFrameCount;
	renderer.Clear();
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
	
	bool open = true;
	ImGui::Begin("Debug Window", &open, ImGuiWindowFlags_MenuBar);
	ImGui::Text("COMP710 GP Framework (%s)", "2021, S2");
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

	m_pInputSystem->ShowMouseCursor(m_bShowDebugWindow);
}
// COMP710 GP Framework 2021
#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include "vector2.h"

// Forward declarations:
class Scene;
class Renderer;
class InputSystem;
class Game
{
	// Member methods:
public:
	static Game& GetInstance();
	static void DestroyInstance();
	bool Initialise();
	bool DoGameLoop();
	void Quit();
	void ToggleDebugWindow();
	void MainMenu();
	void StartGame();
	void PauseMenu();

protected:
	void Process(float deltaTime);
	void Draw(Renderer& renderer);
	void ProcessFrameCounting(float deltaTime);
	void DebugDraw();
	void ProcessInput();

private:
	Game();
	~Game();
	Game(const Game& game);
	Game& operator=(const Game& game);

// Member data:
public:
protected:
	static Game* sm_pInstance;
	Renderer* m_pRenderer;
	__int64 m_iLastTime;
	float m_fExecutionTime;
	float m_fElapsedSeconds;
	int m_iFrameCount;
	int m_iFPS;
	std::vector<Scene*> m_scenes;
	int m_iCurrentScene;
#ifdef USE_LAG
	float m_fLag;
	int m_iUpdateCount;
#endif // USE_LAG
	bool m_bLooping;
	bool m_bShowDebugWindow;
	InputSystem* m_pInputSystem;
	Vector2 m_controllerRamp;
private:
};
#endif // __GAME_H__
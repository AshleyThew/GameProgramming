#include "TestScene.h"
#include "Renderer.h"
#include "Game.h"
#include "SoundManager.h"
#include "InputSystem.h"

TestScene::TestScene()
{

}	
TestScene::~TestScene()
{

}
bool
TestScene::Initialise(Renderer& renderer)
{
	sprite = renderer.CreateSprite("Portal Gun Character Sheet.png");
	sprite->SetX(500);
	sprite->SetY(500);
	return false;
}
void
TestScene::Process(float deltaTime, InputSystem& inputSystem, SoundManager& soundManager)
{
	if (inputSystem.GetKeyState(SDL_SCANCODE_SPACE) == BS_PRESSED)
	{

	}
}
void
TestScene::Draw(Renderer& renderer)
{
	sprite->Draw(renderer);
}

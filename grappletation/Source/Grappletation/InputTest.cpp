#include "InputTest.h"
#include "renderer.h"
#include "InputSystem.h"
#include "logmanager.h"
#include "SDL_scancode.h"
#include "imgui.h"
#include "inputsystem.h"

InputTest::InputTest()
{
}


InputTest::~InputTest()
{
}

bool
InputTest::Initialise(Renderer& renderer)
{
	return false;
}

void
InputTest::Process(float deltaTime)
{
	/*
	ButtonState leftArrowState = (.GetKeyState(SDL_SCANCODE_LEFT)); 
	if (leftArrowState == BS_PRESSED) 
	{ 
		LogManager::GetInstance().Log("Left arrow key pressed."); 
	}
	else if (leftArrowState == BS_RELEASED)
	{
		LogManager::GetInstance().Log("Left arrow key released.");
	}
	*/
}

void
InputTest::Draw(Renderer& renderer)
{
}

void
InputTest::DebugDraw()
{
	
}

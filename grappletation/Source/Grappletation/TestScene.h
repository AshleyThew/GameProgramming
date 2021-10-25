#pragma once

#include "Scene.h"
#include "InputSystem.h"
#include "SoundManager.h"
#include "Renderer.h"
#include "Game.h"
#include "Sprite.h"

class TestScene : public Scene
{
public:
		TestScene();
		~TestScene();
		virtual bool Initialise(Renderer& renderer);
		virtual void Process(float deltaTime, InputSystem& inputSystem, SoundManager& soundManager);
		virtual void Draw(Renderer& renderer);	
protected:
private:

public:
protected:
private:
	Sprite* sprite;
};


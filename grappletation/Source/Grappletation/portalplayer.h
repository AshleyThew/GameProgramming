#pragma once

#include "Player.h"

class Renderer;
class InputSystem;
class SoundManager;

class PortalPlayer : public Player
{
public:
	PortalPlayer();
	~PortalPlayer();
	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime, InputSystem& inputSystem, SoundManager& soundManager);
	virtual void Draw(Renderer& renderer);

protected:
private:
	PortalPlayer(const PortalPlayer& bullet);
	PortalPlayer& operator=(const PortalPlayer& bullet);
};
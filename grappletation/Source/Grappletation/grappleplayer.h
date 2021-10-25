#pragma once

#include "Player.h"

class Renderer;
class InputSystem;
class SoundManager;

class GrapplePlayer : public Player
{
public:
	GrapplePlayer();
	~GrapplePlayer();
	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime, InputSystem& inputSystem, SoundManager& soundManager);
	virtual void Draw(Renderer& renderer);

protected:
private:
	GrapplePlayer(const GrapplePlayer& bullet);
	GrapplePlayer& operator=(const GrapplePlayer& bullet);
};
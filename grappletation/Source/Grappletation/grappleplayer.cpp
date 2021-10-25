#include "grappleplayer.h"

GrapplePlayer::GrapplePlayer()
{

}

GrapplePlayer::~GrapplePlayer()
{

}

bool
GrapplePlayer::Initialise(Renderer& renderer)
{
	m_pAnimatedSprite = renderer.CreateAnimatedSprite("..\\Assets\\Grapple Character Sheet.png");
	Player::Initialise(renderer);
	return false;
}

void
GrapplePlayer::Process(float deltaTime, InputSystem& inputSystem, SoundManager& soundManager)
{
	Player::Process(deltaTime, inputSystem, soundManager);
}

void
GrapplePlayer::Draw(Renderer& renderer)
{
	Player::Draw(renderer);
}
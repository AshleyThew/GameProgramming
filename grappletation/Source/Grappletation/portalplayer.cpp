#include "portalplayer.h"

PortalPlayer::PortalPlayer()
{

}

PortalPlayer::~PortalPlayer()
{

}

bool
PortalPlayer::Initialise(Renderer& renderer)
{
	m_pAnimatedSprite = renderer.CreateAnimatedSprite("..\\Assets\\Portal Gun Character Sheet.png");
	Player::Initialise(renderer);
	return false;
}

void
PortalPlayer::Process(float deltaTime, InputSystem& inputSystem, SoundManager& soundManager)
{
	Player::Process(deltaTime, inputSystem, soundManager);
}

void
PortalPlayer::Draw(Renderer& renderer)
{
	Player::Draw(renderer);
}
// COMP710 Dhanan Patel
// This include:
#include "bullet.h"

// Local includes:
#include "renderer.h"
#include "AnimatedSprite.h"

// Library includes:
#include <cassert>

Bullet::Bullet()
	: bullet_speed(0.0f)
{
}

Bullet::~Bullet()
{

}

bool
Bullet::Initialise(Renderer& renderer, float x, float y, float scale, bool ShootRight)
{
	m_position.x = x + 40;
	m_position.y = y - 20;
	bullet_speed = 15.0f * scale;

	m_pSprite = renderer.CreateSprite("..\\Assets\\diamond.png");
	m_pSprite->SetScale(scale * 0.1f);
	SetDead(false);

	if (ShootRight == false)
	{
		m_velocity.x = bullet_speed;
		m_velocity.y = 0;
	}
	else
	{
		m_velocity.x = (-bullet_speed);
		m_velocity.y = 0;
	}

	return false;
}

void
Bullet::Process(float deltaTime)
{
	Entity::Process(deltaTime);
}

void
Bullet::Draw(Renderer& renderer)
{
	Entity::Draw(renderer);
}

void
Bullet::HitPlayer()
{
	SetDead(true);
	m_velocity.x = 0;
	m_velocity.y = 0;
}
#include "entity.h"
#include "sprite.h"
#include "logmanager.h"
#include "vector2.h"
#include "AnimatedSprite.h"
#include <cmath>
#include <math.h>

#define PI 3.14159265358979323846
#define DEGTORAD PI / 180;

Entity::Entity()
	: m_pSprite{ 0 }
	, m_pAnimatedSprite{0}
	, m_position{0, 0}
	, m_velocity{0, 0}
	, m_bAlive{false}
{
}

Entity::~Entity()
{
	delete m_pAnimatedSprite;
	delete m_pSprite;
}

bool
Entity::Initialise(Renderer& renderer)
{


	return false;
}

void 
Entity::Process(float deltaTime)
{
	if (IsAlive())
	{
		m_position.x -= m_velocity.x * deltaTime;
		m_position.y -= m_velocity.y * deltaTime;
		if (m_pSprite)
		{
			m_pSprite->Process(deltaTime);
			m_pSprite->SetX(GetPosition().x);
			m_pSprite->SetY(GetPosition().y);
		}
		else if (m_pAnimatedSprite)
		{
			m_pAnimatedSprite->Process(deltaTime);
			m_pAnimatedSprite->SetX(GetPosition().x);
			m_pAnimatedSprite->SetY(GetPosition().y);
		}
	}
}

void
Entity::Draw(Renderer& renderer)
{
	if (IsAlive())
	{
		if (m_pSprite)
		{
			m_pSprite->Draw(renderer);
		}
		else if (m_pAnimatedSprite)
		{
			m_pAnimatedSprite->Draw(renderer);

		}
	}
}

void 
Entity::Rotate(float direction)
{
	if (m_pSprite)
	{
		float currentAngle = m_pSprite->GetAngle();
		m_pSprite->SetAngle(currentAngle + direction);
	}
	else if (m_pAnimatedSprite)
	{
		float currentAngle = m_pAnimatedSprite->GetAngle();
		m_pAnimatedSprite->SetAngle(currentAngle + direction);
	}
}

bool
Entity::IsAlive() const
{
	return m_bAlive;
}

void
Entity::SetDead(bool dead)
{
	m_bAlive = !dead;
}

float
Entity::GetRadius()
{
	float height = 0;
	float width = 0;
	if (m_pSprite)
	{
		height = (float)m_pSprite->GetHeight() / 2;
		width = (float)m_pSprite->GetWidth() / 2;
	}
	else if (m_pAnimatedSprite)
	{
		height = (float)m_pAnimatedSprite->GetHeight() / 2;
		width = (float)m_pAnimatedSprite->GetWidth() / 2;
	}


	float radius = sqrt(pow(height, 2) + pow(width, 2));
	return radius;
}

Vector2
Entity::GetFacingDirection()
{
	float angle = 0;
	if (m_pSprite)
	{
		angle = m_pSprite->GetAngle() * DEGTORAD;
	}
	else if (m_pAnimatedSprite)
	{
		angle = m_pAnimatedSprite->GetAngle() * DEGTORAD;
	}
	float x = sin(angle);
	float y = cos(angle);

	float xRounded = roundf(x * 1000) / 1000;
	float yRounded = roundf(y * 1000) / 1000;

	return Vector2(xRounded, yRounded);
}

Vector2&
Entity::GetPosition()
{
	return m_position;
}

Vector2&
Entity::GetVelocity()
{
	return m_velocity;
}

bool
Entity::IsCollidingWith(Entity& entity)
{
	if (IsAlive() && entity.IsAlive())
	{
		float height = 0;
		float width = 0;
		float angle = 0;
		float newHeight = 0;
		if (m_pAnimatedSprite)
		{
			newHeight =
				angle = m_pAnimatedSprite->GetAngle() * DEGTORAD;
			height = abs((m_pAnimatedSprite->GetHeight() / 2) * cos(angle) + (m_pAnimatedSprite->GetWidth() / 2) * sin(angle));
			width = abs((m_pAnimatedSprite->GetWidth() / 2) * cos(angle) + (m_pAnimatedSprite->GetHeight() / 2) * sin(angle));
		}
		if (m_pSprite)
		{
			angle = m_pSprite->GetAngle() * DEGTORAD;
			height = abs((m_pSprite->GetHeight() / 2) * cos(angle) + (m_pSprite->GetWidth() / 2) * sin(angle));
			width = abs((m_pSprite->GetWidth() / 2) * cos(angle) + (m_pSprite->GetHeight() / 2) * sin(angle));
		}

		Vector2 position = GetPosition();
		Vector2* topLeftBoundThis = new Vector2(position.x - width, position.y - height);
		Vector2* bottomRightBoundThis = new Vector2(position.x + width, position.y + height);

		if (entity.m_pAnimatedSprite)
		{
			angle = entity.m_pAnimatedSprite->GetAngle() * DEGTORAD;
			height = abs((entity.m_pAnimatedSprite->GetHeight() / 2) * cos(angle) + (entity.m_pAnimatedSprite->GetWidth() / 2) * sin(angle));
			width = abs((entity.m_pAnimatedSprite->GetWidth() / 2) * cos(angle) + (entity.m_pAnimatedSprite->GetHeight() / 2) * sin(angle));
		}
		if (entity.m_pSprite)
		{
			angle = entity.m_pSprite->GetAngle() * DEGTORAD;
			height = abs((entity.m_pSprite->GetHeight() / 2) * cos(angle) + (entity.m_pSprite->GetWidth() / 2) * sin(angle));
			width = abs((entity.m_pSprite->GetWidth() / 2) * cos(angle) + (entity.m_pSprite->GetHeight() / 2) * sin(angle));
		}

		position.x = entity.GetPosition().x;
		position.y = entity.GetPosition().y;
		Vector2* topLeftBoundOther = new Vector2(position.x - width, position.y - height);
		Vector2* bottomRightBoundOther = new Vector2(position.x + width, position.y + height);

		bool colliding =
			(topLeftBoundThis->x < bottomRightBoundOther->x&& bottomRightBoundThis->x > topLeftBoundOther->x)
			&&
			(topLeftBoundThis->y < bottomRightBoundOther->y&& bottomRightBoundThis->y > topLeftBoundOther->y);

		delete topLeftBoundThis;
		delete bottomRightBoundThis;
		delete topLeftBoundOther;
		delete bottomRightBoundOther;

		return colliding;
	}

	return false;
}

void
Entity::SetAngle(float angle)
{
	if (m_pSprite)
	{
		m_pSprite->SetAngle(angle);
	}
	else if (m_pAnimatedSprite)
	{
		m_pAnimatedSprite->SetAngle(angle);
	}
}

#include "Door.h"
#include "Renderer.h"
#include "Vector2.h"
#include "Sprite.h"

Door::Door(int x, int y)
	: open(false)
	, currentAnimationFrame(-0.001f)
{
	id.x = x;
	id.y = y;
}

Door::~Door()
{
}

bool Door::Initialise(Renderer& renderer, int rotation, float scale)
{	
	m_pSprite = renderer.CreateSprite("..\\Assets\\Objects\\Door.png");
	Rotate(rotation);
	m_pSprite->SetScale(scale);
	Vector2 facingDirection = GetFacingDirection();
	initialPosition.x = (scale * 8) + (id.x * scale * 16) - (facingDirection.x * scale * 8);
	initialPosition.y = (scale * 8) + (id.y * scale * 16) - (facingDirection.y * scale * 8);
	m_position.x = initialPosition.x;
	m_position.y = initialPosition.y;
	MAXDISTANCE.x = facingDirection.x * scale * 32;
	MAXDISTANCE.y = facingDirection.y * scale * 32;

	SetDead(false);
	return false;
}

void Door::Process(float deltaTime)
{
	Entity::Process(deltaTime);
	if ((currentAnimationFrame >= 0 && !open) || (currentAnimationFrame <= 1 && open))
	{
		PlayAnimation(deltaTime);
	}
}

void Door::Draw(Renderer& renderer)
{
	Entity::Draw(renderer);
}

void Door::SetOpen(bool pressed)
{
	//Rotate(90);
	this->open = pressed;
}

Vector2 Door::GetID()
{
	return id;
}

void Door::PlayAnimation(float deltaTime)
{
	int direction = (open * 2) - 1;
	currentAnimationFrame += deltaTime * MOVEMENTSPEED * direction;
	m_position.x = initialPosition.x + (MAXDISTANCE.x * currentAnimationFrame);
	m_position.y = initialPosition.y + (MAXDISTANCE.y * currentAnimationFrame);
}

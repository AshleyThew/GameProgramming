#include "Gem.h"
#include "Entity.h"
#include "Renderer.h"
#include "Sprite.h"

Gem::Gem(int x, int y)
{
	id.x = x;
	id.y = y;
}

Gem::~Gem()
{
}

bool 
Gem::Initialise(Renderer& renderer, const char* gemType, float scale)
{
	m_pSprite = renderer.CreateSprite(gemType);
	m_pSprite->SetScale(scale);
	m_position.x = (scale * 8) + (id.x * scale * 16);
	m_position.y = (scale * 8) + (id.y * scale * 16);

	Reset();
	return false;
}

void 
Gem::Process(float deltaTime)
{
	Entity::Process(deltaTime);
}

void
Gem::Draw(Renderer& renderer)
{
	Entity::Draw(renderer);
}

bool
Gem::GetCollected()
{
	return collected;
}

void
Gem::SetCollected()
{
	collected = true;
	SetDead(true);
}

void
Gem::Reset()
{
	collected = false;
	SetDead(false);
}


Vector2 
Gem::GetID()
{
	return id;
}

#include "Root.h"
#include "Renderer.h"
#include "Vector2.h"
#include "Sprite.h"
#include <List>

Root::Root()
	: colliding(false)
{

}

Root::~Root()
{

}

bool
Root::Initialise(Renderer &renderer)
{
	m_pSprite = renderer.CreateSprite("..\\Assets\\Root.png");
	

	return false;
}

bool
Root::isColliding()
{
	return colliding;
}

void
Root::SetAlive(int x, int y, float scale)
{
	SetDead(false);
	m_position.x = x;
	m_position.y = y;
	m_pSprite->SetScale(scale);
}

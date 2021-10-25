#include "Coin.h"
#include "Renderer.h"
#include "Sprite.h"
#include "Vector2.h"

Coin::Coin()
{
	
}

Coin::~Coin()
{

}

bool
Coin::Initialise(Renderer& renderer)
{
 	m_pSprite = renderer.CreateSprite("..\\Assets\\Coin.png");
	SetDead(false);
	return false;
}

void
Coin::SetTransform(Vector2 position, float scale)
{
	m_position.x = position.x;
	m_position.y = position.y;
	m_pSprite->SetScale(scale);
}

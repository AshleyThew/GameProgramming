#include "Ladder.h"
#include "Renderer.h"
#include "Sprite.h"	

Ladder::Ladder(int x, int y)
{
	id.x = x;
	id.y = y;
}

Ladder::~Ladder()
{
}

bool
Ladder::Initialise(Renderer& renderer, int ladderType, float scale)
{
	switch (ladderType)
	{
	case -1:
		m_pSprite = renderer.CreateSprite("..\\Assets\\Tiles\\Ladder Bottom.png");
		break;
	case 0:
		m_pSprite = renderer.CreateSprite("..\\Assets\\Tiles\\Ladder Middle.png");
		break;
	case 1:
		m_pSprite = renderer.CreateSprite("..\\Assets\\Tiles\\Ladder Top.png");
		break;
	}

	m_position.x = (scale * 8) + (id.x * scale * 16);
	m_position.y = (scale * 8) + (id.y * scale * 16);
	m_pSprite->SetScale(scale);
	SetDead(false);

	return false;
}

Vector2
Ladder::GetID()
{
	return id;
}



#include "tile.h"

#include "Vector2.h"
#include "Renderer.h"
#include "InputSystem.h"

Tile::Tile(int x, int y, TileCategory tileCategory)
	: id(0, 0)
	, tileType(UNDETERMINED)
	, locked(false)
{
	id.x = x;
	id.y = y;
	this->tileCategory = tileCategory;
}

Tile::~Tile()
{

}

bool
Tile::Initialise(Renderer& renderer, TileType tileType, int rotation)
{
	this->tileType = tileType;
	
	switch (tileType)
	{
		case CORNERCONCAVE:
			m_pSprite = renderer.CreateSprite("..\\Assets\\Tiles\\Corner Concave.png");
			break;
		case CORNERCONVEX:
			m_pSprite = renderer.CreateSprite("..\\Assets\\Tiles\\Corner Convex.png");
			break;
		case STRAIGHT:
			m_pSprite = renderer.CreateSprite("..\\Assets\\Tiles\\Straight.png");
			break;
		case MIDDLE:
			m_pSprite = renderer.CreateSprite("..\\Assets\\Tiles\\Middle1.png");
			break;
		case RAILCONCAVE:
			m_pSprite = renderer.CreateSprite("..\\Assets\\Tiles\\Rail Concave.png");
			break;
		case RAILCONVEX:
			m_pSprite = renderer.CreateSprite("..\\Assets\\Tiles\\Rail Convex.png");
			break;
		case RAILSTRAIGHT:
			m_pSprite = renderer.CreateSprite("..\\Assets\\Tiles\\Rail Straight.png");
			break;
		case GOOSURFACE:
			m_pSprite = renderer.CreateSprite("..\\Assets\\Tiles\\Goo Surface.png");
			break;
		case GOODEEP:
			m_pSprite = renderer.CreateSprite("..\\Assets\\Tiles\\Goo Deep.png");
			break;
		case BACKGROUNDLIGHT:
			m_pSprite = renderer.CreateSprite("..\\Assets\\Tiles\\Background1.png");
			break;
		case BACKGROUNDDARK:
			m_pSprite = renderer.CreateSprite("..\\Assets\\Tiles\\Background2.png");
			break;
		case LADDERTOP:
			m_pSprite = renderer.CreateSprite("..\\Assets\\Tiles\\Ladder Top.png");
			break;
		case LADDERMIDDLE:
			m_pSprite = renderer.CreateSprite("..\\Assets\\Tiles\\Ladder Middle.png");
			break;
		case LADDERBOTTOM:
			m_pSprite = renderer.CreateSprite("..\\Assets\\Tiles\\Ladder Bottom.png");
			break;
	}

	Rotate(rotation);

	return false;
}

void
Tile::Process(float deltaTime)
{
	Entity::Process(deltaTime);
}

void
Tile::Draw(Renderer& renderer)
{
	Entity::Draw(renderer);
}

void
Tile::SetPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
}

void
Tile::SetScale(float scale)
{
	m_pSprite->SetScale(scale);
}

Vector2
Tile::GetID()
{

	return id;
}

void
Tile::GetBounds(Vector2* &topLeft, Vector2* &bottomRight)
{
	float radius = m_pSprite->GetScale() * 4;
	float x = m_pSprite->GetX() - radius;
	float y = m_pSprite->GetY() - radius;
	topLeft->x = x;
	topLeft->y = y;
	bottomRight->x = x + (2 * radius);
	bottomRight->y = y + (2 * radius);
}

float
Tile::GetScale()
{
	return m_pSprite->GetScale();
}

TileType 
Tile::GetTileType()
{
	return tileType;
}

TileCategory
Tile::GetTileCategory()
{
	return tileCategory;
}

bool
Tile::GetLocked()
{
	return locked;
}

void
Tile::SetLocked()
{
	locked = true;
}
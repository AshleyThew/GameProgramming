#include "FireSnail.h"
#include "Renderer.h"
#include "AnimatedSprite.h"
#include "SoundManager.h"
#include "Inlinehelper.h"
#include "Tile.h"
#include "LevelManagerScene.h"

FireSnail::FireSnail()
	: tiles(0)
	, snailState(FALLING)
	, direction(-1)
	, timeElapsed(0)
{

}

FireSnail::~FireSnail()
{
}

bool
FireSnail::Initialise(Renderer& renderer)
{
	
	m_pAnimatedSprite = renderer.CreateAnimatedSprite("..\\Assets\\Fire Snail.png");
	m_pAnimatedSprite->SetupFrames(42, 28);
	m_pAnimatedSprite->SetAnimating(true);
	m_pAnimatedSprite->SetFrameDuration(FRAMEDURATION);
	m_pAnimatedSprite->SetLooping(true);
	direction = GetPositiveOrNegative();
	m_pAnimatedSprite->SetFrameBounds((-6.5 * direction) + 6.5, (-6.5 * direction) + 17.5);
	return false;
}

void
FireSnail::Process(float deltaTime, SoundManager& soundManager)
{
	Entity::Process(deltaTime);

	if (IsAlive())
	{
		if (snailState == FALLING)
		{

			if (!CheckCollisions().empty())
			{
				snailState = PATROL;
				m_velocity.y = 0;
				m_velocity.x = 0;
			}
			else
			{
				m_velocity.y -= deltaTime * GRAVITY * GetFacingDirection().y;
				m_velocity.x -= deltaTime * GRAVITY * GetFacingDirection().x;
			}
		}
		if (snailState == PATROL)
		{
			timeElapsed += deltaTime;

			if (timeElapsed > GAMETICK)
			{
				timeElapsed = 0;
				if (!GetRandom(0, 5))
				{
					direction *= -1;
					m_pAnimatedSprite->SetFrameBounds((-6.5 * direction) + 6.5, (-6.5 * direction) + 17.5);
				}
			}

			std::list<Tile*> collisions = CheckCollisions();

			bool touchingLeftRight = false;
			float xDirectionThis = GetFacingDirection().x;
			float yDirectionThis = GetFacingDirection().y;
			int heightThis = m_pAnimatedSprite->GetHeight();
			int widthThis = m_pAnimatedSprite->GetWidth();
			int numGroundTiles = 0;
			Vector2 positionThis = GetPosition();
			Vector2 feetLocation;
			feetLocation.x = positionThis.x + (heightThis / 2 * xDirectionThis);
			feetLocation.y = positionThis.y + (heightThis / 2 * yDirectionThis);
			Tile* bottomTile;


			std::list<Tile*>::iterator itTile;
			for (itTile = collisions.begin(); itTile != collisions.end(); itTile++)
			{
				Vector2 tilePosition = (*itTile)->getPosition();

				if (xDirectionThis * (tilePosition.x - feetLocation.x) > -yDirectionThis * (tilePosition.y - feetLocation.y))
				{
					//Tiles Underneith
					bottomTile = (*itTile);
					numGroundTiles++;
				}
				else if (yDirectionThis * (tilePosition.x - feetLocation.x) > xDirectionThis * (tilePosition.y - feetLocation.y)
					|| (-xDirectionThis * (tilePosition.x - feetLocation.x) > yDirectionThis * (tilePosition.y - feetLocation.y)))
				{
					//Tiles to the left or right
					direction *= -1;
					touchingLeftRight = true;
				}
			}

			if (!touchingLeftRight && numGroundTiles == 1)
			{
				Vector2* topLeftTileBound = new Vector2();
				Vector2* bottomRightTileBound = new Vector2();
				bottomTile->GetBounds(topLeftTileBound, bottomRightTileBound);

				if ((topLeftTileBound->x > positionThis.x || bottomRightTileBound->x < positionThis.x) && (topLeftTileBound->y > positionThis.y || bottomRightTileBound->y < positionThis.y))
				{
					if (topLeftTileBound->x > positionThis.x)
					{
						m_position.x -= heightThis / 2 * abs(yDirectionThis);
						m_position.y += heightThis * yDirectionThis;
						Rotate(yDirectionThis * 90);
					}
					else if (bottomRightTileBound->x < positionThis.x)
					{
						m_position.x += heightThis / 2 * abs(yDirectionThis);
						m_position.y += heightThis * yDirectionThis;
						Rotate(yDirectionThis * -90);
					}

					if (topLeftTileBound->y > positionThis.y)
					{
						m_position.x += heightThis * xDirectionThis;
						m_position.y -= heightThis / 2 * abs(xDirectionThis);
						Rotate(xDirectionThis * -90);
					}
					else if (bottomRightTileBound->y < positionThis.y)
					{
						m_position.x += heightThis * xDirectionThis;
						m_position.y += heightThis / 2 * abs(xDirectionThis);
						Rotate(xDirectionThis * 90);
					}
					snailState = FALLING;
				}
				delete topLeftTileBound;
				delete bottomRightTileBound;
			}

			m_velocity.x = MOVEMENTSPEED * m_pAnimatedSprite->GetScale() * yDirectionThis * direction;
			m_velocity.y = -MOVEMENTSPEED * m_pAnimatedSprite->GetScale() * xDirectionThis * direction;

			if (collisions.empty())
			{
				snailState = FALLING;
			}
			if (snailState == FALLING)
			{
				m_velocity.x = 0;
				m_velocity.y = 0;
			}
		}
	}
	
}

void
FireSnail::Start(std::list<Tile*> tiles)
{
	this->tiles = tiles;

	int randomTile = GetRandom(0, tiles.size() - 1);
	std::list<Tile*>::iterator it;
	bool found = false;
	it = tiles.begin();
	Tile* tileSpawn = NULL;

	for (int i = 0; i < randomTile; i++)
	{
		it++;
	}

	if ((*it)->GetFrame() == 4)
	{
		bool atValidTile = false;
		while (!atValidTile)
		{
			if ((*it)->GetFrame() != 4)
			{
				atValidTile = true;
			}
			else
			{
				it++;
			}


			if (it == tiles.end())
			{
				it = tiles.begin();
			}
		}
	}

	tileSpawn = (*it);

	m_pAnimatedSprite->SetScale(tileSpawn->GetScale() / 4);
	Vector2 tilePosition = tileSpawn->getPosition();
	m_position.x = tilePosition.x;
	m_position.y = tilePosition.y;

	switch (tileSpawn->GetFrame())
	{
	case LevelManagerScene::TOP:
	case LevelManagerScene::TOPLEFT:
	case LevelManagerScene::TOPRIGHT:
		m_position.y -= (tileSpawn->GetScale() * 4) + (m_pAnimatedSprite->GetHeight() / 2);
		m_pAnimatedSprite->SetAngle(0);
		break;
	case LevelManagerScene::BOTTOM:
	case LevelManagerScene::BOTTOMLEFT:
	case LevelManagerScene::BOTTOMRIGHT:
		m_position.y += (tileSpawn->GetScale() * 4) + (m_pAnimatedSprite->GetHeight() / 2);
		m_pAnimatedSprite->SetAngle(180);
		//Rotate(180);
		break;
	case LevelManagerScene::LEFT:
		m_position.x -= (tileSpawn->GetScale() * 4) + (m_pAnimatedSprite->GetHeight() / 2);
		m_pAnimatedSprite->SetAngle(90);
		break;
	case LevelManagerScene::RIGHT:
		m_position.x += (tileSpawn->GetScale() * 4) + (m_pAnimatedSprite->GetHeight() / 2);
		m_pAnimatedSprite->SetAngle(270);
		break;
	}

	int x = 0;
}

std::list<Tile*>
FireSnail::CheckCollisions()
{
	std::list<Tile*> collisions;
	std::list<Tile*>::iterator itTile;

	for (itTile = tiles.begin(); itTile != tiles.end(); itTile++)
	{
		if (IsCollidingWith(*itTile))
		{
			collisions.push_back(*itTile);
		}
	}

	return collisions;
}

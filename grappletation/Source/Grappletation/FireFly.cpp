#include "FireFly.h"
#include "Renderer.h"
#include "AnimatedSprite.h"
#include "Sprite.h"
#include "Inlinehelper.h"
#include "Tile.h"
#include "Vector2.h"
#include "imgui.h"
#include "ParticleSystem.h"
#include <string>
#include <list>
#include <map>
#include <sstream>
FireFly::FireFly()
	: marker(0)
	, particleSystem(0)
	, tileSize(0)
{

}

FireFly::~FireFly()
{
	delete marker;
	delete particleSystem;
}

bool
FireFly::Initialise(Renderer& renderer)
{
	m_pAnimatedSprite = renderer.CreateAnimatedSprite("..\\Assets\\Fly.png");
	m_pAnimatedSprite->SetupFrames(4, 3);
	m_pAnimatedSprite->SetAnimating(true);
	m_pAnimatedSprite->SetFrameDuration(FRAMEDURATION);
	m_pAnimatedSprite->SetLooping(true);

	marker = renderer.CreateSprite("..\\Assets\\bullet.png");
	marker->SetScale(1);

	particleSystem = new ParticleSystem();
	particleSystem->Initialise(renderer, "..\\Assets\\Fire Particle.png");
	particleSystem->lifeSpan = 1;
	particleSystem->spawnSpeed = 0.01f;
	particleSystem->minScale = 0;
	particleSystem->alphaOverLifeTime = QUADRATICFASTDECREASE;
	particleSystem->scaleOverLifeTime = QUADRATICFASTDECREASE;
	particleSystem->Start();

	SetDead(false);
	return false;
}

void
FireFly::Process(float deltaTime, SoundManager& soundManager, Vector2 playerLocation)
{
	marker->Process(deltaTime);
	Entity::Process(deltaTime);
	particleSystem->Process(deltaTime);

	if (IsAlive())
	{
		particleSystem->initialPosition.x = m_position.x;
		particleSystem->initialPosition.y = m_position.y;

		if (playerLocation.y != m_position.y && playerLocation.x != m_position.x && SendRay(playerLocation))
		{

			particleSystem->Start();
			float m = (playerLocation.y - m_position.y) / (playerLocation.x - m_position.x);
			float angle = atan(m);
			if (playerLocation.x > m_position.x)
			{
				m_velocity.x = -MAXVELOCITY * cos(angle) * 2 * m_pAnimatedSprite->GetScale();
				m_velocity.y = -MAXVELOCITY * sin(angle) * 2 * m_pAnimatedSprite->GetScale();
			}
			else
			{
				m_velocity.x = MAXVELOCITY * cos(angle) * 2 * m_pAnimatedSprite->GetScale();
				m_velocity.y = MAXVELOCITY * sin(angle) * 2 * m_pAnimatedSprite->GetScale();
			}

		}
		else
		{
			Tile* collidingTile = NULL;
			particleSystem->Stop();
			bool colliding = false;
			std::list<Tile*>::iterator it;
			for (it = tileList.begin(); it != tileList.end(); it++)
			{
				if (IsCollidingWith((*it)))
				{
					collidingTile = (*it);
				}
			}

			if (collidingTile)
			{
				float increment = 0.01;
				bool xdirection = true;
				do
				{
					if (xdirection)
					{
						m_position.x += increment;
					}
					else
					{
						m_position.y += increment;
						increment *= -2;
					}
					xdirection = !xdirection;
					colliding = false;
					for (it = tileList.begin(); it != tileList.end(); it++)
					{
						if (IsCollidingWith((*it)))
						{
							colliding = true;
						}
					}
				} while (colliding);

				float randomAngle = (float)GetRandom(0, 31459) / 10000.0f;
				m_velocity.x = GetPositiveOrNegative() * MAXVELOCITY * cos(randomAngle) * m_pAnimatedSprite->GetScale();
				m_velocity.y = GetPositiveOrNegative() * MAXVELOCITY * sin(randomAngle) * m_pAnimatedSprite->GetScale();
				
			}

			if (m_position.x < 192)
			{
				m_velocity.x = abs(m_velocity.x) * -1;
			}
			else if (m_position.x > 1920 - 192)
			{
				m_velocity.x = abs(m_velocity.x);

			}
			if (m_position.y < 108)
			{
				m_velocity.y = abs(m_velocity.y) * -1;
			}
			else if (m_position.y > 1080 - 108)
			{
				m_velocity.y = abs(m_velocity.y);

			}

		}
	}
	else
	{
		particleSystem->Stop();
	}
	


}

void
FireFly::Draw(Renderer& renderer)
{
	particleSystem->Draw(renderer);
	Entity::Draw(renderer);
	std::list<Vector2>::iterator it;

	/*
	for (it = colliderPositions.begin(); it != colliderPositions.end(); it++)
	{
		marker->SetX((it->x * tileSize) + 192 + tileSize/2);
		marker->SetY((it->y * tileSize) + 108 + tileSize/2);
		std::ostringstream ss;
		ss << it->x << ", " << it->y;
		if (tileMap[ss.str()])
		{
			marker->SetBlueTint(0);
			marker->SetGreenTint(0);
		}
		else
		{
			marker->SetBlueTint(1);
			marker->SetGreenTint(1);
		}

		marker->Draw(renderer);
	}
	*/
}

bool
FireFly::SendRay(Vector2 destination)
{
	float dx = destination.x - m_position.x;
	float dy = destination.y - m_position.y;
	float maxDistance = sqrt(pow(dx, 2) + pow(dy, 2));
	if (dx == 0 || dy == 0)
	{
		return false;
	}

	float xUnit = sqrt(1 + pow(dy / dx, 2));
	float yUnit = sqrt(1 + pow(dx / dy, 2));

	Vector2 startingTile;
	startingTile.x = (int)((m_position.x - 192) / tileSize);
	startingTile.y = (int)((m_position.y - 108) / tileSize);
	Vector2 topLeft;
	topLeft.x = (startingTile.x * tileSize) + 192;
	topLeft.y = (startingTile.y * tileSize) + 108;

	Vector2 step;
	step.x = dx;
	step.y = dy;

	Vector2 direction;
	direction.x = 0;
	direction.y = 0;

	direction.x = dx / abs(dx);
	step.x = direction.x * tileSize;

	direction.y = dy / abs(dy);
	step.y = direction.y * tileSize;
	
	Vector2 intervalRayLength;
	if (step.x > 0)
	{
		intervalRayLength.x = (tileSize + topLeft.x - m_position.x) * xUnit;
	}
	else if (step.x < 0)
	{
		intervalRayLength.x = (m_position.x - topLeft.x) * xUnit;
	}
	else
	{
		intervalRayLength.x = 0;
	}

	if (step.y > 0)
	{
		intervalRayLength.y = (tileSize + topLeft.y - m_position.y) * yUnit;
	}
	else if (step.y < 0)
	{
		intervalRayLength.y = (m_position.y - topLeft.y) * yUnit;
	}
	else
	{
		intervalRayLength.y = 0;
	}

	Vector2 currentTile;
	currentTile.x = m_position.x;
	currentTile.y = m_position.y;

	Vector2 totalRayLength;
	totalRayLength.x = 0;
	totalRayLength.y = 0;


	float currentDistance = 0;
	bool hit = false;
	colliderPositions.clear();
	while (!hit && currentDistance < maxDistance)
	{

		Vector2 tileID;
		tileID.x = (int)((currentTile.x - 192) / tileSize);
		tileID.y = (int)((currentTile.y - 108) / tileSize);
		colliderPositions.push_back(tileID);

		if (intervalRayLength.x + totalRayLength.x < intervalRayLength.y + totalRayLength.y)
		{
			currentTile.x += step.x;
			intervalRayLength.x = tileSize * xUnit;
			totalRayLength.x += intervalRayLength.x;
			currentDistance = totalRayLength.x;


		}
		else
		{
			currentTile.y += step.y;
			intervalRayLength.y = tileSize * yUnit;
			totalRayLength.y += intervalRayLength.y;
			currentDistance = totalRayLength.y;

		}



		std::ostringstream ss;
		ss << tileID.x << ", " << tileID.y;
		if (tileMap[ss.str()])
		{
			hit = true;
		}

	}

	return !hit;
}

void
FireFly::Start(std::list<Tile*> tiles, Vector2 gridSize, Vector2 startingPosition)
{

	m_position.x = startingPosition.x;
	m_position.y = startingPosition.y;
	m_pAnimatedSprite->SetScale(tiles.front()->GetScale());
	particleSystem->RemoveAllParticles();
	particleSystem->maxScale = tiles.front()->GetScale();
	particleSystem->particleBoundaries.x = 0.5 * m_pAnimatedSprite->GetScale();
	particleSystem->particleBoundaries.y = 0.5 * m_pAnimatedSprite->GetScale();
	float randomAngle = (float)GetRandom(0, 31459) / 10000.0f;
	m_velocity.x = GetPositiveOrNegative() * MAXVELOCITY * cos(randomAngle) * m_pAnimatedSprite->GetScale();
	m_velocity.y = GetPositiveOrNegative() * MAXVELOCITY * sin(randomAngle) * m_pAnimatedSprite->GetScale();

	tileList = tiles;
	tileSize = tiles.front()->GetScale() * 8;
	for (int y = 0; y < gridSize.y; y++)
	{
		for (int x = 0; x < gridSize.x; x++)
		{
			std::ostringstream ss;
			ss << x << ", " << y;
			tileMap[(ss.str())] = false;
		}
	}
	
	std::list<Tile*>::iterator it;
	for (it = tiles.begin(); it != tiles.end(); it++)
	{
		std::ostringstream ss;
		ss << (*it)->GetID().x << ", " << (*it)->GetID().y;
		tileMap[ss.str()] = true;
	}

	int x = 0;
	
}

void
FireFly::DebugDraw()
{

}

void
FireFly::DebugDraw(float angle)
{
	ImGui::Text("Angle: %f", angle);
}

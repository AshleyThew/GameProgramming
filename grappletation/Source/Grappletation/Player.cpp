#include "Player.h"
#include "Renderer.h"
#include "AnimatedSprite.h"
#include "InputSystem.h"
#include "tile.h"
#include "Logmanager.h"
#include "InputSystem.h"
#include "XboxController.h"
#include "Renderer.h"
#include "Entity.h"
#include "Gem.h"
#include "SoundManager.h"
#include "ParticleSystem.h"
#include "levelmanager.h"
#include "Vector2.h"
#include "imgui.h"
#include <stdlib.h>
#include <string>

enum FrameTypes
{
	WALKING_START = 0,
	WALKING_END = 7,

	IDLE_START = 8,
	IDLE_END = 11,

	SHOOT_START = 16,
	SHOOT_END = 20

};

Player::Player()
	: timeElapsed(0)
	, playerState(IDLE)
	, invincible(false)
	, m_selected(false)
{

} 

Player::~Player()
{
	delete bloodBackground;
	bloodBackground = 0;
	//delete particleSystem;
	//delete bloodBackground;

}

bool
Player::Initialise(Renderer& renderer)
{
	m_pAnimatedSprite->SetupFrames(20, 21);
	m_pAnimatedSprite->SetFrameBounds(WALKING_START, WALKING_END);
	m_pAnimatedSprite->SetFrame(0);
	m_pAnimatedSprite->SetFrameDuration(FRAMEDURATION);
	//m_pAnimatedSprite->SetFrameDuration(0.5);
	m_pAnimatedSprite->SetLooping(true);
	m_pAnimatedSprite->SetScale(4.0f);

	//particleSystem = new ParticleSystem();
	//particleSystem->Initialise(renderer, "..\\Assets\\Particle.png");
	//particleSystem->lifeSpan = 1;
	//particleSystem->spawnSpeed = 0.01f;
	//particleSystem->minScale = 0;
	//particleSystem->alphaOverLifeTime = QUADRATICSLOWDECREASE;
	//particleSystem->scaleOverLifeTime = QUADRATICSLOWDECREASE;
	//particleSystem->Start();

	bloodBackground = renderer.CreateSprite("..\\Assets\\Portal Gun Character Sheet.png");
	bloodBackground->SetX(renderer.GetWidth() / 2);
	bloodBackground->SetY(renderer.GetHeight() / 2);
	bloodBackground->SetScale(1.1 * (((float)renderer.GetWidth() - 384) / (float)bloodBackground->GetWidth()));
	bloodBackground->SetAlpha(0.2f);
	SetDead(false);

	return false;
}

void
Player::Process(float deltaTime, InputSystem& inputSystem, SoundManager& soundManager)
{
	Entity::Process(deltaTime);

	bloodBackground->Process(deltaTime);
	if (invincible)
	{
		invincibilityTimeElapsed += deltaTime;
		m_pAnimatedSprite->SetAlpha(0.5f);
		if (invincibilityTimeElapsed > INVINCIBILITYDURATION)
		{
			invincible = false;
			m_pAnimatedSprite->SetAlpha(1);
		}
	}

	std::vector<Gem*> gems = scene->GetLevelManager()->GetAllGems();

	for (std::vector<Gem*>::iterator itGem = gems.begin(); itGem != gems.end(); itGem++)
	{
		Gem*& gem = *itGem;
		if (gem->IsAlive())
		{
			if (IsCollidingWith(*gem))
			{
				soundManager.PlaySound("Coin");
				gem->SetCollected();
			}
		}
	}

	std::list<Tile*> collisions = CheckCollisions();
	if (playerState == FALLING)
	{
		if (!collisions.empty())
		{
			playerState = IDLE;
			m_velocity.y = 0;
			m_velocity.x = 0;
		}
		else
		{
			m_velocity.y -= deltaTime * GRAVITY;
			m_velocity.x = 0;
		}
	}

	if (playerState == IDLE)
	{
		bool touchingLeft = false;
		bool touchingRight = false;
		bool touchingLadder = false;
		bool onGround = false;
		int heightThis = m_pAnimatedSprite->GetHeight();
		int widthThis = m_pAnimatedSprite->GetWidth();
		Vector2 positionThis = GetPosition();
		Vector2 feetLocation;
		feetLocation.x = positionThis.x;
		feetLocation.y = positionThis.y + (heightThis / 2 );
		Tile* bottomTile = 0;

		std::list<Tile*>::iterator itTile;
		for (itTile = collisions.begin(); itTile != collisions.end(); itTile++)
		{
			Tile*& tile = *itTile;
			if (tile->GetTileCategory() == LADDER)
			{
				touchingLadder = true;
			}
			else if (tile->GetTileCategory() == BLOCK)
			{
				Vector2 tilePosition = (*itTile)->GetPosition();

				if ((tilePosition.y - feetLocation.y) > 0)
				{
					//Tiles Underneth
					bottomTile = (*itTile);
				}
				else if (tilePosition.x - feetLocation.x > 0)
				{
					//Tiles to the right
					touchingRight = true;
				}
				else if (tilePosition.x - feetLocation.x < 0)
				{
					// Tiles to the left
					touchingLeft = true;
				}
			}
		}
		if (touchingLadder && bottomTile != 0)
		{
			float val = bottomTile->GetPosition().y - feetLocation.y;
			if (val > heightThis / 2)
			{
				onGround = true;
			}
		}

		if (m_selected)
		{
			CheckInput(inputSystem, soundManager, touchingLeft, touchingRight, touchingLadder);
			if (onGround && m_velocity.y < 0)
			{
				m_velocity.y = 0;
			}
		}

		if (collisions.empty())
		{
			playerState = FALLING;
		}

		if (playerState == FALLING)
		{
			m_velocity.x = 0;
			m_velocity.y = 0;
		}


		//particleSystem->initialPosition.x = feetLocation.x;
		//particleSystem->initialPosition.y = feetLocation.y;
		//particleSystem->initialVelocity.x = -5 * m_pAnimatedSprite->GetScale() * xDirectionThis;
		//particleSystem->initialVelocity.y = -5 * m_pAnimatedSprite->GetScale() * yDirectionThis;
		//particleSystem->acceleration.x = m_pAnimatedSprite->GetScale() * xDirectionThis;
		//particleSystem->acceleration.y = m_pAnimatedSprite->GetScale() * yDirectionThis;
		//particleSystem->particleBoundaries.x = 2 * m_pAnimatedSprite->GetScale();
		//particleSystem->particleBoundaries.y = 2 * m_pAnimatedSprite->GetScale();
	}

	//particleSystem->Process(deltaTime);


}

void
Player::Draw(Renderer& renderer)
{
	//particleSystem->Draw(renderer);

	m_pAnimatedSprite->Draw(renderer);

	if (currentHealth == HIT)
	{
		bloodBackground->Draw(renderer);
	}
}

void
Player::SetScale(float scale)
{
	m_pAnimatedSprite->SetScale(scale);
}

void
Player::Start(SceneGrappletation* scene)
{
	//particleSystem->RemoveAllParticles();
	currentHealth = HEALTHY;
	playerState = FALLING;
	m_velocity.x = 0;
	m_velocity.y = 0;
	m_pAnimatedSprite->SetFrame(0);
	m_pAnimatedSprite->SetAnimating(false);
	timeElapsed = 0;
	m_pAnimatedSprite->SetFrameDuration(FRAMEDURATION);
	m_pAnimatedSprite->SetAngle(0);

	
	this->scene = scene;

	//particleSystem->maxScale = firstTileScale;

}

void
Player::SetPosition(int x, int y)
{
	m_position.x = x;
	m_position.y = y;
}

std::list<Tile*>
Player::CheckCollisions()
{
	std::list<Tile*> collisions;

	std::map<std::string, Tile*> tiles = scene->GetLevelManager()->GetLevelTiles();
	
	for (std::map<std::string, Tile*>::iterator it = tiles.begin(); it != tiles.end(); it++)
	{
		Tile*& tile = (*it).second;
		if (tile->GetTileCategory() == BLOCK || tile->GetTileCategory() == LADDER)
		{
			if (this->IsCollidingWith(*tile))
			{
				collisions.push_back(tile);
			}
		}
	}

	return collisions;
}

void
Player::CheckInput(InputSystem& inputSystem, SoundManager& soundManager, bool touchingLeft, bool touchingRight, bool touchingLadder)
{

	ButtonState leftArrowKeyboardState = inputSystem.GetKeyState(SDL_SCANCODE_LEFT);
	ButtonState rightArrowKeyboardState = inputSystem.GetKeyState(SDL_SCANCODE_RIGHT);
	ButtonState upArrowKeyboardState = inputSystem.GetKeyState(SDL_SCANCODE_UP);
	ButtonState downArrowKeyboardState = inputSystem.GetKeyState(SDL_SCANCODE_DOWN);

	float movementX = 0;
	float movementY = 0;
	
	if(touchingLadder)
	{
		if (upArrowKeyboardState == BS_HELD)
		{
			movementY = 1.0f;
		}
		else if (downArrowKeyboardState == BS_HELD)
		{
			movementY = -1.0f;
		}
		else if (inputSystem.GetNumberOfControllersAttached())
		{
			XboxController* controller = inputSystem.GetController(0);
			Vector2 stick = controller->GetLeftStick();
			if (stick.y > 10000)
			{
				movementY = -1.0f;
			}
			else if (stick.y < -10000)
			{
				movementY = 1.0f;
			}
		}
	}

	if (leftArrowKeyboardState == BS_HELD && !touchingLeft)
	{
		movementX = 1;
	}
	else if (rightArrowKeyboardState == BS_HELD && !touchingRight)
	{
		movementX = -1;
	}
	else if (inputSystem.GetNumberOfControllersAttached())
	{
		XboxController* controller = inputSystem.GetController(0);
		Vector2 stick = controller->GetLeftStick();
		if (stick.x < -10000 && !touchingLeft)
		{
			movementX = 1;
		}
		else if (stick.x > 10000 && !touchingRight)
		{
			movementX = -1;
		}
	}

	m_velocity.y = MOVEMENTSPEED * m_pAnimatedSprite->GetScale() * movementY;

	if (movementX != 0.0f)
	{
		if (m_velocity.x >= 0.0f && movementX < 0.0f)
		{
			m_pAnimatedSprite->SetFrameBounds(WALKING_START, WALKING_END);
		}
		else if(m_velocity.x <= 0.0f && movementX > 0.0f)
		{
			m_pAnimatedSprite->SetFrameBounds(FRAME_LEFT_OFFSET + WALKING_START, FRAME_LEFT_OFFSET + WALKING_END);
		}

		m_pAnimatedSprite->SetAnimating(true);
		m_velocity.x = MOVEMENTSPEED * m_pAnimatedSprite->GetScale() * movementX;
	}
	else
	{
		m_pAnimatedSprite->SetAnimating(false);
		m_velocity.x = 0;
		m_pAnimatedSprite->Restart();
	}
}

bool
Player::DecreaseHealth(SoundManager& soundManager)
{
	if (!invincible)
	{
		currentHealth = (HealthStates)(currentHealth + 1);
		invincible = true;
		invincibilityTimeElapsed = 0;
		soundManager.PlaySound("Hurt");
	}
	
	return currentHealth == DEAD;
}

void
Player::ResetHealth()
{
	currentHealth = HEALTHY;
	invincible = true;
	invincibilityTimeElapsed = 0;
}

void
Player::DebugDraw()
{

}

bool
Player::GetSelected()
{
	return m_selected;
}

void
Player::SetSelected(bool selected)
{
	m_selected = selected;
	m_velocity.x = 0;
	m_velocity.y = 0;
}


void
Player::Hit()
{
	float red = m_pAnimatedSprite->GetRedTint();
	m_pAnimatedSprite->SetRedTint(red/2.0f);
	m_pAnimatedSprite->SetBlueTint(0.00f);
	m_pAnimatedSprite->SetGreenTint(0.00f);
}

#include "interactableLever.h"
#include "Sprite.h"
#include "Renderer.h"
#include "InputSystem.h"
#include "Door.h"

interactableLever::interactableLever(int x, int y)
	:pressed(false)
	, currentAnimationFrame(-0.001)
{
	id.x = x;
	id.y = y;
}

interactableLever::~interactableLever()
{
	delete leverHead;
}

bool
interactableLever::Initialise(Renderer& renderer, int rotation, float scale)
{
	m_pSprite = renderer.CreateSprite("..\\Assets\\Objects\\Lever Base.png");
	leverHead = renderer.CreateSprite("..\\Assets\\Objects\\Lever Head.png");
	Rotate(rotation);
	leverHead->SetAngle(rotation);
	m_pSprite->SetScale(scale);
	leverHead->SetScale(scale);
	Vector2 facingDirection = GetFacingDirection();
	m_position.x = (scale * 8) + (id.x * scale * 16) + ((facingDirection.x * scale)/2);
	m_position.y = (scale * 8) + (id.y * scale * 16) + ((facingDirection.y * scale)/2);
	leverHead->SetX(m_position.x + (facingDirection.x * scale * 2));
	leverHead->SetY(m_position.y + (facingDirection.y * scale * 2));
	SetDead(false);

	return false;
}

void
interactableLever::Process(float deltaTime, InputSystem& inputSystem)
{
	Entity::Process(deltaTime);
	if (IsAlive())
	{
		if (inputSystem.GetKeyState(SDL_SCANCODE_SPACE) == BS_PRESSED)
		{
			SetPressed(!pressed);
		}

		if ((currentAnimationFrame >= 0 && !pressed) || (currentAnimationFrame <= 1 && pressed))
		{
			PlayAnimation(deltaTime);
		}

		leverHead->Process(deltaTime);

	}
}

void
interactableLever::Draw(Renderer& renderer)
{
	if (IsAlive())
	{
		leverHead->Draw(renderer);
	}
	Entity::Draw(renderer);
}

Vector2
interactableLever::GetID()
{
	return id;
}

void
interactableLever::SetPressed(bool pressed)
{
	this->pressed = pressed;
	for (std::vector<Door*>::iterator itDoor = attachedDoors.begin(); itDoor != attachedDoors.end(); itDoor++)
	{
		(*itDoor)->SetOpen(pressed);
	}
}

void
interactableLever::PlayAnimation(float deltaTime)
{
	int direction = (pressed * 2) - 1;
	currentAnimationFrame += deltaTime * MOVEMENTSPEED * direction;
	leverHead->SetAngle(m_pSprite->GetAngle() - (90 * currentAnimationFrame));

}

void 
interactableLever::SetAttachedDoor(Door* attachedDoor)
{
	attachedDoors.push_back(attachedDoor);
}

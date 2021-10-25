#include "InteractableButton.h"
#include "Renderer.h"
#include "Sprite.h"
#include "Vector2.h"
#include "InputSystem.h"
#include "Door.h"

InteractableButton::InteractableButton(int x, int y)
	: timeElapsed(0)
	, pressed(false)
	, currentAnimationFrame(-0.001)
{
	id.x = x;
	id.y = y;
}

InteractableButton::~InteractableButton()
{
	delete buttonHead;
}

bool 
InteractableButton::Initialise(Renderer& renderer, int rotation, float scale)
{
	m_pSprite = renderer.CreateSprite("..\\Assets\\Objects\\Button Base.png");
	buttonHead = renderer.CreateSprite("..\\Assets\\Objects\\Button Head.png");
	Rotate(rotation);
	buttonHead->SetAngle(rotation);
	m_pSprite->SetScale(scale);
	buttonHead->SetScale(scale);
	Vector2 facingDirection = GetFacingDirection();
	m_position.x = (scale * 8) + (id.x * scale * 16) + (facingDirection.x * scale * 6);
	m_position.y = (scale * 8) + (id.y * scale * 16) + (facingDirection.y * scale * 6);
	buttonHead->SetX(m_position.x);
	buttonHead->SetY(m_position.y);
	MAXDISTANCE.x = facingDirection.x * scale * 2;
	MAXDISTANCE.y = facingDirection.y * scale * 2;

	SetDead(false);
	return false;
}

void 
InteractableButton::Process(float deltaTime, InputSystem& inputSystem)
{
	Entity::Process(deltaTime);
	if (IsAlive())
	{
		if (inputSystem.GetKeyState(SDL_SCANCODE_SPACE) == BS_PRESSED)
		{
			SetPressed(!pressed);
		}


		buttonHead->Process(deltaTime);

		if ((currentAnimationFrame >= 0 && !pressed) || (currentAnimationFrame <= 1 && pressed))
		{
			PlayAnimation(deltaTime);
		}
	}

}

void 
InteractableButton::Draw(Renderer& renderer)
{
	if (IsAlive())
	{
		buttonHead->Draw(renderer);
	}
	Entity::Draw(renderer);

}

void
InteractableButton::SetPressed(bool pressed)
{
	this->pressed = pressed;
	for (std::vector<Door*>::iterator itDoor = attachedDoors.begin(); itDoor != attachedDoors.end(); itDoor++)
	{
		(*itDoor)->SetOpen(pressed);
	}
}

void 
InteractableButton::PlayAnimation(float deltaTime)
{
	int direction = (pressed * 2) - 1;
	currentAnimationFrame += deltaTime * MOVEMENTSPEED * direction;
	buttonHead->SetX(m_position.x + (MAXDISTANCE.x * currentAnimationFrame));
	buttonHead->SetY(m_position.y + (MAXDISTANCE.y * currentAnimationFrame));
}

Vector2
InteractableButton::GetID()
{
	return id;
}

void
InteractableButton::SetAttachedDoor(Door* attachedDoor)
{
	attachedDoors.push_back(attachedDoor);
}

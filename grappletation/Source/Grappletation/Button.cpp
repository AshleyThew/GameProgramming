#include "Button.h"
#include "Renderer.h"
#include "SoundManager.h"
#include "InputSystem.h"
#include "Sprite.h"
#include "Vector2.h"
#include "XboxController.h"
#include "logmanager.h"

Button::Button()
	: sprite(0)
	, mousePressed(false)
	, controllerPressed(false)
	, defaultScale(0)
	, cursorHover(false)
	, toggleable(false)
{

}

Button::~Button()
{
	delete sprite;
	sprite = 0;
}

bool
Button::Initialise(Renderer& renderer, const char* spriteLocation)
{
	timer = 0.0f;
	sprite = renderer.CreateSprite(spriteLocation);
	defaultScale = sprite->GetScale();
	return false;
}

bool
Button::Process(float deltaTime, InputSystem& inputSystem)
{
	sprite->Process(deltaTime);

	if ((mousePressed || controllerPressed) && toggleable)
	{
		sprite->SetScale(defaultScale / 0.9f);
		sprite->SetBlueTint(0.8f);
		sprite->SetGreenTint(0.8f);
		sprite->SetScale(defaultScale / 0.9);
		sprite->SetBlueTint(0.8);
		sprite->SetGreenTint(0.8);
	}
	else
	{
		sprite->SetScale(defaultScale);
		sprite->SetBlueTint(1);
		sprite->SetGreenTint(1);
	}

	if (inputSystem.GetNumberOfControllersAttached() &&
		controllerPressed && inputSystem.GetController(0)->GetButtonState(SDL_CONTROLLER_BUTTON_A) == SDL_PRESSED)
	{
		return true;
	}

	Vector2 mousePosition = inputSystem.GetMousePosition();
	if (mousePosition.x > topLeftBound.x &&
		mousePosition.x < bottomRightBound.x &&
		mousePosition.y > topLeftBound.y &&
		mousePosition.y < bottomRightBound.y)
	{
		cursorHover = true;

		ButtonState leftMouseButton = inputSystem.GetMouseButtonState(SDL_BUTTON_LEFT);
		if (leftMouseButton == BS_RELEASED && mousePressed)
		{
			mousePressed = false;
			return true;
		}

		if (leftMouseButton == BS_PRESSED)
		{
			mousePressed = true;
		}
	}
	else
	{
		cursorHover = false;
	}
	
	return false;
}

void
Button::Draw(Renderer& renderer)
{
	sprite->Draw(renderer);
}

void
Button::SetTransform(int x, int y, float scale)
{
	int temp = sprite->GetX();
	sprite->SetX(x);
	sprite->SetY(y);
	defaultScale = scale;
	sprite->SetScale(defaultScale);
	float xRadius = sprite->GetWidth()/2.0f;
	float yRadius = sprite->GetHeight()/2.0f;

	topLeftBound.x = x - xRadius;
	topLeftBound.y = y - yRadius;
	bottomRightBound.x = x + xRadius;
	bottomRightBound.y = y + yRadius;
	int a = 0;
}

void
Button::SetPressed(bool pressed)
{
	this->mousePressed = pressed;
}

void Button::SetSprite(Sprite * newSprite)
{
	sprite = newSprite;
}

Sprite* Button::GetSprite()
{
	return sprite;
}

bool Button::GetCursorHover()
{
	return cursorHover;
}

bool Button::GetMousePressed()
{
	bool returnBool = mousePressed;
	if (mousePressed) {
		mousePressed = false;
	}

	return returnBool;
}

float Button::GetDefaultScale() {
	return defaultScale;
}

void Button::setToggleable() {
	toggleable = true;
}

void  Button::setCursorHover(bool hover) {
	cursorHover = hover;
}

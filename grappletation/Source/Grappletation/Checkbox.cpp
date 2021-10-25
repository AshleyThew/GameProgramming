#include "checkbox.h"
#include "vector2.h"
#include "logmanager.h"
Checkbox::Checkbox()
{
}

Checkbox::~Checkbox()
{
	
}

bool Checkbox::Initialise(Renderer& renderer, bool isActive)
{
	toSwitch = false;
	mousePressed = false;

	if (isActive) {
		Button::Initialise(renderer, "sprites\\menu\\checkboxtrue.png");
		checked = true;
	}
	else {
		Button::Initialise(renderer, "sprites\\menu\\checkboxfalse.png");
		checked = false;
	}

	return false;
}


void Checkbox::Process(float deltaTime, InputSystem & inputSystem)
{
	Button::Process(deltaTime, inputSystem);

	if (Button::GetMousePressed()) {
		toSwitch = true;
	}
}

void Checkbox::Draw(Renderer & renderer)
{
	if (toSwitch) {
		Vector2* spriteLoc = new Vector2();
		spriteLoc->Set(Button::GetSprite()->GetX(), Button::GetSprite()->GetY());
		if (checked) {
			Button::SetSprite(renderer.CreateSprite("sprites\\menu\\checkboxfalse.png"));
			Button::SetTransform(spriteLoc->x, spriteLoc->y, GetDefaultScale());
			checked = false;
		}
		else {
			Button::SetSprite(renderer.CreateSprite("sprites\\menu\\checkboxtrue.png"));
			Button::SetTransform(spriteLoc->x, spriteLoc->y, GetDefaultScale());
			checked = true;
		}
		toSwitch = false;
	}
	Button::Draw(renderer);
}

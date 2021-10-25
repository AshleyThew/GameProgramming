#include "slider.h"
#include "vector2.h"
#include "logmanager.h"

Slider ::Slider()
{
}

Slider::~Slider()
{
	delete sliderbar;
	sliderbar = 0;
}

bool Slider::Initialise(Renderer & renderer, bool isActive)
{
	sliderbar = renderer.CreateSprite("sprites\\menu\\soundbar.png");
	sliderbar->SetScale(4.0f);
	Button::Initialise(renderer, "sprites\\menu\\slider.png");

	return false;
}

void Slider::Process(float deltaTime, InputSystem & inputSystem)
{
	Button::Process(deltaTime, inputSystem);

	if (Button::GetMousePressed()) {
		LogManager::GetInstance().Log("mouse prssed");
		if (inputSystem.GetMousePosition().x < sliderbar->GetX() + 80 && inputSystem.GetMousePosition().x > sliderbar->GetX() - 80) {
			Button::SetTransform(inputSystem.GetMousePosition().x, Button::GetSprite()->GetY(), 4.0f);
		}
	}
}

void Slider::Draw(Renderer & renderer)
{
	sliderbar->Draw(renderer);
	Button::Draw(renderer);
}

void Slider::MoveSlider()
{

}

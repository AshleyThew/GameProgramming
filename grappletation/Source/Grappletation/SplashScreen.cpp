#include "SplashScreen.h"
#include "Renderer.h"
#include "Sprite.h"

SplashScreen::SplashScreen()
	: sprite(0)
	, direction(1)
	, alpha(0)
{

}

SplashScreen::~SplashScreen()
{
	delete sprite;
}

bool
SplashScreen::Initialise(Renderer& renderer, const char* spriteLocation)
{
	sprite = renderer.CreateSprite(spriteLocation);
	sprite->SetX(renderer.GetWidth() / 2);
	sprite->SetY(renderer.GetHeight() / 2);
	sprite->SetScale(0.9 * (((float)renderer.GetWidth() - 384) / (float)sprite->GetWidth()));
	sprite->SetAlpha(alpha);
	return false;
}

bool
SplashScreen::Process(float deltaTime)
{
	if (direction && alpha >= 1)
	{
		direction = -1;
	}

	alpha += deltaTime * direction * SPEED;
	sprite->SetAlpha(alpha);
	return alpha <= 0;
}

void
SplashScreen::Draw(Renderer& renderer)
{
	sprite->Draw(renderer);
}

#include "Particle.h"
#include "Renderer.h"
#include "Inlinehelper.h"

Particle::Particle(Vector2 position, Vector2 velocity, const Vector2 acceleration, float lifeSpan, float rotation, float rotationSpeed, float maxScale, float minScale, ChangeOverLifetime scaleOverLifeTime, ChangeOverLifetime alphaOverLifeTime)
	: age(0)
	, alpha(1)
{
	this->position.x = position.x;
	this->position.y = position.y;
	this->velocity.x = velocity.x;
	this->velocity.y = velocity.y;
	this->acceleration.x = acceleration.x;
	this->acceleration.y = acceleration.y;
	this->lifeSpan = lifeSpan;
	this->rotation = rotation;
	this->rotationSpeed = rotationSpeed;
	this->scale = minScale;
	this->maxScale = maxScale;
	this->minScale = minScale;
	this->scaleOverLifeTime = scaleOverLifeTime;
	this->alphaOverLifeTime = alphaOverLifeTime;
}

Particle::~Particle()
{

}

void
Particle::Process(float deltaTime)
{
	age += deltaTime;

	velocity.x += acceleration.x * deltaTime;
	velocity.y += acceleration.y * deltaTime;
	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;

	rotation += rotationSpeed;

	ChangeAttribute(scale, maxScale, scaleOverLifeTime);
	ChangeAttribute(alpha, 1, alphaOverLifeTime);
}

float
Particle::LifeLeft()
{
	return lifeSpan - age;
}

Vector2
Particle::GetPosition()
{
	return position;
}

float
Particle::GetRotation()
{
	return rotation;
}

float
Particle::GetScale()
{
	return scale;
}

float
Particle::GetAlpha()
{
	return alpha;
}

void
Particle::ChangeAttribute(float& attribute, float maximum, ChangeOverLifetime change)
{
	float x = age / lifeSpan;

	switch (change)
	{
	case NONE:
			break;
	case LINEARINCREASE:
		attribute = LinearProgression(x, 0, maximum);
		break;
	case LINEARDECREASE:
		attribute = LinearProgression(x, maximum, 0);
		break;
	case QUADRATICSLOWINCREASE:
		attribute = QuadraticSlowProgression(x, 0, maximum);
		break;
	case QUADRATICFASTINCREASE:
		attribute = QuadraticFastProgression(x, 0, maximum);
		break;
	case QUADRATICSLOWDECREASE:
		attribute = QuadraticSlowProgression(x, maximum, 0);
		break;
	case QUADRATICFASTDECREASE:
		attribute = QuadraticFastProgression(x, maximum, 0);
		break;
	}


}




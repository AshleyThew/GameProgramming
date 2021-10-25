#include "ParticleSystem.h"
#include "Particle.h"
#include "Renderer.h"
#include "Inlinehelper.h"
#include "LogManager.h"
#include <sstream>
#include <list>

ParticleSystem::ParticleSystem()
	: initialPosition{0, 0}
	, particleBoundaries{0, 0}
	, initialVelocity{0, 0}
	, acceleration{0, 0}
	, lifeSpan(0)
	, Initialrotation(0)
	, rotationSpeed(0)
	, maxScale(0)
	, minScale(0)
	, spawnSpeed(0)
	, timeElapsed(0)
	, scaleOverLifeTime(NONE)
	, alphaOverLifeTime(NONE)
	, isPaused(false)
	, isActive(false)

{
}

ParticleSystem::~ParticleSystem()
{
	std::list<Particle*>::iterator it;
	for (it = particles.begin(); it != particles.end(); it++)
	{
		delete (*it);
	}

	delete sprite;
}

bool
ParticleSystem::Initialise(Renderer& renderer, const char* defaultSpriteLocation)
{
	sprite = renderer.CreateSprite(defaultSpriteLocation);
	return false;
}

void
ParticleSystem::Process(float deltaTime)
{


	if (isActive)
	{
		timeElapsed += deltaTime;

		while (timeElapsed >= spawnSpeed)
		{
			timeElapsed -= spawnSpeed;
			Vector2 randomPosition;
			randomPosition.x = initialPosition.x + ((GetRandomPercentage() - 0.5f) * 2 * particleBoundaries.x);
			randomPosition.y = initialPosition.y + ((GetRandomPercentage() - 0.5f) * 2 * particleBoundaries.y);

			Particle* particle = new Particle(randomPosition, initialVelocity, acceleration, lifeSpan, Initialrotation, rotationSpeed, maxScale, minScale, scaleOverLifeTime, alphaOverLifeTime);
			particles.push_back(particle);
			timeElapsed = 0;
		}
	}
	
	if (!isPaused)
	{
		std::list<Particle*>::iterator it;

		it = particles.begin();
		while (!particles.empty() && it != particles.end())
		{
			(*it)->Process(deltaTime);

			if ((*it)->LifeLeft() <= 0)
			{
				delete (*it);
				it = particles.erase(it);


			}

			if (!particles.empty() && it != particles.end())
			{
				it++;

			}

		}
	}


}

void
ParticleSystem::Draw(Renderer& renderer)
{
	std::list<Particle*>::iterator it;
	for (it = particles.begin(); it != particles.end(); it++)
	{
		Vector2 position = (*it)->GetPosition();
		sprite->SetX(position.x);
		sprite->SetY(position.y);
		sprite->SetAngle((*it)->GetRotation());
		sprite->SetAlpha((*it)->GetAlpha());
		sprite->SetScale((*it)->GetScale());

		sprite->Draw(renderer);
	}
}

void
ParticleSystem::Start()
{
	isPaused = false;
	isActive = true;
}

void
ParticleSystem::Stop()
{
	isActive = false;
}

void
ParticleSystem::Pause()
{
	isPaused = true;
	isActive = false;
}

void
ParticleSystem::RemoveAllParticles()
{
	std::list<Particle*>::iterator it;

	it = particles.begin();
	while (!particles.empty() && it != particles.end())
	{
		delete (*it);
		it = particles.erase(it);

		if (!particles.empty() && it != particles.end())
		{
			it++;

		}

	}
}



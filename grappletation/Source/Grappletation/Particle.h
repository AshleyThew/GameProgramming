#pragma once

#include "Vector2.h"
#include "Renderer.h"
#include "Sprite.h"
#include "ParticleSystem.h"

class Particle
{
public:
	Particle(Vector2 position, Vector2 velocity, const Vector2 acceleration, float lifeSpan, float rotation, float rotationSpeed, float maxScale, float minScale, ChangeOverLifetime scaleOverLifeTime, ChangeOverLifetime alphaOverLifeTime);
	~Particle();
	void Process(float deltaTime);
	float LifeLeft();
	Vector2 GetPosition();
	float GetRotation();
	float GetScale();
	float GetAlpha();
protected:
private:
	void ChangeAttribute(float& attribute, float maximum, ChangeOverLifetime change);
public:
protected:
private:
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	float age;
	float lifeSpan;
	float rotation;
	float rotationSpeed;
	float maxScale;
	float minScale;
	float scale;
	float alpha;

	ChangeOverLifetime scaleOverLifeTime;
	ChangeOverLifetime alphaOverLifeTime;
};


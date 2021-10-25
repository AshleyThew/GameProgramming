#pragma once

#include "Vector2.h"
#include <list>

class Particle;
class Renderer;
class Sprite;

enum ChangeOverLifetime
{
    NONE,
    LINEARINCREASE,
    LINEARDECREASE,
    QUADRATICSLOWINCREASE,
    QUADRATICFASTINCREASE,
    QUADRATICSLOWDECREASE,
    QUADRATICFASTDECREASE
};
class ParticleSystem
{
public: 
    ParticleSystem();
    ~ParticleSystem();
    bool Initialise(Renderer& renderer, const char* defaultSpriteLocation);
    void Process(float deltaTime);
    void Draw(Renderer& renderer);

    void RemoveAllParticles();
    void Start();
    void Stop();
    void Pause();
protected:
private:
public:
    Vector2 initialPosition;
    Vector2 particleBoundaries;
    Vector2 initialVelocity;
    Vector2 acceleration;
	float lifeSpan;
	float Initialrotation;
    float rotationSpeed;
    float maxScale;
    float minScale;
    float spawnSpeed;
    float timeElapsed;
    ChangeOverLifetime scaleOverLifeTime;
    ChangeOverLifetime alphaOverLifeTime;
protected:
private:

    bool isPaused;
    bool isActive;
    Sprite* sprite;
    std::list<Particle*> particles;
};




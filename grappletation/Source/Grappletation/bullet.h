// COMP710 Dhanan Patel
#ifndef __BULLET_H__
#define __BULLET_H__

// Local includes:
#include "vector2.h"
#include "inputsystem.h"
#include "Entity.h"
#include "AnimatedSprite.h"

// Forward declarations:
class Renderer;
class Entity;

// Class declaration:
class Bullet : public Entity
{
	// Member methods:
public:
	Bullet();
	~Bullet();
	bool Initialise(Renderer& renderer, float x, float y, float scale, bool ShootRight);
	void Process(float deltaTime);
	void Draw(Renderer& renderer);

	void HitPlayer();

protected:

private:
	Bullet(const Bullet& bullet);
	Bullet& operator=(const Bullet& bullet);

	// Member data:
public:
	int bullet_direction;
	float bullet_speed;

protected:

private:

};
#endif // __BULLET_H__
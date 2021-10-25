// COMP710 GP Framework 2021
#ifndef __ENTITY_H__
#define __ENTITY_H__
// Local includes:
#include "entity.h"
#include "vector2.h"
// Forward declarations:
class Renderer;
class Sprite;
class AnimatedSprite;
class Tile;
// Class declaration:
class Entity
{
	// Member methods:
public:
	Entity();
	~Entity();
	virtual bool Initialise(Renderer& renderer);
	void Process(float deltaTime);
	void Draw(Renderer& renderer);
	void Rotate(float direction);
	bool IsAlive() const;
	void SetDead(bool dead);
	float GetRadius();
	Vector2 GetFacingDirection();
	Vector2& GetPosition();
	Vector2& GetVelocity();
	bool IsCollidingWith(Entity& toCheck);
	void SetAngle(float angle);
protected:
private:
	Entity(const Entity& entity);
	Entity& operator=(const Entity& entity);
	// Member data:
public:
protected:
	AnimatedSprite* m_pAnimatedSprite;
	Sprite* m_pSprite;
	Vector2 m_position;
	Vector2 m_velocity;
	bool m_bAlive;
private:
};
#endif // __ENTITY_H__
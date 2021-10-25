#pragma once

#include "Entity.h"
#include "tile.h"
#include "Renderer.h"
#include "ParticleSystem.h"
#include "Sprite.h"
#include "scenegrappletation.h"
#include <list>

class Renderer;
class InputSystem;
class SoundManager;
class SceneGrappletation;

class Player : public Entity
{
static const int FRAME_LEFT_OFFSET = 24;
public:
	Player();
	~Player();
	virtual bool Initialise(Renderer& renderer);
	void SetScale(float scale);
	virtual void Process(float deltaTime, InputSystem& inputSystem, SoundManager& soundManager);
	virtual void Draw(Renderer& renderer);
	void Start(SceneGrappletation* scene);
	void SetPosition(int x, int y);
	bool DecreaseHealth(SoundManager& soundManager);
	void ResetHealth();
	void DebugDraw();
	void SetSelected(bool selected);
	bool GetSelected();
	void Hit();
protected:
private:
	std::list<Tile*> CheckCollisions();
	void CheckInput(InputSystem& inputSystem, SoundManager& soundManager, bool touchingLeft, bool touchingRight, bool touchingLadder);
public:
	enum PlayerStates
	{
		FALLING,
		IDLE,
		SHOOTING,
	};

	enum HealthStates
	{
		HEALTHY,
		HIT,
		DEAD
	};
protected:
private:
	SceneGrappletation* scene;
	bool invincible;
	bool m_selected;
	const int GRAVITY = 1000;
	const int MOVEMENTSPEED = 100;
	const float FRAMEDURATION = 0.05f;
	const float REACHSPEED = 0.01f;
	const float RETRACTSPEED = 0.002f;
	const float INVINCIBILITYDURATION = 1.0f;
	float timeElapsed;
	float invincibilityTimeElapsed;
	PlayerStates playerState;
	ParticleSystem* particleSystem;
	HealthStates currentHealth;
	Sprite* bloodBackground;
};


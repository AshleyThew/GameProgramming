#define __TURRET_H__
#ifdef __TURRET_H__
#pragma once

#include "Vector2.h"
#include "Sprite.h"
#include "bullet.h"
#include "Player.h"
#include <vector>

class AnimatedSprite;
class InputSystem;
class Renderer;
class Player;

class Turret
{
	// Member Methods:
public:
	Turret(int x, int y);
	~Turret();
	virtual bool Initialise(Renderer& renderer, int set, float scale);
	virtual void Process(float deltaTime);
	virtual void Draw(Renderer& renderer);

	Vector2& Position();
	int& State();
	void ActiveTurret();
	void IdleSetUp();
	void Attack();
	void AddBullets();
	void GetPlayersStatus(Player player1, Player player2);
	//std::vector<Bullet> checkcol();
protected:
private:
	Turret(const Turret& turret);
	Turret& operator=(const Turret& turret);
	// Member Data:
public:
	enum TState
	{
		IDLE,
		SETUP,
		IDLEUP,
		SHOTTING
	};
protected:
private:
	Renderer* m_pRenderer;

	AnimatedSprite* idle;
	AnimatedSprite* setup;
	AnimatedSprite* idle_setup;
	AnimatedSprite* shot_type;

	std::vector<Bullet*> bullets;

	int set;
	float m_scale;
	TState state;
	Vector2 m_position;
	float m_fBulletTimer;
};				  
#endif __TURRET_H__
#include "turret.h"

#include "Vector2.h"
#include "Renderer.h"
#include "InputSystem.h"
#include "AnimatedSprite.h"

Turret::Turret(int x, int y)
	: set(0)
	, state(IDLE)
{
	m_position.x = x;
	m_position.y = y;
}

Turret::~Turret()
{
	delete idle; 
	idle = 0;

	delete setup;
	setup = 0;

	delete idle_setup;
	idle_setup = 0;

	delete shot_type;
	shot_type = 0;

	std::vector<Bullet*>::iterator bullet;
	bullet = bullets.begin();

	while (bullet != bullets.end())
	{
		Bullet* pBullet = *bullet;

		delete pBullet;
		pBullet = 0;

		bullet++;
	}
}

bool
Turret::Initialise(Renderer& renderer, int type, float scale)
{
	idle = renderer.CreateAnimatedSprite("..\\Assets\\turret.png");
	setup = renderer.CreateAnimatedSprite("..\\Assets\\turret.png");
	idle_setup = renderer.CreateAnimatedSprite("..\\Assets\\turret.png");
	shot_type = renderer.CreateAnimatedSprite("..\\Assets\\turret.png");

	m_pRenderer = &renderer;

	m_scale = scale;

	m_position.x = (scale * 8) + (m_position.x * scale * 16);
	m_position.y = (scale * 8) + (m_position.y * scale * 16) + (scale * 2);
	idle->SetX(m_position.x);
	idle->SetY(m_position.y);
	setup->SetX(m_position.x);
	setup->SetY(m_position.y);
	idle_setup->SetX(m_position.x);
	idle_setup->SetY(m_position.y);
	shot_type->SetX(m_position.x);
	shot_type->SetY(m_position.y);

	idle->SetupFrames(40, 33);
	idle->SetScale(scale / 2.5f);
	idle->SetAnimating(true);
	idle->SetFrameBounds(0, 1);
	idle->SetFrameDuration(0.0f);
	idle->SetLooping(false);

	setup->SetupFrames(40, 33);
	setup->SetScale(scale / 2.5f);
	setup->SetAnimating(true);
	setup->SetFrameBounds(0, 11);
	setup->SetFrameDuration(0.15f);
	setup->SetLooping(false);

	idle_setup->SetupFrames(40, 33);
	idle_setup->SetScale(scale / 2.5f);
	idle_setup->SetAnimating(true);
	idle_setup->SetFrameBounds(12, 13);
	idle_setup->SetFrameDuration(0.15f);
	idle_setup->SetLooping(false);

	shot_type->SetupFrames(40, 33);
	shot_type->SetScale(scale / 2.5f);
	shot_type->SetAnimating(true);
	shot_type->SetFrameBounds(12, 17);
	shot_type->SetLooping(true);

	if (type == 1)
	{
		shot_type->SetFrameDuration(0.6f);
	}
	else if (type == 2)
	{
		shot_type->SetFrameDuration(0.3f);
	}

	state = SHOTTING;

	m_fBulletTimer = 0.0f;

	return false;
}

void
Turret::Process(float deltaTime)
{
	/*idle->Process(deltaTime);
	setup->Process(deltaTime);
	idle_setup->Process(deltaTime);
	shot_type->Process(deltaTime);

	idle->SetX(static_cast<int>(m_position.x));
	idle->SetY(static_cast<int>(m_position.y));

	setup->SetX(static_cast<int>(m_position.x));
	setup->SetY(static_cast<int>(m_position.y));

	idle_setup->SetX(static_cast<int>(m_position.x));
	idle_setup->SetY(static_cast<int>(m_position.y));

	shot_type->SetX(static_cast<int>(m_position.x));
	shot_type->SetY(static_cast<int>(m_position.y));*/

	if (m_fBulletTimer <= 0.0f)
	{
		AddBullets();
		m_fBulletTimer = 3.0f;
	}

	if (m_fBulletTimer > 0.0f)
	{
		m_fBulletTimer = m_fBulletTimer - deltaTime;
	}

	std::vector<Bullet*>::iterator bullet;

	bullet = bullets.begin();

	while (bullet != bullets.end())
	{
		Bullet* pBullet = *bullet;

		if (pBullet->IsAlive())
		{
			pBullet->Process(deltaTime);

			/*if ((*pBullet).IsCollidingWith(*m_characters[0]) == true)
			{
				pBullet->HitPlayer();
				m_characters[0]->Hit();
			}

			if ((*pBullet).IsCollidingWith(*m_characters[1]) == true)
			{
				pBullet->HitPlayer();
				m_characters[1]->Hit();
			}*/
		}
		bullet++;
	}
}

void
Turret::Draw(Renderer& renderer)
{
	if (state == IDLE) 
	{
		idle->Draw(renderer);
	}
	else if (state == SETUP)
	{
		setup->Draw(renderer);
	}
	else if (state == IDLEUP)
	{
		idle_setup->Draw(renderer);
	}
	else if (state == SHOTTING)
	{
		shot_type->Draw(renderer);
	}

	std::vector<Bullet*>::iterator bullet;

	bullet = bullets.begin();

	while (bullet != bullets.end())
	{
		if ((*bullet)->IsAlive())
		{
			(*bullet)->Draw(renderer);
		}
		bullet++;
	}	
}

Vector2&
Turret::Position()
{
	return m_position;
}

int&
Turret::State()
{
	int x = 0;

	if (state == IDLE)
	{
		x = 0;
	}
	else if (state == SETUP)
	{
		x = 1;
	}
	else if (state == IDLEUP)
	{
		x = 2;
	}
	else if (state == SHOTTING)
	{
		x = 3;
	}

	return x;
}

void
Turret::ActiveTurret()
{
	state = SETUP;
}

void
Turret::IdleSetUp()
{
	state = IDLEUP;
}

void
Turret::Attack()
{
	state = SHOTTING;
}


void
Turret::AddBullets()
{
	Bullet* bullet = new Bullet();
	bullet->Initialise(*m_pRenderer, m_position.x, m_position.y, m_scale, true);
	bullets.push_back(bullet);
}

void
Turret::GetPlayersStatus(Player player1, Player player2)
{
	std::vector<Bullet*>::iterator bullet;

	bullet = bullets.begin();

	while (bullet != bullets.end())
	{
		Bullet* pBullet = *bullet;

		if (pBullet->IsAlive())
		{
			if ((*pBullet).IsCollidingWith(player1) == true)
			{
				pBullet->HitPlayer();
				player1.Hit();
			}

			if ((*pBullet).IsCollidingWith(player2) == true)
			{
				pBullet->HitPlayer();
				player2.Hit();
			}
		}
		bullet++;
	}
}
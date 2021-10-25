// COMP710 GP Framework 2021
#ifndef __SCENEGRAPPLETATION_H__
#define __SCENEGRAPPLETATION_H__

// Local includes:
#include "scene.h"
#include "inputsystem.h"
#include "XboxController.h"
#include "levelmanager.h"
#include "tile.h"
#include "turret.h"
#include "bullet.h"
#include "Sprite.h"
#include "Player.h"
#include "mainmenu.h"
#include "pausemenu.h"

// Forward declarations:
class Renderer;
class Sprite;
class LevelManager;
class Player;

// Class declaration:
class SceneGrappletation : public Scene
{
	// Member methods:
public:
	SceneGrappletation();
	virtual ~SceneGrappletation();

	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime, InputSystem& inputsystem, SoundManager& soundManager);
	virtual void StartLevel();
	virtual void Draw(Renderer& renderer);
	virtual void DebugDraw();
	LevelManager* GetLevelManager();

protected:

private:
	SceneGrappletation(const SceneGrappletation& scenegrappletation);
	SceneGrappletation& operator=(const SceneGrappletation& scenegrappletation);

	// Member data:
public:

protected:

private:
	LevelManager* level;
	MainMenu* menu;
	PauseMenu* pause;

	int turretmode;
	//Sprite* sprite;
	int m_curCharacter;
	Player* m_characters[2];
	int i;
};

#endif // __SCENEGRAPPLETATION_H__
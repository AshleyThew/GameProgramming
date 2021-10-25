#pragma once

// local includes:
#include "scene.h"
#include "Vector2.h"
#include "tile.h"
#include <fstream>
#include <list>
#include <map>
#include <vector>
#include <string>


// Foward Declarations:
class Renderer;
class AnimatedSprite;
class Sprite;
class Tile;
class Vector2;
class Sprite;
class InteractableButton;
class interactableLever;
class InputSystem;
class SoundManager;
class Door;
class Gem;
class Turret;

class LevelManager
{

	// Member Methods
public:
	LevelManager();
	virtual ~LevelManager();

	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime, InputSystem& inputSystem, SoundManager& soundManager);
	virtual void Draw(Renderer& renderer);
	virtual void DebugDraw();
	int CheckInput(char input);
	void SetLevel(int level);
	int GetLevel();
	int GetLevelScale();
	void ResetAllLevels();
	std::map<std::string, Tile*> GetLevelTiles();
	std::vector<InteractableButton*> GetAllButtons();
	std::vector<interactableLever*> GetAllLevers();
	std::vector<Door*> GetAllDoors();
	std::vector<Gem*> GetAllGems();

	Vector2 GetPortalGunnerStartLocation();
	Vector2 GetGrapplerStartLocation();

protected:

private:
	LevelManager(const LevelManager& levelmanager);
	LevelManager& operator=(const LevelManager& levelmanager);
	//void SetUpEntityPosition(std::map<std::string, > entities[3]);

	// Member Data
public:
protected:
private:
	const int MAXLEVELS = 3;

	std::vector<Vector2*> emptyTiles[3];

	std::fstream levelFile[3];
	std::map<std::string, Tile*> levelTiles[3];
	std::map<std::string, Sprite*> levelBackgroundTiles[3];
	std::vector<InteractableButton*> buttons[3];
	std::vector<interactableLever*> levers[3];
	std::vector<Door*> doors[3];
	std::vector<Gem*> gems[3];
	std::vector<Turret*> turrets[3];

	Vector2 grapplerStartCoordinates[3];
	Vector2 portalGunnerStartCoordinates[3];

	Vector2 levelDimensions[3];
	float levelScale[3];
	int currentLevel;
	const int NUMCHUNKSHADOW = 2;
};
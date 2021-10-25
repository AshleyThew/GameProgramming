#pragma once
#define LEVELMANAGERSCENE_H__
#ifdef LEVELMANAGERSCENE_H__

// local includes:
#include "scene.h"
#include "Vector2.h"
#include <fstream>
#include <list>



// Foward Declarations:
class Renderer;
class InputSystem;
class AnimatedSprite;
class Sprite;
class Tile;
class Player;
class SoundManager;
class FireSnail;
class Vector2;
class LocationMaster;
class FireFly;
class Button;
class Coin;
class SplashScreen;

class LevelManagerScene : public Scene
{
	// Member Methods
public:
	LevelManagerScene();
	virtual ~LevelManagerScene();

	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime, InputSystem& inputSystem, SoundManager& soundManager, Game& game);
	virtual void Draw(Renderer& renderer);
	void CheckInput(char& input);
	virtual void DebugDraw();

protected:
private:
	void CreateNewCoin();
	void ChangeNumbers(int value);
	void ChangeHighScore();
	// Member Data
public:
	enum Tiles
	{
		TOPLEFT,
		TOP,
		TOPRIGHT,
		LEFT,
		CENTER,
		RIGHT,
		BOTTOMLEFT,
		BOTTOM,
		BOTTOMRIGHT
	};
protected:
private:
	const int MAXLEVELS = 3;

	std::list<Vector2*> emptyTiles[3];

	std::fstream levelFile[3];
	std::list<Tile*> levelTiles[3];

	AnimatedSprite* numbers[3];

	Button* backButton;
	Button* controlsButton;
	Button* levelButtons[3];
	Button* playButton;
	Button* quitButton;

	Coin* activeCoin;

	FireFly* fireFlyList[10];
	FireSnail* fireSnailList[10];
	int numFireFly;
	int numFireSnail;

	float levelScale[3];
	int currentLevel;
	int highScores[3];
	int score;

	int currentControllerMenuButton;

	Player* player;

	SplashScreen* autSplashScreen;
	SplashScreen* fmodSplashScreen;

	Sprite* arrowKeysSprite;
	Sprite* collectCoinsSprite;
	Sprite* controllerSwitchSprite;
	Sprite* keyboardSprite;
	Sprite* controllerSprite;
	Sprite* keyBoardSwitchSprite;
	Sprite* thumbstickSprite;

	Sprite* highScoreSprite;
	Sprite* levelBackground;
	Sprite* menuBackgrounds[5];
	Sprite* title;

	Vector2 center;
	Vector2 levelDimensions[3];

	enum GameStates
	{
		LEVEL1,
		LEVEL2,
		LEVEL3,
		MAINMENU,
		CONTROLS,
		AUTSPLASHSCREEN,
		FMODSPLASHSCREEN
	};

	GameStates gameState;
};

#endif LEVELMANAGERSCENE_H__ 


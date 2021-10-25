#include "LevelManagerScene.h"
#include "Renderer.h"
#include "InputSystem.h"
#include "LogManager.h"
#include "Animatedsprite.h"
#include "Sprite.h"
#include "imgui.h"
#include "Tile.h"
#include "Player.h"
#include "SoundManager.h"
#include "FireSnail.h"
#include "LocationMaster.h"
#include "FireFly.h"
#include "Vector2.h"
#include "Button.h"
#include "Game.h"
#include "Inlinehelper.h"
#include "Coin.h"
#include "SplashScreen.h"
#include "XboxController.h"
#include <sstream>
#include <fstream>



LevelManagerScene::LevelManagerScene()
	: numbers{ 0 }
	, backButton(0)
	, controlsButton(0)
	, levelButtons{ 0 }
	, playButton(0)
	, quitButton(0)
	, activeCoin(0)
	, fireFlyList{ 0 }
	, fireSnailList{ 0 }
	, numFireFly(0)
	, numFireSnail(0)
	, levelScale{ 0 }
	, currentLevel{ 0 }
	, highScores{ 0 }
	, score(0)
	, currentControllerMenuButton(0)
	, player(0)
	, autSplashScreen(0)
	, fmodSplashScreen(0)
	, arrowKeysSprite(0)
	, collectCoinsSprite(0)
	, controllerSwitchSprite(0)
	, keyboardSprite(0)
	, controllerSprite(0)
	, keyBoardSwitchSprite(0)
	, thumbstickSprite(0)
	, highScoreSprite(0)
	, levelBackground(0)
	, menuBackgrounds{0}
	, title(0)
	, center(0, 0)
	, gameState(AUTSPLASHSCREEN)


{
	// Read Levels from File
	levelFile[0].open("..\\Source\\Levels\\Level1.txt");
	levelFile[1].open("..\\Source\\Levels\\Level2.txt");
	levelFile[2].open("..\\Source\\Levels\\Level3.txt");
}

LevelManagerScene::~LevelManagerScene()
{
	std::list<Vector2*>::iterator itEmptyTiles;
	std::list<Tile*>::iterator itLevelTiles;

	for (int i = 0; i < MAXLEVELS; i++)
	{
		for (itLevelTiles = levelTiles[i].begin(); itLevelTiles != levelTiles[i].end(); itLevelTiles++)
		{
			delete (*itLevelTiles);
		}

		for (itEmptyTiles = emptyTiles[i].begin(); itEmptyTiles != emptyTiles[i].end(); itEmptyTiles++)
		{
			delete (*itEmptyTiles);
		}
	}

	delete numbers[0];
	delete numbers[1];
	delete numbers[2];

	delete backButton;
	delete controlsButton;
	delete levelButtons[0];
	delete levelButtons[1];
	delete levelButtons[2];
	delete playButton;
	delete quitButton;

	delete activeCoin;

	for (int i = 0; i < 10; i++)
	{
		delete fireFlyList[i];
		delete fireSnailList[i];
	}

	delete player;

	delete arrowKeysSprite;
	delete collectCoinsSprite;
	delete controllerSwitchSprite;
	delete keyboardSprite;
	delete controllerSprite;
	delete keyBoardSwitchSprite;
	delete thumbstickSprite;

	delete autSplashScreen;
	delete fmodSplashScreen;
	delete highScoreSprite;
	delete levelBackground;
	delete menuBackgrounds[0];
	delete menuBackgrounds[1];
	delete menuBackgrounds[2];
	delete menuBackgrounds[3];
	delete menuBackgrounds[4];
	delete title;
}

bool
LevelManagerScene::Initialise(Renderer& renderer)
{
	center.x = renderer.GetWidth() / 2;
	center.y = renderer.GetHeight() / 2;
	srand((int)time(0));

	for (int level = 0; level < MAXLEVELS; level++)
	{
		char input;
		int maxColumns = 0;
		int currentRow = 0;

		for (int i = 0; levelFile[level] >> input; i++)
		{
			int x = 0;
			CheckInput(input);
			// Check if input is a tile
			if (input >= 0 && input <= 9)
			{
				levelTiles[level].push_back(new Tile(input, i, currentRow));
			}
			else if (input == '-')
			{
				emptyTiles[level].push_back(new Vector2(i, currentRow));
			}
			else if (input == '|')
			{
				currentRow++;
				i = -1;
			}

			if (maxColumns < (i + 1))
			{
				maxColumns = i + 1;
			}
		}

		// Scale tiles so they fit the screen
		if ((float)renderer.GetWidth() / (float)maxColumns < (float)renderer.GetHeight() / (float)currentRow)
		{
			levelScale[level] = (0.8 * renderer.GetWidth()) / (float)maxColumns;
		}
		else
		{
			levelScale[level] = (0.8 * renderer.GetHeight()) / (float)currentRow;
		}
		levelScale[level] /= 8;

		std::list<Tile*>::iterator it;

		// Set up each tile
		for (it = levelTiles[level].begin(); it != levelTiles[level].end(); it++)
		{
			(*it)->Initialise(renderer);
			Vector2 id = (*it)->GetID();
			float x = (levelScale[level] * 4) + (renderer.GetWidth() / 10) + (id.x * levelScale[level] * 8);
			float y = (levelScale[level] * 4) + (renderer.GetHeight() / 10) + (id.y * levelScale[level] * 8);
			(*it)->SetPosition(x, y);
			(*it)->SetScale(levelScale[level]);

		}

		levelDimensions[level].x = maxColumns;
		levelDimensions[level].x = currentRow;
	}

	for (int i = 0; i < 3; i++)
	{
		numbers[i] = renderer.CreateAnimatedSprite("..\\Assets\\Numbers.png");
		numbers[i]->SetupFrames(10, 15);
		numbers[i]->SetX(1400 + (100 * i));
		numbers[i]->SetY(900);
		numbers[i]->SetScale(7);
	}

	backButton = new Button();
	backButton->Initialise(renderer, "..\\Assets\\back.png");
	backButton->SetTransform(renderer.GetWidth() / 2, 900, 7);

	controlsButton = new Button();
	controlsButton->Initialise(renderer, "..\\Assets\\Controls.png");
	controlsButton->SetTransform(renderer.GetWidth() / 2, 750, 7);

	for (int i = 0; i < 3; i++)
	{
		levelButtons[i] = new Button();
		std::ostringstream ss;
		ss << "..\\Assets\\Level" << (i + 1) << ".png";
		levelButtons[i]->Initialise(renderer, &ss.str()[0]);
		levelButtons[i]->SetTransform(renderer.GetWidth()/2, 600, 7);
	}

	playButton = new Button();
	playButton->Initialise(renderer, "..\\Assets\\Play.png");
	playButton->SetTransform(renderer.GetWidth()/2, 450, 7);
	quitButton = new Button();
	quitButton->Initialise(renderer, "..\\Assets\\Quit.png");
	quitButton->SetTransform(renderer.GetWidth() / 2, 900, 7);

	activeCoin = new Coin();
	activeCoin->Initialise(renderer);

	for (int i = 0; i < 10; i++)
	{

		fireSnailList[i] = new FireSnail();
		fireSnailList[i]->Initialise(renderer);
		fireFlyList[i] = new FireFly();
		fireFlyList[i]->Initialise(renderer);
	}

	player = new Player();
	player->Initialise(renderer);

	autSplashScreen = new SplashScreen();
	autSplashScreen->Initialise(renderer, "..\\Assets\\aut-logo-block.png");
	fmodSplashScreen = new SplashScreen();
	fmodSplashScreen->Initialise(renderer, "..\\Assets\\FMOD Logo White - Black Background.png");

	arrowKeysSprite = renderer.CreateSprite("..\\Assets\\Arrow Keys.png");
	arrowKeysSprite->SetX((renderer.GetWidth() / 2) - 400);
	arrowKeysSprite->SetY(550);
	arrowKeysSprite->SetScale(0.65);
	collectCoinsSprite = renderer.CreateSprite("..\\Assets\\Collect Coins.png");
	collectCoinsSprite->SetX((renderer.GetWidth() / 2));
	collectCoinsSprite->SetY(750);
	controllerSwitchSprite = renderer.CreateSprite("..\\Assets\\Controller Switch.png");
	controllerSwitchSprite->SetX((renderer.GetWidth() / 2) + 400);
	controllerSwitchSprite->SetY(600);
	controllerSwitchSprite->SetScale(0.65);
	keyboardSprite = renderer.CreateSprite("..\\Assets\\Keyboard.png");
	keyboardSprite->SetX((renderer.GetWidth() / 2) - 400);
	keyboardSprite->SetY(450);
	keyboardSprite->SetScale(7);
	controllerSprite = renderer.CreateSprite("..\\Assets\\Controller.png");
	controllerSprite->SetX((renderer.GetWidth() / 2) + 400);
	controllerSprite->SetY(450);
	controllerSprite->SetScale(7);
	keyBoardSwitchSprite = renderer.CreateSprite("..\\Assets\\Space.png");
	keyBoardSwitchSprite->SetX((renderer.GetWidth() / 2) - 400);
	keyBoardSwitchSprite->SetY(600);
	keyBoardSwitchSprite->SetScale(0.65);
	thumbstickSprite = renderer.CreateSprite("..\\Assets\\Thumbstick.png");
	thumbstickSprite->SetX((renderer.GetWidth() / 2) + 400);
	thumbstickSprite->SetY(550);
	thumbstickSprite->SetScale(0.65);

	highScoreSprite = renderer.CreateSprite("..\\Assets\\High Score.png");
	highScoreSprite->SetX(1550);
	highScoreSprite->SetY(800);
	highScoreSprite->SetScale(3);
	title = renderer.CreateSprite("..\\Assets\\Title.png");
	title->SetX(renderer.GetWidth() / 2);
	title->SetY(250);
	title->SetScale(7);

	for (int i = 0; i < 5; i++)
	{
		std::ostringstream ss;
		ss << "..\\Assets\\MenuBackground" << i << ".png";
		menuBackgrounds[i] = renderer.CreateSprite(&ss.str()[0]);
		menuBackgrounds[i]->SetX(renderer.GetWidth() / 2);
		menuBackgrounds[i]->SetY(renderer.GetHeight() / 2);
		menuBackgrounds[i]->SetScale(1.1 * (((float)renderer.GetWidth() - 384) / (float)menuBackgrounds[i]->GetWidth()));
	}

	levelBackground = renderer.CreateSprite("..\\Assets\\Level Background.png");
	levelBackground->SetX(renderer.GetWidth()/2);
	levelBackground->SetY(renderer.GetHeight() / 2);
	levelBackground->SetScale((float)renderer.GetWidth() / (float)levelBackground->GetWidth());

	return false;
}

void
LevelManagerScene::Process(float deltaTime, InputSystem& inputSystem, SoundManager& soundManager, Game& game)
{
	if (gameState == AUTSPLASHSCREEN)
	{
		if (autSplashScreen->Process(deltaTime))
		{
			gameState = FMODSPLASHSCREEN;
		}
	}
	else if (gameState == FMODSPLASHSCREEN)
	{
		if (fmodSplashScreen->Process(deltaTime))
		{
			gameState = MAINMENU;
			soundManager.PlaySound("Motherlode");
		}
	}
	else if (gameState == MAINMENU)
	{
		Vector2 mousePosition = inputSystem.GetMousePosition();
		for (int i = 0; i < 5; i++)
		{
			menuBackgrounds[i]->Process(deltaTime);
			menuBackgrounds[i]->SetX(center.x + (i * 0.02 * (mousePosition.x - center.x)));
			menuBackgrounds[i]->SetY(center.y + (i * 0.02 * (mousePosition.y - center.y)));
		}
	
		highScoreSprite->Process(deltaTime);
		title->Process(deltaTime);

		if (inputSystem.GetNumberOfControllersAttached())
		{
			if (inputSystem.GetController(0)->GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_UP) == BS_PRESSED)
			{
				if (currentControllerMenuButton > 0)
				{
					currentControllerMenuButton--;
					soundManager.PlaySound("Select");
				}
			}
			else if (inputSystem.GetController(0)->GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == BS_PRESSED)
			{
				if (currentControllerMenuButton < 3)
				{
					currentControllerMenuButton++;
					soundManager.PlaySound("Select");
				}
			}

			playButton->SetPressed(currentControllerMenuButton == 0);
			levelButtons[currentLevel]->SetPressed(currentControllerMenuButton == 1);
			controlsButton->SetPressed(currentControllerMenuButton == 2);
			quitButton->SetPressed(currentControllerMenuButton == 3);
		}

		if (levelButtons[currentLevel]->Process(deltaTime, inputSystem, soundManager))
		{
			currentLevel++;
			if (currentLevel >= MAXLEVELS)
			{
				currentLevel = 0;
			}
			ChangeNumbers(highScores[currentLevel]);
		}

		if (playButton->Process(deltaTime, inputSystem, soundManager))
		{
			gameState = (GameStates)currentLevel;
			player->Start(levelTiles[currentLevel]);
			player->ResetHealth();
			score = 0;
			CreateNewCoin();

			for (int i = 0; i < 10; i++)
			{
				int randomTile = GetRandom(1, emptyTiles[currentLevel].size() - 1);
				std::list<Vector2*>::iterator itTile;
				itTile = emptyTiles[currentLevel].begin();

				for (int i = 0; i < randomTile; i++)
				{
					itTile++;
				}

				float tileSize = levelTiles[currentLevel].front()->GetScale() * 8;
				Vector2 position;
				position.x = (tileSize * (*itTile)->x) + 192 + tileSize / 2;
				position.y = (tileSize * (*itTile)->y) + 108 + tileSize / 2;

				fireFlyList[i]->SetDead(true);
				fireSnailList[i]->SetDead(true);
				fireFlyList[i]->Start(levelTiles[currentLevel], levelDimensions[currentLevel], position);
				fireSnailList[i]->Start(levelTiles[currentLevel]);
			}

			numFireFly = 0;
			numFireSnail = 0;
			ChangeNumbers(0);
		}
		if (controlsButton->Process(deltaTime, inputSystem, soundManager))
		{
			gameState = CONTROLS;
		}
		if (quitButton->Process(deltaTime, inputSystem, soundManager))
		{
			game.Quit();
		}


		numbers[0]->Process(deltaTime);
		numbers[1]->Process(deltaTime);
		numbers[2]->Process(deltaTime);
	}
	else if (gameState == CONTROLS)
	{
		Vector2 mousePosition = inputSystem.GetMousePosition();
		for (int i = 0; i < 5; i++)
		{
			menuBackgrounds[i]->Process(deltaTime);
			menuBackgrounds[i]->SetX(center.x + (i * 0.02 * (mousePosition.x - center.x)));
			menuBackgrounds[i]->SetY(center.y + (i * 0.02 * (mousePosition.y - center.y)));
		}
		if (inputSystem.GetNumberOfControllersAttached())
		{
			backButton->SetPressed(true);
		}
		if (backButton->Process(deltaTime, inputSystem, soundManager))
		{
			gameState = MAINMENU;
		}
	}
	else
	{
		levelBackground->Process(deltaTime);

		std::list<Tile*>::iterator itTiles;
		for (itTiles = levelTiles[currentLevel].begin(); itTiles != levelTiles[currentLevel].end(); itTiles++)
		{
			(*itTiles)->Process(deltaTime, inputSystem);
		}

		player->Process(deltaTime, inputSystem, soundManager);

		if (inputSystem.GetKeyState(SDL_SCANCODE_ESCAPE) == BS_PRESSED || inputSystem.GetController(0)->GetButtonState(SDL_CONTROLLER_BUTTON_START) == BS_PRESSED)
		{
			gameState = MAINMENU;
			ChangeHighScore();
			ChangeNumbers(highScores[currentLevel]);
		}

		activeCoin->Process(deltaTime);


		if (player->IsCollidingWith(*activeCoin))
		{
			soundManager.PlaySound("Coin");
			player->ResetHealth();
			CreateNewCoin();
			score++;
			ChangeNumbers(score);

			if (!((score - 1) % 3))
			{
				if (score % 2)
				{
					if (numFireSnail < 10)
					{
						fireSnailList[numFireSnail++]->SetDead(false);
					}
				}
				else
				{
					if (numFireFly < 10)
					{
						fireFlyList[numFireFly++]->SetDead(false);
					}
				}
			}

			if (!(score % 5))
			{
				if (score % 2)
				{
					if (numFireSnail < 10)
					{
						fireSnailList[numFireSnail++]->SetDead(false);
					}
				}
				else
				{
					if (numFireFly < 10)
					{
						fireFlyList[numFireFly++]->SetDead(false);
					}
				}
			}
		}

		for (int i = 0; i < 10; i++)
		{
			fireFlyList[i]->Process(deltaTime, soundManager, player->GetPosition());
			fireSnailList[i]->Process(deltaTime, soundManager);
		}

		bool collidingWithEnemy = false;
		for (int i = 0; i < numFireSnail && !collidingWithEnemy; i++)
		{
			if (player->IsCollidingWith(*fireSnailList[i]))
			{
				collidingWithEnemy = true;
			}
		}
		for (int i = 0; i < numFireFly && !collidingWithEnemy; i++)
		{
			if (player->IsCollidingWith(*fireFlyList[i]))
			{
				collidingWithEnemy = true;
			}
		}

		if (collidingWithEnemy)
		{
			if (player->DecreaseHealth(soundManager))
			{
				gameState = MAINMENU;
				ChangeHighScore();
				ChangeNumbers(highScores[currentLevel]);
			}
		}



	}
}

void
LevelManagerScene::Draw(Renderer& renderer)
{
	if (gameState == AUTSPLASHSCREEN)
	{
		autSplashScreen->Draw(renderer);
	}
	else if (gameState == FMODSPLASHSCREEN)
	{
		fmodSplashScreen->Draw(renderer);
	}
	else if (gameState == MAINMENU)
	{
		for (int i = 0; i < 5; i++)
		{
			menuBackgrounds[i]->Draw(renderer);
		}

		highScoreSprite->Draw(renderer);
		title->Draw(renderer);
		levelButtons[currentLevel]->Draw(renderer);
		playButton->Draw(renderer);
		controlsButton->Draw(renderer);
		quitButton->Draw(renderer);
	}
	else if (gameState == CONTROLS)
	{
		for (int i = 0; i < 5; i++)
		{
			menuBackgrounds[i]->Draw(renderer);
		}
		title->Draw(renderer);
		backButton->Draw(renderer);

		arrowKeysSprite->Draw(renderer);
		collectCoinsSprite->Draw(renderer);
		controllerSwitchSprite->Draw(renderer);
		keyboardSprite->Draw(renderer);
		controllerSprite->Draw(renderer);
		keyBoardSwitchSprite->Draw(renderer);
		thumbstickSprite->Draw(renderer);
	}
	else
	{
		levelBackground->Draw(renderer);

		std::list<Tile*>::iterator it;
		for (it = levelTiles[currentLevel].begin(); it != levelTiles[currentLevel].end(); it++)
		{
			(*it)->Draw(renderer);
		}

		player->Draw(renderer);

		activeCoin->Draw(renderer);


		for (int i = 0; i < 10; i++)
		{
			fireSnailList[i]->Draw(renderer);
			fireFlyList[i]->Draw(renderer);
		}
	}

	bool non0 = false;
	for (int i = 0; i < 3; i++)
	{
		if (numbers[i]->GetFrame())
		{
			non0 = true;
		}

		if (non0)
		{
			numbers[i]->Draw(renderer);
		}
	}
}

void LevelManagerScene::DebugDraw()
{
	player->DebugDraw();
}

void LevelManagerScene::CheckInput(char& input)
{
	switch (input)
	{
	case 't':
		input = TOP;
		break;
	case 'r':
		input = RIGHT;
		break;
	case 'b':
		input = BOTTOM;
		break;
	case 'l':
		input = LEFT;
		break;
	case 'q':
		input = TOPLEFT;
		break;
	case 'p':
		input = TOPRIGHT;
		break;
	case 'm':
		input = BOTTOMRIGHT;
		break;
	case 'z':
		input = BOTTOMLEFT;
		break;
	case 'c':
		input = CENTER;
		break;
	}
}

void
LevelManagerScene::CreateNewCoin()
{
	int randomTile = GetRandom(1, emptyTiles[currentLevel].size() - 1);
	std::list<Vector2*>::iterator itTile;
	itTile = emptyTiles[currentLevel].begin();

	for (int i = 0; i < randomTile; i++)
	{
		itTile++;
	}

	float tileSize = levelTiles[currentLevel].front()->GetScale() * 8;
	Vector2 position;
	position.x = (tileSize * (*itTile)->x) + 192 + tileSize/2;
	position.y = (tileSize * (*itTile)->y) + 108 + tileSize/2;

	activeCoin->SetTransform(position, levelTiles[currentLevel].front()->GetScale());
}

void
LevelManagerScene::ChangeNumbers(int value)
{
	for (int i = 0; i < 3; i++)
	{
		int n = (value % (int)(pow(10, i+1)))/pow(10, i);
		numbers[2-i]->SetFrame(n);
	}
}

void
LevelManagerScene::ChangeHighScore()
{
	if (score > highScores[currentLevel])
	{
		highScores[currentLevel] = score;
	}
}

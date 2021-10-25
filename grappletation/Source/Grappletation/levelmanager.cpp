// COMP710 Dhanan Patel
// This include:
#include "levelmanager.h"

// Local includes:
#include "renderer.h"
#include "Entity.h"
#include "inputsystem.h"
#include "Inlinehelper.h"
#include "InteractableButton.h"
#include "interactableLever.h"
#include "InputSystem.h"
#include "SoundManager.h"
#include "Door.h"
#include "imgui.h"
#include "Gem.h"
#include "Ladder.h"
#include "turret.h"

// Library includes:
#include <cassert>
#include <sstream>
#include <string>
#include <iostream>

LevelManager::LevelManager()
	: currentLevel{ 0 }
{
	levelFile[0].open("..\\Source\\Levels\\Level1.txt");
	levelFile[1].open("..\\Source\\Levels\\Level2.txt");
	levelFile[2].open("..\\Source\\Levels\\Level3.txt");
}

LevelManager::~LevelManager()
{
	for (int i = 0; i < MAXLEVELS; i++)
	{
		for (std::map<std::string, Tile*>::iterator itLevelTiles = levelTiles[i].begin(); itLevelTiles != levelTiles[i].end(); itLevelTiles++)
		{
			delete itLevelTiles->second;
		}

		for (std::vector<Vector2*>::iterator itEmptyTiles = emptyTiles[i].begin(); itEmptyTiles != emptyTiles[i].end(); itEmptyTiles++)
		{
			delete (*itEmptyTiles);
		}

		for (std::map<std::string, Sprite*>::iterator itBackgroundTiles = levelBackgroundTiles[i].begin(); itBackgroundTiles != levelBackgroundTiles[i].end(); itBackgroundTiles++)
		{
			delete itBackgroundTiles->second;
		}

		for (std::vector<InteractableButton*>::iterator itButtons = buttons[i].begin(); itButtons != buttons[i].end(); itButtons++)
		{
			delete (*itButtons);
		}
		for (std::vector<interactableLever*>::iterator itLever = levers[i].begin(); itLever != levers[i].end(); itLever++)
		{
			delete (*itLever);
		}
		for (std::vector<Door*>::iterator itDoor = doors[i].begin(); itDoor != doors[i].end(); itDoor++)
		{
			delete (*itDoor);
		}
		for (std::vector<Gem*>::iterator itGem = gems[i].begin(); itGem != gems[i].end(); itGem++)
		{
			delete (*itGem);
		}
		for (std::vector<Turret*>::iterator itTurret = turrets[i].begin(); itTurret != turrets[i].end(); itTurret++)
		{
			delete (*itTurret);
		}
	}
}

bool
LevelManager::Initialise(Renderer& renderer)
{
	for (int level = 0; level < MAXLEVELS; level++)
	{
		char input;
		int maxColumns = 0;
		int currentRow = 0;
		bool readEntireLevel = false;

		for (int i = 0; levelFile[level] >> input; i++)
		{
			if (!readEntireLevel)
			{
				int typeOfTile = CheckInput(input);
				// Check if input is a tile
				if (typeOfTile != -1)
				{
					levelTiles[level][Vector2ToString(i, currentRow)] = new Tile(i, currentRow, (TileCategory)typeOfTile);
				}
				else if (input == 'B')
				{
					buttons[level].push_back(new InteractableButton(i, currentRow));
				}
				else if (input == 'L')
				{
					levers[level].push_back(new interactableLever(i, currentRow));
				}
				else if (input == 'D')
				{
					doors[level].push_back(new Door(i, currentRow));
				}
				else if (input == 'C')
				{
					gems[level].push_back(new Gem(i, currentRow));
				}
				else if (input == 'T')
				{
					//Facing Right
					turrets[level].push_back(new Turret(i, currentRow));
				}
				else if (input == 't')
				{
					//Facing Left
					turrets[level].push_back(new Turret(i, currentRow));
				}
				else if (input == 'G')
				{
					grapplerStartCoordinates[level].x = i;
					grapplerStartCoordinates[level].y = currentRow;
				}
				else if (input == 'P')
				{
					portalGunnerStartCoordinates[level].x = i;
					portalGunnerStartCoordinates[level].y = currentRow;
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

				if (input == '!')
				{
					readEntireLevel = true;
				}
				else
				{
					if (maxColumns < (i + 1))
					{
						maxColumns = i + 1;
					}
				}
			}
			else
			{
				char inputType = input;
				levelFile[level] >> input;
				int inputTypeN = (int)input - 48;
				levelFile[level] >> input;

				while ((input != 'D'))
				{
					inputTypeN *= 10;
					inputTypeN += (int)input - 48;
					levelFile[level] >> input;
				} 

				levelFile[level] >> input;
				int outputTypeN = (int)input - 48;
				levelFile[level] >> input;

				while ((input != '|'))
				{
					outputTypeN *= 10;
					outputTypeN += (int)input - 48;
					levelFile[level] >> input;
				}

				int x = 0;

				if (inputType == 'L')
				{
					levers[level][inputTypeN]->SetAttachedDoor(doors[level][outputTypeN]);
				}
				else if (inputType == 'B')
				{
					buttons[level][inputTypeN]->SetAttachedDoor(doors[level][outputTypeN]);
				}
			}
			
		}

		// Scale tiles so they fit the screen
		if ((float)renderer.GetWidth() / (float)maxColumns < (float)renderer.GetHeight() / (float)currentRow)
		{
			levelScale[level] = (renderer.GetWidth()) / (float)maxColumns;
		}
		else
		{
			levelScale[level] = (renderer.GetHeight()) / (float)currentRow;
		}
		levelScale[level] /= 16;




		std::map<std::string, Tile*>::iterator it;

		// Set up each tile
		for (it = levelTiles[level].begin(); it != levelTiles[level].end(); it++)
		{
			Vector2 id = (*it).second->GetID();
			TileCategory tileCategory = (*it).second->GetTileCategory();

			std::map<std::string, Tile*>::iterator upIt = levelTiles[level].find(Vector2ToString(id.x, id.y - 1));
			std::map<std::string, Tile*>::iterator downIt = levelTiles[level].find(Vector2ToString(id.x, id.y + 1));
			std::map<std::string, Tile*>::iterator leftIt = levelTiles[level].find(Vector2ToString(id.x - 1, id.y));
			std::map<std::string, Tile*>::iterator rightIt = levelTiles[level].find(Vector2ToString(id.x + 1, id.y));

			bool up = upIt != levelTiles[level].end() && tileCategory == (*upIt).second->GetTileCategory();
			bool down = downIt != levelTiles[level].end() && tileCategory == (*downIt).second->GetTileCategory();
			bool left = leftIt != levelTiles[level].end() && tileCategory == (*leftIt).second->GetTileCategory();
			bool right = rightIt != levelTiles[level].end() && tileCategory == (*rightIt).second->GetTileCategory();

			TileType tileType = (TileType)tileCategory;
			int rotation = 0;

			if (up && down && left && right)
			{
				tileType = UNDETERMINED;
			}
			else if (up && down)
			{
				tileType = (TileType)tileCategory;

				if (tileCategory != LADDER)
				{
					if (left)
					{
						rotation = 270;
					}
					else
					{
						rotation = 90;
					}
				}
			}
			else if (left && right)
			{
				tileType = (TileType)tileCategory;

				if (up)
				{
					rotation = 180;
				}
			}
			else if (up && left)
			{
				tileType = (TileType)(tileCategory + 2);
				rotation = 270;
			}
			else if (up && right)
			{
				tileType = (TileType)(tileCategory + 2);
				rotation = 180;
			}
			else if (down && right)
			{
				tileType = (TileType)(tileCategory + 2);
				rotation = 90;
			}
			else if (down && left)
			{
				tileType = (TileType)(tileCategory + 2);
			}
			else if (up || down)
			{
				if (tileCategory == LADDER)
				{
					if (up)
					{
						tileType = (TileType)(tileCategory + 1);
					}
					else if (down)
					{
						tileType = (TileType)(tileCategory - 1);
					}
				}
				else
				{
					tileType = (TileType)tileCategory;
					rotation = 90;
				}
			}


			if (tileType != UNDETERMINED)
			{
				(*it).second->Initialise(renderer, tileType, rotation);
				float x = (levelScale[level] * 8) + (id.x * levelScale[level] * 16);
				float y = (levelScale[level] * 8) + (id.y * levelScale[level] * 16);
				(*it).second->SetPosition(x, y);
				(*it).second->SetScale(levelScale[level]);
				(*it).second->SetDead(false);
			}
			else
			{
				int x = 0;
			}
		}
		
		for (it = levelTiles[level].begin(); it != levelTiles[level].end(); it++)
		{
			if ((*it).second->GetTileType() == UNDETERMINED)
			{
				Vector2 id = (*it).second->GetID();
				bool up = false;
				bool down = false;
				bool left = false;
				bool right = false;

				std::map<std::string, Tile*>::iterator upIt = levelTiles[level].find(Vector2ToString(id.x, id.y - 1));
				std::map<std::string, Tile*>::iterator downIt = levelTiles[level].find(Vector2ToString(id.x, id.y + 1));
				std::map<std::string, Tile*>::iterator leftIt = levelTiles[level].find(Vector2ToString(id.x - 1, id.y));
				std::map<std::string, Tile*>::iterator rightIt = levelTiles[level].find(Vector2ToString(id.x + 1, id.y));

				if (upIt != levelTiles[level].end())
				{
					up = (upIt->second->GetTileType() == CORNERCONVEX) || (upIt->second->GetTileType() == STRAIGHT && upIt->second->GetFacingDirection().x);
				}
				if (downIt != levelTiles[level].end())
				{
					down = (downIt->second->GetTileType() == CORNERCONVEX) || (downIt->second->GetTileType() == STRAIGHT && downIt->second->GetFacingDirection().x);
				}
				if (leftIt != levelTiles[level].end())
				{
					left = (leftIt->second->GetTileType() == CORNERCONVEX) || (leftIt->second->GetTileType() == STRAIGHT && leftIt->second->GetFacingDirection().y);
				}
				if (rightIt != levelTiles[level].end())
				{
					right = (rightIt->second->GetTileType() == CORNERCONVEX) || (rightIt->second->GetTileType() == STRAIGHT && rightIt->second->GetFacingDirection().y);
				}

				TileType tileType;
				int rotation = 0;

				if (up && left)
				{
					tileType = CORNERCONCAVE;
					rotation = 90;
				}
				else if (up && right)
				{
					tileType = CORNERCONCAVE;
				}
				else if (down && right)
				{
					tileType = CORNERCONCAVE;
					rotation = 270;
				}
				else if (down && left)
				{
					tileType = CORNERCONCAVE;
					rotation = 180;
				}
				else
				{
					tileType = MIDDLE;
				}
				(*it).second->Initialise(renderer, tileType, rotation);
				float x = (levelScale[level] * 8) + (id.x * levelScale[level] * 16);
				float y = (levelScale[level] * 8) + (id.y * levelScale[level] * 16);
				(*it).second->SetPosition(x, y);
				(*it).second->SetScale(levelScale[level]);
				(*it).second->SetDead(false);

			}
		}

		for (std::vector<InteractableButton*>::iterator itButton = buttons[level].begin(); itButton != buttons[level].end(); itButton++)
		{
			Vector2 id = (*itButton)->GetID();

			std::map<std::string, Tile*>::iterator upIt = levelTiles[level].find(Vector2ToString(id.x, id.y - 1));
			std::map<std::string, Tile*>::iterator downIt = levelTiles[level].find(Vector2ToString(id.x, id.y + 1));
			std::map<std::string, Tile*>::iterator leftIt = levelTiles[level].find(Vector2ToString(id.x - 1, id.y));
			std::map<std::string, Tile*>::iterator rightIt = levelTiles[level].find(Vector2ToString(id.x + 1, id.y));

			bool up = upIt != levelTiles[level].end() && (*upIt).second->GetTileCategory() == BLOCK;
			bool down = downIt != levelTiles[level].end() && (*downIt).second->GetTileCategory() == BLOCK;
			bool left = leftIt != levelTiles[level].end() && (*leftIt).second->GetTileCategory() == BLOCK;
			bool right = rightIt != levelTiles[level].end() && (*rightIt).second->GetTileCategory() == BLOCK;

			int rotation = 0;
			if (up)
			{
				rotation = 180;
			}
			else if (down)
			{
				rotation = 0;
			}
			else if (left)
			{
				rotation = 270;
			}
			else if (right)
			{
				rotation = 90;
			}

			(*itButton)->Initialise(renderer, rotation, levelScale[level]);
		}

		for (std::vector<interactableLever*>::iterator itLever = levers[level].begin(); itLever != levers[level].end(); itLever++)
		{
			Vector2 id = (*itLever)->GetID();

			std::map<std::string, Tile*>::iterator upIt = levelTiles[level].find(Vector2ToString(id.x, id.y - 1));
			std::map<std::string, Tile*>::iterator downIt = levelTiles[level].find(Vector2ToString(id.x, id.y + 1));
			std::map<std::string, Tile*>::iterator leftIt = levelTiles[level].find(Vector2ToString(id.x - 1, id.y));
			std::map<std::string, Tile*>::iterator rightIt = levelTiles[level].find(Vector2ToString(id.x + 1, id.y));

			bool up = upIt != levelTiles[level].end() && (*upIt).second->GetTileCategory() == BLOCK;
			bool down = downIt != levelTiles[level].end() && (*downIt).second->GetTileCategory() == BLOCK;
			bool left = leftIt != levelTiles[level].end() && (*leftIt).second->GetTileCategory() == BLOCK;
			bool right = rightIt != levelTiles[level].end() && (*rightIt).second->GetTileCategory() == BLOCK;

			int rotation = 0;
			if (up)
			{
				rotation = 180;
			}
			else if (down)
			{
				rotation = 0;
			}
			else if (left)
			{
				rotation = 270;
			}
			else if (right)
			{
				rotation = 90;
			}

			(*itLever)->Initialise(renderer, rotation, levelScale[level]);
		}

		for (std::vector<Door*>::iterator itDoor = doors[level].begin(); itDoor != doors[level].end(); itDoor++)
		{
			Vector2 id = (*itDoor)->GetID();

			std::map<std::string, Tile*>::iterator upIt = levelTiles[level].find(Vector2ToString(id.x, id.y - 1));
			std::map<std::string, Tile*>::iterator downIt = levelTiles[level].find(Vector2ToString(id.x, id.y + 1));
			std::map<std::string, Tile*>::iterator leftIt = levelTiles[level].find(Vector2ToString(id.x - 1, id.y));
			std::map<std::string, Tile*>::iterator rightIt = levelTiles[level].find(Vector2ToString(id.x + 1, id.y));

			bool up = upIt != levelTiles[level].end() && (*upIt).second->GetTileCategory() == BLOCK;
			bool down = downIt != levelTiles[level].end() && (*downIt).second->GetTileCategory() == BLOCK;
			bool left = leftIt != levelTiles[level].end() && (*leftIt).second->GetTileCategory() == BLOCK;
			bool right = rightIt != levelTiles[level].end() && (*rightIt).second->GetTileCategory() == BLOCK;

			int rotation = 0;
			if (up)
			{
				rotation = 180;
			}
			else if (down)
			{
				rotation = 0;
			}
			else if (left)
			{
				rotation = 270;
			}
			else if (right)
			{
				rotation = 90;
			}

			(*itDoor)->Initialise(renderer, rotation, levelScale[level]);
		}

		for (std::vector<Turret*>::iterator itTurret = turrets[level].begin(); itTurret != turrets[level].end(); itTurret++)
		{
			(*itTurret)->Initialise(renderer, 1, levelScale[level]);
		}

		const char* gemTypes[] = {"..\\Assets\\Objects\\Green Gem.png", "..\\Assets\\Objects\\Orange Gem.png", "..\\Assets\\Objects\\Red Gem.png", "..\\Assets\\Objects\\Blue Gem.png" };
		for (int i = 0; i < gems[level].size(); i++)
		{
			gems[level][i]->Initialise(renderer, gemTypes[i % 4], levelScale[level]);
		}

		levelDimensions[level].x = maxColumns;
		levelDimensions[level].y = currentRow;
		
		for (int x = 0; x < levelDimensions[level].x; x++)
		{
			int numChunks = 0;
			bool insideChunk = false;
			for (int y = 0; y < levelDimensions[level].y; y++)
			{
				std::map<std::string, Tile*>::iterator itTile = levelTiles[level].find(Vector2ToString(x, y));
				if (itTile != levelTiles[level].end() && (*itTile).second->GetTileCategory() == BLOCK && !insideChunk)
				{
					insideChunk = true;
					numChunks++;
				}
				else if(itTile == levelTiles[level].end() || (*itTile).second->GetTileCategory() != BLOCK)
				{
					insideChunk = false;

					Sprite* sprite;
					if (numChunks >= NUMCHUNKSHADOW)
					{
						sprite = renderer.CreateSprite("..\\Assets\\Tiles\\Dark Background.png");

					}
					else
					{
						sprite = renderer.CreateSprite("..\\Assets\\Tiles\\Light Background.png");
					}

					sprite->SetX((levelScale[level] * 8) + (x * levelScale[level] * 16));
					sprite->SetY((levelScale[level] * 8) + (y * levelScale[level] * 16));
					sprite->SetScale(levelScale[level]);
					levelBackgroundTiles[level][Vector2ToString(x, y)] = sprite;


				}

				

			}
		}
		
	}

	for (int i = 0; i < 3; i++)
	{
		grapplerStartCoordinates[i].x = (levelScale[i] * 8) + (grapplerStartCoordinates[i].x * levelScale[i] * 16);
		grapplerStartCoordinates[i].y = (levelScale[i] * 8) + (grapplerStartCoordinates[i].y * levelScale[i] * 16);
		portalGunnerStartCoordinates[i].x = (levelScale[i] * 8) + (portalGunnerStartCoordinates[i].x * levelScale[i] * 16);
		portalGunnerStartCoordinates[i].y = (levelScale[i] * 8) + (portalGunnerStartCoordinates[i].y * levelScale[i] * 16);
	}
	
	return false;
}

void
LevelManager::Process(float deltaTime, InputSystem& inputSystem, SoundManager& soundManager)
{
	for (std::map<std::string, Tile*>::iterator itLevelTiles = levelTiles[currentLevel].begin(); itLevelTiles != levelTiles[currentLevel].end(); itLevelTiles++)
	{
		(*itLevelTiles).second->Process(deltaTime);
	}
	for (std::map<std::string, Sprite*>::iterator itBackgroundTiles = levelBackgroundTiles[currentLevel].begin(); itBackgroundTiles != levelBackgroundTiles[currentLevel].end(); itBackgroundTiles++)
	{
		(*itBackgroundTiles).second->Process(deltaTime);
	}
	for (std::vector<InteractableButton*>::iterator itButton = buttons[currentLevel].begin(); itButton != buttons[currentLevel].end(); itButton++)
	{
		(*itButton)->Process(deltaTime, inputSystem);
	}
	for (std::vector<interactableLever*>::iterator itLever = levers[currentLevel].begin(); itLever != levers[currentLevel].end(); itLever++)
	{
		(*itLever)->Process(deltaTime, inputSystem);
	}
	for (std::vector<Door*>::iterator itDoor = doors[currentLevel].begin(); itDoor != doors[currentLevel].end(); itDoor++)
	{
		(*itDoor)->Process(deltaTime);
	}
	for (std::vector<Gem*>::iterator itGem = gems[currentLevel].begin(); itGem != gems[currentLevel].end(); itGem++)
	{
		(*itGem)->Process(deltaTime);
	}
	for (std::vector<Turret*>::iterator itTurret = turrets[currentLevel].begin(); itTurret != turrets[currentLevel].end(); itTurret++)
	{
		(*itTurret)->Process(deltaTime);
	}
}

void
LevelManager::Draw(Renderer& renderer)
{
	std::map<std::string, Tile*>::iterator it;
		
	for (std::map<std::string, Sprite*>::iterator itBackgroundTiles = levelBackgroundTiles[currentLevel].begin(); itBackgroundTiles != levelBackgroundTiles[currentLevel].end(); itBackgroundTiles++)
	{
		(*itBackgroundTiles).second->Draw(renderer);
	}
	for (std::vector<Door*>::iterator itDoor = doors[currentLevel].begin(); itDoor != doors[currentLevel].end(); itDoor++)
	{
		(*itDoor)->Draw(renderer);
	}
	for (it = levelTiles[currentLevel].begin(); it != levelTiles[currentLevel].end(); it++)
	{
		(*it).second->Draw(renderer);
	}
	for (std::vector<Gem*>::iterator itGem = gems[currentLevel].begin(); itGem != gems[currentLevel].end(); itGem++)
	{
		(*itGem)->Draw(renderer);
	}
	for (std::vector<InteractableButton*>::iterator itButton = buttons[currentLevel].begin(); itButton != buttons[currentLevel].end(); itButton++)
	{
		(*itButton)->Draw(renderer);
	}
	for (std::vector<interactableLever*>::iterator itLever = levers[currentLevel].begin(); itLever != levers[currentLevel].end(); itLever++)
	{
		(*itLever)->Draw(renderer);
	}
	for (std::vector<Turret*>::iterator itTurret = turrets[currentLevel].begin(); itTurret != turrets[currentLevel].end(); itTurret++)
	{
		(*itTurret)->Draw(renderer);
	}


}

int
LevelManager::CheckInput(char input)
{
	switch (input)
	{
	case '@':
		return BLOCK;
		break;
	case 'R':
		return RAIL;
		break;
	case 'A':
		return LADDER;
		break;
	}
	return -1;
}

void
LevelManager::SetLevel(int level)
{
	this->currentLevel = level;
}

int
LevelManager::GetLevel()
{
	return currentLevel;
}

int
LevelManager::GetLevelScale()
{
	return levelScale[currentLevel];
}

std::map<std::string, Tile*>
LevelManager::GetLevelTiles()
{
	return levelTiles[currentLevel];
}



std::vector<InteractableButton*>
LevelManager::GetAllButtons()
{
	return buttons[currentLevel];
}

std::vector<interactableLever*>
LevelManager::GetAllLevers()
{
	return levers[currentLevel];
}

std::vector<Door*>
LevelManager::GetAllDoors()
{
	return doors[currentLevel];
}

std::vector<Gem*>
LevelManager::GetAllGems()
{
	return gems[currentLevel];
}

Vector2
LevelManager::GetGrapplerStartLocation()
{
	return grapplerStartCoordinates[currentLevel];
}

Vector2
LevelManager::GetPortalGunnerStartLocation()
{
	return portalGunnerStartCoordinates[currentLevel];
}

void 
LevelManager::ResetAllLevels()
{
	for (int i = 0; i < 3; i++)
	{
		for (std::vector<InteractableButton*>::iterator itButtons = buttons[i].begin(); itButtons != buttons[i].end(); itButtons++)
		{
			(*itButtons)->SetPressed(false);
		}
		for (std::vector<interactableLever*>::iterator itLever = levers[i].begin(); itLever != levers[i].end(); itLever++)
		{
			(*itLever)->SetPressed(false);
		}
		for (std::vector<Gem*>::iterator itGem = gems[i].begin(); itGem != gems[i].end(); itGem++)
		{
			(*itGem)->Reset();
		}
	}
}

void
LevelManager::DebugDraw()
{
	ImGui::SliderInt("Level: ", &currentLevel, 0, 2);
}

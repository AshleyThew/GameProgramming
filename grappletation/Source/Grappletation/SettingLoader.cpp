#include "SettingLoader.h"
#include <sstream>
#include "logmanager.h"



class Level;
class Room;

SettingLoader::SettingLoader()
//: stringMap(0, 0)

{

}

SettingLoader::~SettingLoader()
{
	//need to delete all entry in map
}


bool SettingLoader::LoadSettings()
{
	std::string categoryString;
	std::string valueType;
	std::string value;
	std::string currentLine;
	
	bool keyScanned = false;


	std::ifstream infile("gamesettings.ini");

	for (currentLine; getline(infile, currentLine); )
	{
		for (int i = 0; i <= currentLine.size() - 1; i++) {
			if (currentLine.at(i) != ' ' && currentLine.at(i) != '=') {
				if (!keyScanned) {
					categoryString += currentLine.at(i);
				}
				else {
					value += currentLine.at(i);
				}
			}
			else if (currentLine.at(i) == '=') {
				keyScanned = true;
			}
		}

		
		if (value != "" && categoryString != "") {
			std::string tempString = categoryString + valueType;
			const char *temp = tempString.c_str();
			LogManager::GetInstance().Log("printing map key:");
			LogManager::GetInstance().Log(temp);
			LogManager::GetInstance().Log("printing map value:");
			LogManager::GetInstance().Log(value.c_str());

			gameSettings[categoryString] = value;

			categoryString = "";
			value = "";
			keyScanned = false;

		}
		
	}

	return false;
}

std::string SettingLoader::GetValueAsString( const std::string & key)
{
	return gameSettings[key];
}

int SettingLoader::GetValueAsInt(const std::string & key)
{
	return std::stoi(gameSettings[key]);
}

float SettingLoader::GetValueAsFloat(const std::string & key)
{
	return std::stof(gameSettings[key]);
}

bool SettingLoader::GetValueAsBoolean(const std::string & key)
{
	std::string temp = gameSettings[key];
	if (temp == "true") {
		return true;
	}
	return false;
}

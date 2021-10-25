#pragma once
// COMP710 GP Framework 2021
#ifndef __SETTINGLOADER_H__
#define __SETTINGLOADER_H__

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>


// Class declaration:
class SettingLoader
{
	// Member methods:
public:
	SettingLoader();
	virtual ~SettingLoader();

	bool LoadSettings();
	std::string GetValueAsString( const std::string& key);
	int GetValueAsInt(const std::string& key);
	float GetValueAsFloat(const std::string& key);
	bool GetValueAsBoolean(const std::string& key);

protected:

private:
	SettingLoader(const SettingLoader& iniparse);
	SettingLoader& operator=(const SettingLoader& iniparse);

	// Member data:
public:
protected:
	std::map<std::string, std::string> gameSettings;
	//int exitCounter;

private:
};
#endif // __INILOADER_H__
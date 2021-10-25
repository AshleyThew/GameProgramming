#pragma once
#include "fmod.hpp"
#include <map>
class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	void Initialise();
	FMOD_RESULT AddSound(const char* soundName, const char* soundLocation, FMOD_MODE mode);
	void Process();
	bool PlaySound(const char* sound);
protected:
private:
public:
protected:
private:
	FMOD::System* fmod;
	std::map<const char*, FMOD::Sound*> soundsList;
};


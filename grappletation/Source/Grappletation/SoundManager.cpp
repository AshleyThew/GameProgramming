#include "SoundManager.h"
#include <map>

SoundManager::SoundManager()
	: fmod{ 0 }
{

}

SoundManager::~SoundManager()
{
	std::map<const char*, FMOD::Sound*>::iterator it;

	for (it = soundsList.begin(); it != soundsList.end(); it++)
	{
		if ((*it).second)
		{
			(*it).second->release();
			(*it).second = 0;
		}
	}
}

void
SoundManager::Initialise()
{
	FMOD_RESULT result = FMOD::System_Create(&fmod);
	result = fmod->init(8, FMOD_INIT_NORMAL, 0);
	result = AddSound("Coin", "..\\Assets\\Coin.wav", FMOD_DEFAULT);
}

FMOD_RESULT
SoundManager::AddSound(const char* soundName, const char* soundLocation, FMOD_MODE mode)
{
	FMOD::Sound* sound = NULL;
	soundsList[soundName] = sound;
	return fmod->createSound(soundLocation, mode, 0, &soundsList[soundName]);
}

void
SoundManager::Process()
{
	fmod->update();
}

bool
SoundManager::PlaySound(const char* soundName)
{
	FMOD::Sound* sound = soundsList[soundName];

	if (sound)
	{
		fmod->playSound(sound, 0, false, 0);
		return true;
	}

  	return false;
}

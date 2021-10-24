// COMP710 GP Framework 2021
// This include:
#include "texturemanager.h"
// Local includes:
#include "texture.h"
#include "logmanager.h"
// Library includes:
#include <cassert>
#include <SDL.h>
TextureManager::TextureManager()
{
}
TextureManager::~TextureManager()
{
	std::map<std::string, Texture*>::iterator iter = m_pLoadedTextures.begin();
	while (iter != m_pLoadedTextures.end())
	{
		Texture* pTexture = iter->second;
		delete pTexture;
		++iter;
	}
	m_pLoadedTextures.clear();

	iter = m_pTextTextures.begin();
	while (iter != m_pTextTextures.end())
	{
		Texture* pTexture = iter->second;
		delete pTexture;
		++iter;
	}
	m_pLoadedTextures.clear();
}
bool
TextureManager::Initialise()
{
	LogManager::GetInstance().Log("TextureManager starting...");
	return true;
}
Texture*
TextureManager::GetTexture(const char* pcFilename)
{
	Texture* pTexture = 0;
	if (m_pLoadedTextures.find(pcFilename) == m_pLoadedTextures.end())
	{
		// Not already loaded... so load...
		pTexture = new Texture();
		if (!pTexture->Initialise(pcFilename))
		{
			LogManager::GetInstance().Log("Texture failed to initialise!");
			assert(0);
		}
		m_pLoadedTextures[pcFilename] = pTexture;
	}
	else
	{
		// It has already been loaded...
		pTexture = m_pLoadedTextures[pcFilename];
	}
	return pTexture;
}

Texture*
TextureManager::GetTextTexture(const char* text, int pointsize)
{
	Texture* pTexture = 0;
	if (m_pTextTextures.find(text) == m_pTextTextures.end())
	{
		// Not already loaded... so load...
		pTexture = new Texture();
		pTexture->LoadTextTexture(text, "runescape_uf.ttf", pointsize);
		m_pTextTextures[text] = pTexture;
	}
	else
	{
		// It has already been loaded...
		pTexture = m_pTextTextures[text];
	}
	return pTexture;
}
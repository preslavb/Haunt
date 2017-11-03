/*
=================
TextureManager.cpp
- CPP file for class definition - IMPLEMENTATION
- CPP file for the TextureMgr class
=================
*/
#include "TextureManager.h"
TextureManager* TextureManager::instance = NULL;

/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
TextureManager* TextureManager::getInstance()
{
	if (instance == NULL)
	{
		instance = new TextureManager();
	}
	return TextureManager::instance;
}

/*
=================
- Data constructor initializes the TextureMgr object 
- Is always called, thus ensures all TextureMgr objects are in a consistent state.
=================
*/
TextureManager::TextureManager()
{
	
}

TextureManager::TextureManager(SDL_Renderer* renderer)
{
	renderer = renderer;
}

/*
=================
- Destructor.
=================
*/
TextureManager::~TextureManager()
{
	
}

void TextureManager::initialise()
{
	// Store the textures
	for (int tCount = 0; tCount < 9; tCount++)
	{
		Texture* newTexture = this->addTexture(textureNames[tCount], texturesToUse[tCount]);
		newTexture->setIndex(tCount);
	}
}

Texture* TextureManager::addTexture(LPCSTR textureName, LPCSTR fileName)
{
	if (!getTexture(textureName))
	{
		Texture* newTexture = new Texture();
		newTexture->loadTexture(fileName, renderer);
		textureList.insert(make_pair(textureName, newTexture));

		return newTexture;
	}
}

void TextureManager::deleteTextures()
{
	for (map<LPCSTR, Texture*>::iterator textureIterator = textureList.begin(); textureIterator != textureList.end(); ++textureIterator)
	{
		delete textureIterator->second;
	}
}

Texture* TextureManager::getTexture(LPCSTR textureName)
{
	map<LPCSTR, Texture*>::iterator textureIterator = textureList.find(textureName);
	if (textureIterator != textureList.end())
	{
		return textureIterator->second;
	}
	else
	{
		return NULL;
	}
}

Texture* TextureManager::getTexture(int textureIndex)
{
	map<LPCSTR, Texture*>::iterator textureIterator = textureList.find(textureNames[textureIndex]);
	if (textureIterator != textureList.end())
	{
		return textureIterator->second;
	}
	else
	{
		return NULL;
	}
}
/*
=================
- Set the renderer.
=================
*/
void TextureManager::setRenderer(SDL_Renderer* prenderer)
{
	this->renderer = prenderer;
}
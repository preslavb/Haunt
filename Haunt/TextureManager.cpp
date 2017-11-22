/*
=================
TextureManager.cpp
- CPP file for class definition - IMPLEMENTATION
- CPP file for the TextureMgr class
=================
*/
#include "TextureManager.h"
TextureManager* TextureManager::instance = nullptr;

/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
TextureManager* TextureManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new TextureManager();
	}
	return instance;
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

TextureManager::TextureManager(SDL_Renderer* t_renderer)
{
	renderer = t_renderer;
}

/*
=================
- Destructor.
=================
*/
TextureManager::~TextureManager()
{
}

void TextureManager::Initialise()
{
	// Store the textures
	for (int tCount = 0; tCount < 9; tCount++)
	{
		Texture* newTexture = this->AddTexture(TextureNames[tCount], TexturesToUse[tCount]);
		newTexture->SetIndex(tCount);
	}
}

Texture* TextureManager::AddTexture(LPCSTR t_texture_name, const LPCSTR t_file_name)
{
	if (!GetTexture(t_texture_name))
	{
		Texture* newTexture = new Texture();
		newTexture->LoadTexture(t_file_name, renderer);
		texturesMap.insert(make_pair(t_texture_name, newTexture));

		return newTexture;
	}
	else
	{
		return nullptr;
	}
}

void TextureManager::DeleteTextures()
{
	for (map<LPCSTR, Texture*>::iterator textureIterator = texturesMap.begin(); textureIterator != texturesMap.end(); ++
	     textureIterator)
	{
		delete textureIterator->second;
	}
}

Texture* TextureManager::GetTexture(const LPCSTR textureName)
{
	const map<LPCSTR, Texture*>::iterator textureIterator = texturesMap.find(textureName);
	if (textureIterator != texturesMap.end())
	{
		return textureIterator->second;
	}
	return nullptr;
}

Texture* TextureManager::GetTexture(const int textureIndex)
{
	const map<LPCSTR, Texture*>::iterator textureIterator = texturesMap.find(TextureNames[textureIndex]);
	if (textureIterator != texturesMap.end())
	{
		return textureIterator->second;
	}
	return nullptr;
}

/*
=================
- Set the renderer.
=================
*/
void TextureManager::SetRenderer(SDL_Renderer* t_prenderer)
{
	this->renderer = t_prenderer;
}

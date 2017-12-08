/*
=================
TextureManager.cpp
- CPP file for class definition - IMPLEMENTATION
- CPP file for the TextureMgr class
=================
*/
#include "TextureManager.h"
#include <GL/freeglut_std.h>
#include <GL/glew.h>
#include "GameConstants.h"

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
	for (int tCount = 0; tCount < min(TexturesToUse.size(), TextureNames.size()); tCount++)
	{
		Texture* newTexture = this->AddTexture(TextureNames[tCount], TexturesToUse[tCount]);
	}
}

Texture* TextureManager::AddTexture(LPCSTR t_texture_name, const LPCSTR t_file_name)
{
	if (!GetTexture(t_texture_name))
	{
		Texture* newTexture = new Texture();
		newTexture->LoadTexture(t_file_name);
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
	for (map<LPCSTR, Texture*>::iterator textureIterator = texturesMap.begin(); textureIterator != texturesMap.end(); ++textureIterator)
	{
		delete textureIterator->second;
	}
}

Texture* TextureManager::GetTexture(const LPCSTR t_texture_name)
{
	const map<LPCSTR, Texture*>::iterator textureIterator = texturesMap.find(t_texture_name);
	if (textureIterator != texturesMap.end())
	{
		return textureIterator->second;
	}
	return nullptr;
}

Texture* TextureManager::GetTexture(const int t_texture_index)
{
	const map<LPCSTR, Texture*>::iterator textureIterator = texturesMap.find(TextureNames[t_texture_index]);
	if (textureIterator != texturesMap.end())
	{
		return textureIterator->second;
	}
	return nullptr;
}

void TextureManager::WriteText(string t_text, glm::vec2 t_position)
{
	glUseProgram(0);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glRasterPos2i(t_position.x / _WINDOW_WIDTH, t_position.y / _WINDOW_HEIGHT);

	//glDisable(GL_COLOR_ARRAY);
	for (int i = 0; i < t_text.length(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, t_text[i]);
	}
}
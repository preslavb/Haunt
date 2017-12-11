#ifndef _TEXTUREMANAGER_H
#define _TEXTUREMANAGER_H

#include "GameConstants.h"
#include "Texture.h"
#include <map>
#include <vector>

// Texture manager to store and reference textures used in the game
class TextureManager
{
private:
	// The instance of the singleton
	static TextureManager* instance;

	// Map of textures 
	std::map<LPCSTR, Texture*> texturesMap;

public:
	// Get the instance of the singleton
	static TextureManager* GetInstance();

	// Constructors and destructors
	TextureManager();
	~TextureManager();

	// Names of the textures, used to reference a specific texture in the texturesMap
	std::vector<LPCSTR> TextureNames;

	// The path to the actual textures
	std::vector<LPCSTR> TexturesToUse;

	// Initialise the Texture manager
	void Initialise();

	// Accessors to the Textures
	Texture* AddTexture(LPCSTR t_texture_name, LPCSTR t_file_name);
	Texture* GetTexture(LPCSTR t_texture_name);
	Texture* GetTexture(const int t_texture_index);
	void WriteText(string t_text, glm::vec2 t_position, Color t_color = Color(1.0f, 1.0f, 1.0f, 1.0f));

	// Delete all textures
	void DeleteTextures();
};
#endif

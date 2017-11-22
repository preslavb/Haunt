#ifndef _TEXTUREMANAGER_H
#define _TEXTUREMANAGER_H

#include "GameConstants.h"
#include "Texture.h"

// Texture manager to store and reference textures used in the game
class TextureManager
{
private:
	// The instance of the singleton
	static TextureManager* instance;

	// Map of textures 
	map<LPCSTR, Texture*> texturesMap;

	// The SDL Renderer which will display the textures
	SDL_Renderer* renderer;

public:
	// Get the instance of the singleton
	static TextureManager* GetInstance();

	// Constructors and destructors
	TextureManager();
	TextureManager(SDL_Renderer* t_renderer);
	~TextureManager();

	// Names of the textures, used to reference a specific texture in the texturesMap
	vector<LPCSTR> TextureNames = {
		"grass", "grassstone", "grassbare", "grassdark", "treedark", "treelight", "treescary", "treeautumn", "theBackground"
	};

	// The path to the actual textures
	vector<LPCSTR> TexturesToUse = {
		"Images\\tile1.png", "Images\\tile2.png", "Images\\tile3.png", "Images\\tile4.png", "Images\\tree1.png",
		"Images\\tree2.png", "Images\\tree3.png", "Images\\tree4.png", "Images\\theBackground.png"
	};;

	// Initialise the Texture manager
	void Initialise();

	// Accessors to the Textures
	Texture* AddTexture(LPCSTR t_texture_name, LPCSTR t_file_name);
	Texture* GetTexture(LPCSTR t_texture_name);
	Texture* GetTexture(int t_texture_index);

	// Set the renderer to render the textures
	void SetRenderer(SDL_Renderer* t_renderer);

	// Delete all textures
	void DeleteTextures();
};
#endif

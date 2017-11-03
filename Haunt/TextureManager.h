#ifndef _TEXTUREMANAGER_H
#define _TEXTUREMANAGER_H

#include "GameConstants.h"
#include "Texture.h"

class TextureManager
{
private:
	static TextureManager* instance;
	map<LPCSTR, Texture*> textureList;
	SDL_Renderer* renderer;

public:
	static TextureManager* getInstance();
	TextureManager();
	TextureManager(SDL_Renderer* renderer);
	~TextureManager();
	vector<LPCSTR> textureNames = { "grass", "grassstone", "grassbare", "grassdark", "treedark", "treelight", "treescary", "treeautumn", "theBackground" };
	vector<LPCSTR> texturesToUse = { "Images\\tile1.png", "Images\\tile2.png", "Images\\tile3.png", "Images\\tile4.png", "Images\\tree1.png", "Images\\tree2.png", "Images\\tree3.png", "Images\\tree4.png", "Images\\theBackground.png" };;
	void initialise();
	Texture* addTexture(LPCSTR textureName, LPCSTR fileName);
	Texture* getTexture(LPCSTR textureName);
	Texture* getTexture(int textureIndex);
	void setRenderer(SDL_Renderer* renderer);
	void deleteTextures();
};
#endif
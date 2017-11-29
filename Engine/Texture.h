#ifndef _TEXTURE_H
#define _TEXTURE_H
#include "GameConstants.h"
#include <GL/glew.h>
#include <SDL/SDL_image.h>
#include "Errors.h"
#include <glm/glm.hpp>

class Texture
{
private:
	SDL_Surface* sdlTextureId;
	GLuint glTextureId;

	int width;
	int height;

	int depth;
public:
	Texture();
	Texture(LPCSTR t_file_name);
	~Texture();
	bool LoadTexture(LPCSTR t_file_name);
	GLuint* GetTextureID();
	int GetTextureWidth() const;
	int GetTextureHeight() const;

	int GetDepth();
	void SetDepth(const int t_new_depth);
};
#endif

#ifndef _TEXTURE_H
#define _TEXTURE_H
#include "GameConstants.h"
#include <GL/glew.h>
#include <SDL/SDL_image.h>
#include "Errors.h"
#include <glm/glm.hpp>
#include "Vertex.h"
#include "Coroutine.h"

class Texture
{
private:
	SDL_Surface* sdlTextureId;
	GLuint glTextureId;

	Color tint;

	int width;
	int height;

	float depth;
	float order;
public:
	Texture();
	Texture(LPCSTR t_file_name);
	~Texture();
	bool LoadTexture(LPCSTR t_file_name);
	GLuint* GetTextureID();
	int GetTextureWidth() const;
	int GetTextureHeight() const;

	float GetDepth();
	float GetOrder();
	void SetDepth(const float t_new_depth, const float* t_new_order = nullptr);
};
#endif

#pragma once

#include <gl/glew.h>
#include "Vertex.h"
#include "glm/glm.hpp"
#include <vector>
#include "GameObject.h"
#include "Collider.h"
#include "UIElement.h"

enum class QuadSortType
{
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};

struct SpriteQuad
{
	GLuint Texture;
	float Depth;

	Vertex TopLeft;
	Vertex BottomLeft;
	Vertex TopRight;
	Vertex BottomRight;
};

class RenderBatch
{
public:
	RenderBatch(GLuint t_offset, GLuint t_number_of_verts, GLuint t_texture, GLfloat t_depth = 1) : Offset(t_offset), NumberOfVerts(t_number_of_verts), Texture(t_texture), Depth(t_depth)
	{
		
	}
	GLuint Offset;
	GLuint NumberOfVerts;
	GLuint Texture;
	GLfloat Depth;
};

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();

	void Initialize();

	void Begin(QuadSortType t_sort_type = QuadSortType::TEXTURE);
	void End();

	void Draw(const glm::vec4& t_dest_rect, const glm::vec4& t_uv_rect, GLuint t_texture, float t_depth, Color t_color);
	void Draw(GameObject* t_game_object, Color t_tint_to_use);
	void Draw(UIElement* t_game_object, Color t_tint_to_use);
	void Draw(Collider* t_collider, Texture* t_texture, Color t_tint_to_use);

	void RenderBatches();

private:
	void CreateRenderBatches();
	void CreateVertexArray();
	void SortQuads();

	static bool CompareFrontToBack(SpriteQuad* t_first, SpriteQuad* t_second);
	static bool CompareBackToFront(SpriteQuad* t_first, SpriteQuad* t_second);
	static bool CompareTexture(SpriteQuad* t_first, SpriteQuad* t_second);

	QuadSortType sortType;

	GLuint vertexBufferObject;
	GLuint vertexArrayObject;

	std::vector<SpriteQuad*> quads;
	std::vector<RenderBatch> renderBatches;
};


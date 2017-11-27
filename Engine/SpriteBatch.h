#pragma once

#include <gl/glew.h>
#include "Vertex.h"
#include "glm/glm.hpp"
#include <vector>

enum class GlyphSortType
{
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};

struct Glyph
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
	RenderBatch(GLuint t_offset, GLuint t_number_of_verts, GLuint t_texture) : Offset(t_offset), NumberOfVerts(t_number_of_verts), Texture(t_texture)
	{
		
	}
	GLuint Offset;
	GLuint NumberOfVerts;
	GLuint Texture;
};

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();

	void Initialize();

	void Begin(GlyphSortType t_sort_type = GlyphSortType::TEXTURE);
	void End();

	void Draw(const glm::vec4& t_dest_rect, const glm::vec4& t_uv_rect, GLuint t_texture, float t_depth, Color t_color);

	void RenderABatch();

private:
	void CreateRenderBatches();
	void CreateVertexArray();
	void SortGlyphs();

	static bool CompareFrontToBack(Glyph* t_first, Glyph* t_second);
	static bool CompareBackToFront(Glyph* t_first, Glyph* t_second);
	static bool CompareTexture(Glyph* t_first, Glyph* t_second);

	GlyphSortType sortType;

	GLuint vertexBufferObject;
	GLuint vertexArrayObject;

	std::vector<Glyph*> glyphs;
	std::vector<RenderBatch> renderBatches;
};


#pragma once

#include <gl/glew.h>
#include "Vertex.h"
#include "glm/glm.hpp"
#include <vector>
#include "GameObject.h"
#include "Collider.h"
#include "UIElement.h"

// The method to use for sorting quads
enum class QuadSortType
{
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};

// A structure for the sprite quads
struct SpriteQuad
{
	GLuint Texture;
	float Depth;

	Vertex TopLeft;
	Vertex BottomLeft;
	Vertex TopRight;
	Vertex BottomRight;
};

// A batch of vertices to render with a specific texture
class RenderBatch
{
public:
	// Constructor
	RenderBatch(GLuint t_offset, GLuint t_number_of_verts, GLuint t_texture, GLfloat t_depth = 1) : Offset(t_offset), NumberOfVerts(t_number_of_verts), Texture(t_texture), Depth(t_depth)
	{
		
	}

	// The data offset (required because of the way OpenGL stores vertices)
	GLuint Offset;
	// The number of vertices to render with the texture specified
	GLuint NumberOfVerts;
	// The GL texture to use for rendering the vertices
	GLuint Texture;
	GLfloat Depth;
};

// The render batch manager based on the XNA Framework
class SpriteBatch
{
public:
	//Constructor and Destructor
	SpriteBatch();
	~SpriteBatch();

	// Initialize the Sprite Batch object
	void Initialize();

	// Enable the drawing of quads with the given sort method
	void Begin(QuadSortType t_sort_type = QuadSortType::TEXTURE);
	// Stop the drawing of quads
	void End();

	// Draw methods for different object types
	void Draw(const glm::vec4& t_dest_rect, const glm::vec4& t_uv_rect, GLuint t_texture, float t_depth, Color t_color);
	void Draw(GameObject* t_game_object, Color t_tint_to_use);
	void Draw(UIElement* t_game_object, Color t_tint_to_use);

	// Debug drawing method for collider bounding boxes
	void Draw(Collider* t_collider, Texture* t_texture, Color t_tint_to_use);

	// Render the drawn render batches to the screen
	void RenderBatches();

private:
	// Create the render batches for drawing
	void CreateRenderBatches();
	// Create the GL array of vertices to draw to
	void CreateVertexArray();
	// Sort the quads with the given method
	void SortQuads();

	// Different sorting methods
	static bool CompareFrontToBack(SpriteQuad* t_first, SpriteQuad* t_second);
	static bool CompareBackToFront(SpriteQuad* t_first, SpriteQuad* t_second);
	static bool CompareTexture(SpriteQuad* t_first, SpriteQuad* t_second);

	// The selected sort type to use
	QuadSortType sortType;

	// The vertex storage for GL
	GLuint vertexBufferObject;
	GLuint vertexArrayObject;

	// The quads to draw
	std::vector<SpriteQuad*> quads;
	// The render batches to draw
	std::vector<RenderBatch> renderBatches;
};


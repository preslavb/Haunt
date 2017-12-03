#include "stdafx.h"
#include "SpriteBatch.h"
#include <algorithm>
#include "UIElement.h"


SpriteBatch::SpriteBatch(): sortType(QuadSortType::TEXTURE), vertexBufferObject(0), vertexArrayObject(0)
{
}


SpriteBatch::~SpriteBatch()
{
}

// Setup the SpriteBatch
void SpriteBatch::Initialize()
{
	CreateVertexArray();
}

// Set up the sort order of the quads for the frame and delete any previous quads in memory
void SpriteBatch::Begin(const QuadSortType t_sort_type)
{
	sortType = t_sort_type;
	renderBatches.clear();
	for (int i = 0; i < quads.size(); i++)
	{
		delete quads[i];
	}
	quads.clear();
}

// Signifies that the frame has been constructed. Sorts the quads for the frame using the method specified at the begining of the frame and then creates the batches of sprites to render
void SpriteBatch::End()
{
	SortQuads();
	CreateRenderBatches();
}

// Register a new quad to draw this frame, with a position, a uv, texture to use, sort depth and color tint
void SpriteBatch::Draw(const glm::vec4& t_destination_rect, const glm::vec4& t_uv_rect, const GLuint t_texture, const float t_depth, const Color t_color)
{
	SpriteQuad* quad = new SpriteQuad();
	quad->Texture = t_texture;
	quad->Depth = t_depth;

	quad->TopLeft.Color = t_color;
	quad->TopLeft.SetPosition(t_destination_rect.x, t_destination_rect.y + t_destination_rect.w);
	quad->TopLeft.SetUV(t_uv_rect.x, t_uv_rect.y + t_uv_rect.w);

	quad->BottomLeft.Color = t_color;
	quad->BottomLeft.SetPosition(t_destination_rect.x, t_destination_rect.y);
	quad->BottomLeft.SetUV(t_uv_rect.x, t_uv_rect.y);

	quad->BottomRight.Color = t_color;
	quad->BottomRight.SetPosition(t_destination_rect.x + t_destination_rect.z, t_destination_rect.y);
	quad->BottomRight.SetUV(t_uv_rect.x + t_uv_rect.z, t_uv_rect.y);

	quad->TopRight.Color = t_color;
	quad->TopRight.SetPosition(t_destination_rect.x + t_destination_rect.z, t_destination_rect.y + t_destination_rect.w);
	quad->TopRight.SetUV(t_uv_rect.x + t_uv_rect.z, t_uv_rect.y + t_uv_rect.w);

	quads.push_back(quad);

}
// Register a new quad to draw this frame at the position of the game object, using the texture and its sort depth, and optionally a tint
void SpriteBatch::Draw(GameObject* t_game_object, Color t_tint_to_use = Color(255, 255, 255, 255))
{
	SpriteQuad* quad = new SpriteQuad();
	quad->Texture = *t_game_object->GetTexture()->GetTextureID();
	quad->Depth = t_game_object->GetTexture()->GetDepth();

	glm::vec4 destinationRect = t_game_object->GetRect();
	glm::vec4 uv(0, 0, 1, 1);


	quad->TopLeft.Color = t_tint_to_use;
	quad->TopLeft.SetPosition(destinationRect.x, destinationRect.y + destinationRect.w);
	quad->TopLeft.SetUV(uv.x, uv.y + uv.w);

	quad->BottomLeft.Color = t_tint_to_use;
	quad->BottomLeft.SetPosition(destinationRect.x, destinationRect.y);
	quad->BottomLeft.SetUV(uv.x, uv.y);

	quad->BottomRight.Color = t_tint_to_use;
	quad->BottomRight.SetPosition(destinationRect.x + destinationRect.z, destinationRect.y);
	quad->BottomRight.SetUV(uv.x + uv.z, uv.y);

	quad->TopRight.Color = t_tint_to_use;
	quad->TopRight.SetPosition(destinationRect.x + destinationRect.z, destinationRect.y + destinationRect.w);
	quad->TopRight.SetUV(uv.x + uv.z, uv.y + uv.w);

	quads.push_back(quad);
}

void SpriteBatch::Draw(UIElement* t_ui_element, Color t_tint_to_use = Color(255, 255, 255, 255))
{
	SpriteQuad* quad = new SpriteQuad();
	quad->Texture = *t_ui_element->GetTexture()->GetTextureID();
	quad->Depth = t_ui_element->GetTexture()->GetDepth();

	glm::vec4 destinationRect = t_ui_element->GetRect();
	glm::vec4 uv(0, 0, 1, 1);


	quad->TopLeft.Color = t_tint_to_use;
	quad->TopLeft.SetPosition(destinationRect.x, destinationRect.y + destinationRect.w);
	quad->TopLeft.SetUV(uv.x, uv.y + uv.w);

	quad->BottomLeft.Color = t_tint_to_use;
	quad->BottomLeft.SetPosition(destinationRect.x, destinationRect.y);
	quad->BottomLeft.SetUV(uv.x, uv.y);

	quad->BottomRight.Color = t_tint_to_use;
	quad->BottomRight.SetPosition(destinationRect.x + destinationRect.z, destinationRect.y);
	quad->BottomRight.SetUV(uv.x + uv.z, uv.y);

	quad->TopRight.Color = t_tint_to_use;
	quad->TopRight.SetPosition(destinationRect.x + destinationRect.z, destinationRect.y + destinationRect.w);
	quad->TopRight.SetUV(uv.x + uv.z, uv.y + uv.w);

	quads.push_back(quad);
}

void SpriteBatch::Draw(Collider* t_collider, Texture* t_texture, Color t_tint_to_use)
{
	SpriteQuad* quad = new SpriteQuad();
	quad->Texture = *t_texture->GetTextureID();
	quad->Depth = t_texture->GetDepth();

	glm::vec4 destinationRect = glm::vec4(t_collider->GetRect().TopLeft().x, t_collider->GetRect().TopLeft().y, t_collider->GetRect().GetDimensions().x,t_collider->GetRect().GetDimensions().y);
	glm::vec4 uv(0, 0, 1, 1);


	quad->TopLeft.Color = t_tint_to_use;
	quad->TopLeft.SetPosition(destinationRect.x, destinationRect.y + destinationRect.w);
	quad->TopLeft.SetUV(uv.x, uv.y + uv.w);

	quad->BottomLeft.Color = t_tint_to_use;
	quad->BottomLeft.SetPosition(destinationRect.x, destinationRect.y);
	quad->BottomLeft.SetUV(uv.x, uv.y);

	quad->BottomRight.Color = t_tint_to_use;
	quad->BottomRight.SetPosition(destinationRect.x + destinationRect.z, destinationRect.y);
	quad->BottomRight.SetUV(uv.x + uv.z, uv.y);

	quad->TopRight.Color = t_tint_to_use;
	quad->TopRight.SetPosition(destinationRect.x + destinationRect.z, destinationRect.y + destinationRect.w);
	quad->TopRight.SetUV(uv.x + uv.z, uv.y + uv.w);

	quads.push_back(quad);
}

// Display the final batches on the screen
void SpriteBatch::RenderBatches()
{
	// Get the array of vertices created for the frame
	glBindVertexArray(vertexArrayObject);

	// Go through the batches and draw the appropriate texture for the vertices belonging to that render batch
	for (int i = 0; i < renderBatches.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, renderBatches[i].Texture);

		glDrawArrays(GL_TRIANGLES, renderBatches[i].Offset, renderBatches[i].NumberOfVerts);
	}

	// Unbind the array of vertices
	glBindVertexArray(0);
}

// Create the batches to render
void SpriteBatch::CreateRenderBatches()
{
	// Setup the vertex storage vector
	std::vector <Vertex> vertices;

	// Resize the allocated space for the vector based on the number of quads we have, multiplied by the vertices for each quad (6)
	vertices.resize(quads.size() * 6);

	// Exit the method if there is nothing to render
	if (quads.empty())
	{
		return;
	}

	// The offset for each consecutive batch (based on vertices)
	int offset = 0;

	// The index to insert the new vertex in
	int currentVert = 0;

	// Create the first batch
	renderBatches.emplace_back(offset, 6, quads[0]->Texture);
	vertices[currentVert++] = quads[0]->TopLeft;
	vertices[currentVert++] = quads[0]->BottomLeft;
	vertices[currentVert++] = quads[0]->BottomRight;
	vertices[currentVert++] = quads[0]->BottomRight;
	vertices[currentVert++] = quads[0]->TopRight;
	vertices[currentVert++] = quads[0]->TopLeft;
	offset += 6;

	// Create the other batches, melding the vertices together if the texture matches the previous frame texture
	for (int currentQuad = 1; currentQuad < quads.size(); currentQuad++)
	{
		if (quads[currentQuad]->Texture != quads[currentQuad-1]->Texture)
		{
			renderBatches.emplace_back(offset, 6, quads[currentQuad]->Texture);
		}
		else
		{
			renderBatches.back().NumberOfVerts += 6;
		}
		vertices[currentVert++] = quads[currentQuad]->TopLeft;
		vertices[currentVert++] = quads[currentQuad]->BottomLeft;
		vertices[currentVert++] = quads[currentQuad]->BottomRight;
		vertices[currentVert++] = quads[currentQuad]->BottomRight;
		vertices[currentVert++] = quads[currentQuad]->TopRight;
		vertices[currentVert++] = quads[currentQuad]->TopLeft;
		offset += 6;
	}

	// Bind the buffer of vertices to draw
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

	// Remove old pointers to the data (without deleting the data for now, as that would take time away from drawing)
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

	// Substitute the data in the buffer with the new vertices created 
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

	// Unbind the array buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Initialize the array of vertices for the renderer to use
void SpriteBatch::CreateVertexArray()
{
	// Set up the GL vertex array object
	if (vertexArrayObject == 0)
	{
		glGenVertexArrays(1, &vertexArrayObject);
	}
	glBindVertexArray(vertexArrayObject);
	
	// Set up the GL vertex buffer object
	if (vertexBufferObject == 0)
	{
		glGenBuffers(1, &vertexBufferObject);
	}
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

	// Enable the attributes of the bound vertices
	glEnableVertexAttribArray(0);

	glEnableVertexAttribArray(1);

	glEnableVertexAttribArray(2);

	// Set the vertex pointers to use in the shader to the appropriate vertex position, color and uvs
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Position));

	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, Color));

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, UVCoordinates));

	// Unbind the array
	glBindVertexArray(0);
}

// Sort the quads based on the desired sequence of rendering
void SpriteBatch::SortQuads()
{
	switch (sortType)
	{
	case QuadSortType::BACK_TO_FRONT:
		std::stable_sort(quads.begin(), quads.end(), CompareBackToFront);
		break;
	case QuadSortType::FRONT_TO_BACK:
		std::stable_sort(quads.begin(), quads.end(), CompareFrontToBack);
		break;
	case QuadSortType::TEXTURE:
		std::stable_sort(quads.begin(), quads.end(), CompareTexture);
		break;
	}
}

// Comparison methods for the stable_sort function
bool SpriteBatch::CompareFrontToBack(SpriteQuad* t_first, SpriteQuad* t_second)
{
	return (t_first->Depth < t_second->Depth);
}

bool SpriteBatch::CompareBackToFront(SpriteQuad* t_first, SpriteQuad* t_second)
{
	return (t_first->Depth > t_second->Depth);
}

bool SpriteBatch::CompareTexture(SpriteQuad* t_first, SpriteQuad* t_second)
{
	return (t_first->Texture < t_second->Texture);
}

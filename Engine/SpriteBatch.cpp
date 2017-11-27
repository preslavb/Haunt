#include "stdafx.h"
#include "SpriteBatch.h"
#include <algorithm>


SpriteBatch::SpriteBatch(): sortType(GlyphSortType::TEXTURE), vertexBufferObject(0), vertexArrayObject(0)
{
}


SpriteBatch::~SpriteBatch()
{
}

void SpriteBatch::Initialize()
{
	CreateVertexArray();
}

void SpriteBatch::Begin(const GlyphSortType t_sort_type)
{
	sortType = t_sort_type;
	renderBatches.clear();
	for (int i = 0; i < glyphs.size(); i++)
	{
		delete glyphs[i];
	}
	glyphs.clear();
}

void SpriteBatch::End()
{
	SortGlyphs();
	CreateRenderBatches();
}

void SpriteBatch::Draw(const glm::vec4& t_dest_rect, const glm::vec4& t_uv_rect, const GLuint t_texture, const float t_depth, const Color t_color)
{
	Glyph* newGlyph = new Glyph();
	newGlyph->Texture = t_texture;
	newGlyph->Depth = t_depth;

	newGlyph->TopLeft.Color = t_color;
	newGlyph->TopLeft.SetPosition(t_dest_rect.x, t_dest_rect.y + t_dest_rect.w);
	newGlyph->TopLeft.SetUV(t_uv_rect.x, t_uv_rect.y + t_uv_rect.w);

	newGlyph->BottomLeft.Color = t_color;
	newGlyph->BottomLeft.SetPosition(t_dest_rect.x, t_dest_rect.y);
	newGlyph->BottomLeft.SetUV(t_uv_rect.x, t_uv_rect.y);

	newGlyph->BottomRight.Color = t_color;
	newGlyph->BottomRight.SetPosition(t_dest_rect.x + t_dest_rect.z, t_dest_rect.y);
	newGlyph->BottomRight.SetUV(t_uv_rect.x + t_uv_rect.z, t_uv_rect.y);

	newGlyph->TopRight.Color = t_color;
	newGlyph->TopRight.SetPosition(t_dest_rect.x + t_dest_rect.z, t_dest_rect.y + t_dest_rect.w);
	newGlyph->TopRight.SetUV(t_uv_rect.x + t_uv_rect.z, t_uv_rect.y + t_uv_rect.w);

	glyphs.push_back(newGlyph);

}

void SpriteBatch::RenderABatch()
{
	glBindVertexArray(vertexArrayObject);

	for (int i = 0; i < renderBatches.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, renderBatches[i].Texture);

		glDrawArrays(GL_TRIANGLES, renderBatches[i].Offset, renderBatches[i].NumberOfVerts);
	}

	glBindVertexArray(0);
}

void SpriteBatch::CreateRenderBatches()
{
	std::vector <Vertex> vertices;

	vertices.resize(glyphs.size() * 6);

	if (glyphs.empty())
	{
		return;
	}

	int offset = 0;

	int currentVert = 0;
	renderBatches.emplace_back(0, 6, glyphs[0]->Texture);
	vertices[currentVert++] = glyphs[0]->TopLeft;
	vertices[currentVert++] = glyphs[0]->BottomLeft;
	vertices[currentVert++] = glyphs[0]->BottomRight;
	vertices[currentVert++] = glyphs[0]->BottomRight;
	vertices[currentVert++] = glyphs[0]->TopRight;
	vertices[currentVert] = glyphs[0]->TopLeft;
	offset += 6;

	for (int currentGlyph = 1; currentGlyph < glyphs.size(); currentGlyph++)
	{
		if (glyphs[currentGlyph]->Texture != glyphs[currentGlyph-1]->Texture)
		{
			renderBatches.emplace_back(0, 6, glyphs[0]->Texture);
		}
		else
		{
			renderBatches.back().NumberOfVerts += 6;
		}
		vertices[currentVert++] = glyphs[currentGlyph]->TopLeft;
		vertices[currentVert++] = glyphs[currentGlyph]->BottomLeft;
		vertices[currentVert++] = glyphs[currentGlyph]->BottomRight;
		vertices[currentVert++] = glyphs[currentGlyph]->BottomRight;
		vertices[currentVert++] = glyphs[currentGlyph]->TopRight;
		vertices[currentVert++] = glyphs[currentGlyph]->TopLeft;
		offset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

	// Orphan the buffer
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::CreateVertexArray()
{
	if (vertexArrayObject == 0)
	{
		glGenVertexArrays(1, &vertexArrayObject);
	}
	glBindVertexArray(vertexArrayObject);
	
	if (vertexBufferObject == 0)
	{
		glGenBuffers(1, &vertexBufferObject);
	}
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

	glEnableVertexAttribArray(0);

	glEnableVertexAttribArray(1);

	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Position));

	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, Color));

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, UVCoordinates));

	glBindVertexArray(0);
}

void SpriteBatch::SortGlyphs()
{
	switch (sortType)
	{
	case GlyphSortType::BACK_TO_FRONT:
		std::stable_sort(glyphs.begin(), glyphs.end(), CompareBackToFront);
		break;
	case GlyphSortType::FRONT_TO_BACK:
		std::stable_sort(glyphs.begin(), glyphs.end(), CompareFrontToBack);
		break;
	case GlyphSortType::TEXTURE:
		std::stable_sort(glyphs.begin(), glyphs.end(), CompareTexture);
		break;
	}
}

bool SpriteBatch::CompareFrontToBack(Glyph* t_first, Glyph* t_second)
{
	return (t_first->Depth < t_second->Depth);
}

bool SpriteBatch::CompareBackToFront(Glyph* t_first, Glyph* t_second)
{
	return (t_first->Depth > t_second->Depth);
}

bool SpriteBatch::CompareTexture(Glyph* t_first, Glyph* t_second)
{
	return (t_first->Texture < t_second->Texture);
}

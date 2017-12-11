#pragma once

#include <glm/glm.hpp>
#include "Texture.h"
#include "Camera2D.h"

class SpriteBatch;

// Any UI Element present in the game
[event_receiver(native)][event_source(native)]
class UIElement
{
protected:
	static int uiElementsInitialized;

	bool isFading = false;

	// The position of the UI Element represented by a Vector2D
	glm::vec2 position;
	// The scale of the UI Element represented by a Vector2D
	glm::vec2 scale;
	// The rotation of the UI Element represented by a double in radians
	double rotation;
	// The texture that represents this UI Element in the scene
	Texture* texture;

	glm::vec2 dimensions;
	Color tint = Color(255, 255, 255, 255);

	Coroutine<bool>* fadeOutCoroutine;
	Coroutine<bool> FadeOutCoroutine(float t_seconds);
public:
	Uint16 id;

	float FadeSeconds = 2;

	// Constructors
	UIElement(Texture* t_texture_to_use);
	UIElement(Texture* t_texture_to_use, glm::vec2 t_new_position);
	UIElement(Texture* t_texture_to_use, glm::vec2 t_new_position, int t_new_depth);
	UIElement(Texture* t_texture_to_use, glm::vec2 t_new_position, float t_new_rotation);
	UIElement(Texture* t_texture_to_use, glm::vec2 t_new_position, glm::vec2 t_new_dimensions);
	UIElement(Texture* t_texture_to_use, glm::vec2 t_new_position, glm::vec2 t_new_scale, float t_new_rotation);
	virtual ~UIElement();
	void HookInputs();

	// Accessors for the position, rotation and scale of the UI Element
	void SetPosition(glm::vec2 t_new_position);
	void SetRotation(float t_new_rotation);
	void SetScale(glm::vec2 t_new_scale);
	glm::vec2 GetPosition() const;
	double GetRotation() const;
	glm::vec2 GetScale() const;
	Texture* GetTexture() const;
	glm::vec4 GetRect() const;

	Color GetTint();

	void FadeOut(float t_seconds);

	// Update logic for any UI Element in the game
	virtual void Update();

	// Update logic for any UI Element in the game that is based on time passage
	virtual void Update(float t_delta_time);

	__event void WasDestroyed(UIElement* t_element_destroyed);
};

inline std::ostream & operator<<(std::ostream & t_string, UIElement const & t_object)
{
	t_string << t_object.id;
	return t_string;
}

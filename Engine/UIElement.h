#pragma once

#include <glm/glm.hpp>
#include "Texture.h"
#include "Camera2D.h"

// Forward declaration of the sprite batch class
class SpriteBatch;

// Any UI Element present in the game
[event_receiver(native)][event_source(native)]
class UIElement
{
protected:
	// The number of UI elements initialized to this point
	static int uiElementsInitialized;

	// Is the UI element currently fading out
	bool isFading = false;

	// The position of the UI Element represented by a Vector2D
	glm::vec2 position;
	// The scale of the UI Element represented by a Vector2D
	glm::vec2 scale;
	// The rotation of the UI Element represented by a double in radians
	double rotation;
	// The texture that represents this UI Element in the scene
	Texture* texture;

	// The dimensions of the UI element
	glm::vec2 dimensions;
	// The tint to use when displaying the element
	Color tint = Color(255, 255, 255, 255);

	// The fade coroutines
	Coroutine<bool>* fadeCoroutine;
	Coroutine<bool> FadeOutCoroutine(float t_seconds);

	// Not used
	Coroutine<bool> FadeInCoroutine();
public:
	// The id of the UI object based on how many UI elements have been initialized
	Uint16 id;

	// How fast the fede in and out should happen
	float FadeSeconds = 2;

	// Constructors and destructors
	UIElement(Texture* t_texture_to_use, bool t_fade_out);
	UIElement(Texture* t_texture_to_use, glm::vec2 t_new_position, bool t_fade_out);
	UIElement(Texture* t_texture_to_use, glm::vec2 t_new_position, int t_new_depth, bool t_fade_out);
	UIElement(Texture* t_texture_to_use, glm::vec2 t_new_position, float t_new_rotation, bool t_fade_out);
	UIElement(Texture* t_texture_to_use, glm::vec2 t_new_position, glm::vec2 t_new_dimensions, bool t_fade_out);
	UIElement(Texture* t_texture_to_use, glm::vec2 t_new_position, glm::vec2 t_new_scale, float t_new_rotation, bool t_fade_out);
	virtual ~UIElement();

	// Event hook for elements that are fade out enabled (fade out when a movement button is pressed)
	void HookFadeOutInputs();

	// Accessors for the position, rotation and scale of the UI Element
	void SetPosition(glm::vec2 t_new_position);
	void SetRotation(float t_new_rotation);
	void SetScale(glm::vec2 t_new_scale);
	glm::vec2 GetPosition() const;
	double GetRotation() const;
	glm::vec2 GetScale() const;
	Texture* GetTexture() const;
	glm::vec4 GetRect() const;

	// Accessor for the color tint
	Color GetTint() const;

	// Functions for firing the coroutines
	void FadeOut(float t_seconds);
	void FadeIn(float t_seconds);

	// Update logic for any UI Element in the game
	virtual void Update();

	// Update logic for any UI Element in the game that is based on time passage
	virtual void Update(float t_delta_time);

	// Event to fire when the UI element was destroyed (used in the game class)
	__event void WasDestroyed(UIElement* t_element_destroyed);
};

// Function for displaying information in couts 
inline std::ostream & operator<<(std::ostream & t_string, UIElement const & t_object)
{
	t_string << t_object.id;
	return t_string;
}

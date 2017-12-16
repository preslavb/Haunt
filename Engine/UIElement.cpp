#include "UIElement.h"
#include "Rect.h"
#include "CoroutineManager.h"
#include "KeyState.h"
#include "InputHandler.h"

// Initialize the count of initialized elements to 0
int UIElement::uiElementsInitialized = 0;

// When constructing, hook the input and increase the elements initialized count by 1
UIElement::UIElement(Texture* t_texture_to_use, bool t_fade_out) : rotation(0), texture(t_texture_to_use), id(uiElementsInitialized), dimensions(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight())
{
	t_fade_out ? HookFadeOutInputs() : nullptr;
	uiElementsInitialized++;
}

UIElement::UIElement(Texture* t_texture_to_use, glm::vec2 t_new_position, bool t_fade_out) : rotation(0), texture(t_texture_to_use), id(uiElementsInitialized), position(t_new_position), dimensions(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight())
{
	t_fade_out ? HookFadeOutInputs() : nullptr;
	uiElementsInitialized++;
}

UIElement::UIElement(Texture* t_texture_to_use, glm::vec2 t_new_position, glm::vec2 t_new_dimensions, bool t_fade_out) : rotation(0), texture(t_texture_to_use), id(uiElementsInitialized), position(t_new_position), dimensions(t_new_dimensions)
{
	t_fade_out ? HookFadeOutInputs() : nullptr;
	uiElementsInitialized++;
}

UIElement::UIElement(Texture* t_texture_to_use, glm::vec2 t_new_position, int t_new_depth, bool t_fade_out) : rotation(0), texture(t_texture_to_use), id(uiElementsInitialized), position(t_new_position), dimensions(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight())
{
	t_fade_out ? HookFadeOutInputs() : nullptr;
	uiElementsInitialized++;
}

UIElement::UIElement(Texture* t_texture_to_use, glm::vec2 t_new_position, float t_new_rotation, bool t_fade_out) : rotation(t_new_rotation), texture(t_texture_to_use), id(uiElementsInitialized), position(t_new_position), dimensions(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight())
{
	t_fade_out ? HookFadeOutInputs() : nullptr;
	uiElementsInitialized++;
}

UIElement::UIElement(Texture* t_texture_to_use, glm::vec2 t_new_position, glm::vec2 t_new_scale, float t_new_rotation, bool t_fade_out) : rotation(t_new_rotation), texture(t_texture_to_use), id(uiElementsInitialized), position(t_new_position), scale(t_new_scale), dimensions(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight())
{
	t_fade_out ? HookFadeOutInputs() : nullptr;
	uiElementsInitialized++;
}

// When the object is being destroyed, first make sure the coroutine is removed from the coroutine manager, so no inaccessible memory errors happen
UIElement::~UIElement()
{
	CoroutineManager<bool>::GetInstance()->StopCoroutine(fadeCoroutine);
}

void UIElement::HookFadeOutInputs()
{
	// The hooks for the movement keys
	__hook(&KeyState::OnKeyPressed, InputHandler::GetInstance()->GetKeyStateClass(SDLK_RIGHT), &UIElement::FadeOut);
	__hook(&KeyState::OnKeyPressed, InputHandler::GetInstance()->GetKeyStateClass(SDLK_LEFT), &UIElement::FadeOut);
	__hook(&KeyState::OnKeyPressed, InputHandler::GetInstance()->GetKeyStateClass(SDLK_UP), &UIElement::FadeOut);
	__hook(&KeyState::OnKeyPressed, InputHandler::GetInstance()->GetKeyStateClass(SDLK_DOWN), &UIElement::FadeOut);
}

void UIElement::SetPosition(glm::vec2 t_new_position)
{
	position = t_new_position;
}

void UIElement::SetRotation(float t_new_rotation)
{
	rotation = t_new_rotation;
}

void UIElement::SetScale(glm::vec2 t_new_scale)
{
	scale = t_new_scale;
}

glm::vec2 UIElement::GetPosition() const
{
	return position;
}

double UIElement::GetRotation() const
{
	return rotation;
}

glm::vec2 UIElement::GetScale() const
{
	return scale;
}

Texture* UIElement::GetTexture() const
{
	return texture;
}

glm::vec4 UIElement::GetRect() const
{
	return glm::vec4(position.x, position.y, dimensions.x, dimensions.y);
}

Color UIElement::GetTint() const
{
	return tint;
}

void UIElement::FadeOut(float t_delta_time)
{
	// IF the element has not yet started fading out, start the fade out coroutine
	if (!isFading)
	{
		isFading = true;
		fadeCoroutine = CoroutineManager<bool>::GetInstance()->StartCoroutine(FadeOutCoroutine(t_delta_time));
	}
}

void UIElement::FadeIn(float t_delta_time)
{
	// IF the element has not yet started fading out, start the fade out coroutine
	if (!isFading)
	{
		isFading = true;
		fadeCoroutine = CoroutineManager<bool>::GetInstance()->StartCoroutine(FadeInCoroutine());
	}
}

// Unused as of yet
void UIElement::Update()
{
}
void UIElement::Update(float t_delta_time)
{
}

Coroutine<bool> UIElement::FadeOutCoroutine(float t_delta_time)
{
	// Store the fade seconds as a local variable
	float secondsLeft = FadeSeconds;

	// If there is still time until the element is completely faded, execute
	while (secondsLeft >= 0)
	{
		// Set the transparancy tint to a proportional value of the seconds left over the seconds meant to wait
		tint.A = (secondsLeft / FadeSeconds) * 255;

		// Suspend the function until next frame
		co_yield false;

		// Calculate how many seconds are left for the execution based on delta time
		secondsLeft -= t_delta_time;
	}

	// Call any functions subscribed to the destruction of the UI element
	__raise WasDestroyed(this);

	// The function is complete so exit out of the coroutine
	co_return true;
}

// Not currently functional
Coroutine<bool> UIElement::FadeInCoroutine()
{
	float secondsLeft = FadeSeconds;

	while (secondsLeft > 0)
	{
		std::clock_t begin = SDL_GetTicks();

		tint.A = ((FadeSeconds - secondsLeft) / FadeSeconds) * 255;
		co_yield false;

		std::clock_t end = SDL_GetTicks();

		secondsLeft -= (end - begin)/1000;
	}

	co_return true;
}

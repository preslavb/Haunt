#include "UIElement.h"
#include "Rect.h"
#include "GarbageDestroyer.h"
#include "CoroutineManager.h"
#include "KeyState.h"
#include "InputHandler.h"

int UIElement::uiElementsInitialized = 0;

UIElement::UIElement(Texture* t_texture_to_use) : rotation(0), texture(t_texture_to_use), id(uiElementsInitialized), dimensions(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight())
{
	HookInputs();
	uiElementsInitialized++;
}

UIElement::UIElement(Texture* t_texture_to_use, glm::vec2 t_new_position) : rotation(0), texture(t_texture_to_use), id(uiElementsInitialized), position(t_new_position), dimensions(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight())
{
	HookInputs();
	uiElementsInitialized++;
}

UIElement::UIElement(Texture* t_texture_to_use, glm::vec2 t_new_position, glm::vec2 t_new_dimensions) : rotation(0), texture(t_texture_to_use), id(uiElementsInitialized), position(t_new_position), dimensions(t_new_dimensions)
{
	HookInputs();
	uiElementsInitialized++;
}

UIElement::UIElement(Texture* t_texture_to_use, glm::vec2 t_new_position, int t_new_depth) : rotation(0), texture(t_texture_to_use), id(uiElementsInitialized), position(t_new_position), dimensions(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight())
{
	HookInputs();
	texture->SetDepth(t_new_depth);
	uiElementsInitialized++;
}

UIElement::UIElement(Texture* t_texture_to_use, glm::vec2 t_new_position, float t_new_rotation) : rotation(t_new_rotation), texture(t_texture_to_use), id(uiElementsInitialized), position(t_new_position), dimensions(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight())
{
	HookInputs();
	uiElementsInitialized++;
}

UIElement::UIElement(Texture* t_texture_to_use, glm::vec2 t_new_position, glm::vec2 t_new_scale, float t_new_rotation) : rotation(t_new_rotation), texture(t_texture_to_use), id(uiElementsInitialized), position(t_new_position), scale(t_new_scale), dimensions(t_texture_to_use->GetTextureWidth(), t_texture_to_use->GetTextureHeight())
{
	HookInputs();
	uiElementsInitialized++;
}

UIElement::~UIElement()
{
}

void UIElement::HookInputs()
{
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

Color UIElement::GetTint()
{
	return tint;
}

void UIElement::FadeOut(float t_delta_time)
{
	if (!isFading)
	{
		isFading = true;
		CoroutineManager<bool>::GetInstance()->StartCoroutine(FadeOutCoroutine(t_delta_time));
	}
}

void UIElement::Update()
{
}

void UIElement::Update(float t_delta_time)
{
}

Coroutine<bool> UIElement::FadeOutCoroutine(float t_delta_time)
{
	float secondsLeft = FadeSeconds;

	while (secondsLeft > 0)
	{
		//std::clock_t begin = clock();

		tint.A = (secondsLeft / FadeSeconds) * 255;
		co_yield false;

		//std::clock_t end = clock();

		secondsLeft -= t_delta_time;
	}
	__raise WasDestroyed(this);

	co_return true;
}

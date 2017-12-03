#include "Camera2D.h"
#include <iostream>
#include <SDL/SDL.h>
#include "InputHandler.h"

Camera2D* Camera2D::mainCamera = nullptr;

Camera2D::Camera2D() : scale(1), updateMatrix(true), cameraMatrix(1.0f), orthographicMatrix(1.0f), screenWidth(500),
					   screenHeight(500)
{
	if (!mainCamera)
	{
		mainCamera = this;
	}
}

Camera2D::~Camera2D()
{
}

void Camera2D::Focus(glm::vec2 t_focus_position)
{
	SetPosition(t_focus_position - glm::vec2(screenWidth / 2, screenHeight / 2));
}

void Camera2D::Initialize(int t_new_width, int t_new_height)
{
	screenWidth = t_new_width;
	screenHeight = t_new_height;
	orthographicMatrix = glm::ortho(0.0f, static_cast<float>(screenWidth), 0.0f, static_cast<float>(screenHeight));

	updateMatrix = true;
}

void Camera2D::Update()
{
	if (updateMatrix)
	{
		const glm::vec3 newTranslation(-position.x, -position.y, 0.0f);
		cameraMatrix = glm::translate(orthographicMatrix, newTranslation);

		const glm::vec3 newScale(scale, scale, 0.0f);
		cameraMatrix = glm::scale(cameraMatrix, newScale);

		updateMatrix = false;
	}
}

Camera2D* Camera2D::GetMainCamera()
{
	return mainCamera;
}

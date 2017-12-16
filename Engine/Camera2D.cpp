#include "Camera2D.h"
#include <iostream>
#include <SDL/SDL.h>
#include "InputHandler.h"

// Initialize the main camera pointer to a null pointer
Camera2D* Camera2D::mainCamera = nullptr;

// Default constructor for a camera
Camera2D::Camera2D() : scale(1), updateMatrix(true), cameraMatrix(1.0f), orthographicMatrix(1.0f), screenWidth(500),
					   screenHeight(500)
{
	// If this is the first camera initialized in the level, treat it as the main camera until specified otherwise
	if (!mainCamera)
	{
		mainCamera = this;
	}
}

// Camera destructor
Camera2D::~Camera2D()
{
}

void Camera2D::Focus(glm::vec2 t_focus_position)
{
	// Set the position of the camera so that the middle of the screen is the focus position specified
	SetPosition(t_focus_position - glm::vec2(screenWidth / 2, screenHeight / 2));
}

void Camera2D::Initialize(int t_new_width, int t_new_height)
{
	// Store the new dimensions
	screenWidth = t_new_width;
	screenHeight = t_new_height;

	// Set the orthographic matrix for the screen
	orthographicMatrix = glm::ortho(0.0f, static_cast<float>(screenWidth), 0.0f, static_cast<float>(screenHeight));

	// Update the view matrix next frame
	updateMatrix = true;
}

void Camera2D::Update()
{
	// If the view matrix needs to be recalculated, recalculate and scale it appropriately
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
	// Return the pointer to the main camera
	return mainCamera;
}

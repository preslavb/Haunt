#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

// Class for a camera that renders a 2D image based on world coordinates
[event_receiver(native)]
class Camera2D
{
public:
	// Constructor and destructor
	Camera2D();
	~Camera2D();

	// Set the position of the camera (based on the middle of the screen) and update the transformation matrix
	void SetPosition(const glm::vec2& t_new_position)
	{
		position = t_new_position - glm::vec2(screenWidth/2, screenHeight/2);
		updateMatrix = true;
	}

	// Set the scale (zoom level) of the camera and update the transformation matrix
	void SetScale(const float t_new_scale)
	{
		scale = t_new_scale;
		updateMatrix = true;
	}

	// Get the current position of the camera (the middle of the camera)
	glm::vec2 GetPosition() const
	{
		return position + glm::vec2(screenWidth/2, screenHeight/2);
	}

	// Return the scale of the camera
	float GetScale() const
	{
		return scale;
	}

	// Get the dimensions of the screen that the camera is rendering to
	glm::vec2 Camera2D::GetScreenDimensions() const
	{
		return glm::vec2(screenWidth, screenHeight);
	}

	// Get the camera transform matrix
	glm::mat4 GetCameraMatrix() const
	{
		return cameraMatrix;
	}

	// Get the generic orthographic matrix
	glm::mat4 GetOrthoMatrix() const
	{
		return orthographicMatrix;
	}

	// Move the camera and update the transformation matrix
	void MoveUp()
	{
		position.y += 1;
		updateMatrix = true;
	}

	void MoveDown()
	{
		position.y -= 1;
		updateMatrix = true;
	}

	void MoveLeft()
	{
		position.x -= 1;
		updateMatrix = true;
	}

	void MoveRight()
	{
		position.x += 1;
		updateMatrix = true;
	}

	// Focus the camera on a position on the screen
	void Focus(glm::vec2 t_focus_position);

	// Initialize the camera
	void Initialize(int t_new_width, int t_new_height);
	// Update logic for the camera (and the transformation matrix)
	void Update();
	static Camera2D* GetMainCamera();
private:
	// The zoom level of the camera
	float scale;

	// Whether to update the matrix this frame
	bool updateMatrix;

	// The position of the camera in world coords
	glm::vec2 position;

	// The view matrix of the camera
	glm::mat4 cameraMatrix;

	// The orthographic projection of the screen
	glm::mat4 orthographicMatrix;

	// The screen dimensions
	int screenWidth;
	int screenHeight;

	// A reference to the main camera in the game
	static Camera2D* mainCamera;
};

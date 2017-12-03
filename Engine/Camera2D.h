#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

[event_receiver(native)]
class Camera2D
{
public:
	Camera2D();
	~Camera2D();

	void SetPosition(const glm::vec2& t_new_position)
	{
		position = t_new_position - glm::vec2(screenWidth/2, screenHeight/2);
		updateMatrix = true;
	}

	void SetScale(const float t_new_scale)
	{
		scale = t_new_scale;
		updateMatrix = true;
	}

	glm::vec2 GetPosition() const
	{
		return position + glm::vec2(screenWidth/2, screenHeight/2);
	}

	float GetScale() const
	{
		return scale;
	}

	glm::vec2 Camera2D::GetScreenDimensions() const
	{
		return glm::vec2(screenWidth, screenHeight);
	}

	glm::mat4 GetCameraMatrix() const
	{
		return cameraMatrix;
	}

	glm::mat4 GetOrthoMatrix() const
	{
		return orthographicMatrix;
	}

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

	void Focus(glm::vec2 t_focus_position);

	void Initialize(int t_new_width, int t_new_height);
	void Update();
	static Camera2D* GetMainCamera();
private:
	float scale;
	bool updateMatrix;
	glm::vec2 position;
	glm::mat4 cameraMatrix;
	glm::mat4 orthographicMatrix;

	int screenWidth;
	int screenHeight;

	static Camera2D* mainCamera;
};

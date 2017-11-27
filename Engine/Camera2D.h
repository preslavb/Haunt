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
		position = t_new_position;
		updateMatrix = true;
	}

	void SetScale(const float t_new_scale)
	{
		scale = t_new_scale;
		updateMatrix = true;
	}

	glm::vec2 GetPosition() const
	{
		return position;
	}

	float GetScale() const
	{
		return scale;
	}

	glm::mat4 GetCameraMatrix() const
	{
		return cameraMatrix;
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

	void Initialize(int t_new_width, int t_new_height);
	void Update();
private:
	float scale;
	bool updateMatrix;
	glm::vec2 position;
	glm::mat4 cameraMatrix;
	glm::mat4 orthographicMatrix;

	int screenWidth;
	int screenHeight;
};

#include "Camera.h"

Camera::Camera(glm::vec3 postion,glm::vec3 target,glm::vec3 wordup)
{
	Position = postion;
	WorldUp = wordup;
	Forward = glm::normalize(target - postion);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));
}

Camera::Camera(glm::vec3 postion, float pitch, float yaw, glm::vec3 wordup)
{
	Position = postion;
	WorldUp = wordup;
	Pitch = pitch;
	Yaw = yaw;
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));
}

glm::mat4 Camera::GetViewMatrix()
{
	//相机位置/观看位置/世界的上方向
	return glm::lookAt(Position,Position + Forward,WorldUp);
}

Camera::~Camera()
{
}

void Camera::ProcessMouseMovement(float offsetX, float offsetY)
{
	Pitch += offsetY*0.01;
	Pitch = Pitch > 89.0f ? 89.0f : Pitch;
	Yaw += offsetX*0.01;
	Yaw = Yaw > 89.0f ? 89.0f : Yaw;
	UpdateCameraVectors();
}

void Camera::UpdateCameraPos()
{
	Position += Forward * speedZ * 0.01f;
}

void Camera::UpdateCameraVectors()
{
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));
}

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
	Forward.x = glm::cos(pitch) * glm::sin(yaw);
	Forward.y = glm::sin(pitch);
	Forward.z = glm::cos(pitch) * glm::cos(yaw);
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

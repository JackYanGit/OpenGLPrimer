#pragma once
//包含OpenGL数学运算库
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera
{
public:
	//参数相机位置/观察目标位置/世界的上方向
	Camera(glm::vec3 postion, glm::vec3 target, glm::vec3 wordup);
	Camera(glm::vec3 postion, float pitch,float yaw, glm::vec3 wordup);
	glm::mat4 GetViewMatrix();
	~Camera();
	float speedZ = .0f;
	void ProcessMouseMovement(float offsetX, float offsetY);
	void UpdateCameraPos();
private:
	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;
	float Pitch;
	float Yaw;

	void UpdateCameraVectors();
};


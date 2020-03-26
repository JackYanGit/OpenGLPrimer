#pragma once
//����OpenGL��ѧ�����
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera
{
public:
	//�������λ��/�۲�Ŀ��λ��/������Ϸ���
	Camera(glm::vec3 postion, glm::vec3 target, glm::vec3 wordup);
	Camera(glm::vec3 postion, float pitch,float yaw, glm::vec3 wordup);
	glm::mat4 GetViewMatrix();
	~Camera();
private:
	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;


};


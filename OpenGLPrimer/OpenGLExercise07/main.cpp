#define GLEW_STATIC           ////////////////////5
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
//����OpenGL��ѧ�����
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//VBO����
float vertices[] = {
	//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
};
//EBO����
unsigned int indices[] = {
	0,1,2,
	2,3,0
};
//������ƺ�������
void processInput(GLFWwindow* window);
int main() {
	//��ʼ��
	glfwInit();
	//���ð汾3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//��������
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//��������
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL ����任λ����ת����", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//�󶨴��ڵ���ǰ�߳�
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return -1;
	}
	//���û�ͼ����
	glViewport(0, 0, 800, 600);
	//���ñ����޳� ��ʱ�����Ϊ����
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	//����ֻ��������
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	Shader* pshader = new Shader("vertextSource.txt", "fragmentSource.txt");
	pshader->print();
	//��layout(location=0)�� lacation ������λ��һ����0-15��
	//λ������
	glVertexAttribPointer(15, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(15);
	//��ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//uv����
	glVertexAttribPointer(7, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(7);


	stbi_set_flip_vertically_on_load(true);
	unsigned int TexBufferA;
	glGenTextures(1, &TexBufferA);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TexBufferA);
	int width, height, numChannel;
	unsigned char* data = stbi_load("box.jpg", &width, &height, &numChannel, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else{
		std::cout << "load image failed0." << std::endl;
	}
	stbi_image_free(data);

	unsigned int TexBufferB;
	glGenTextures(1, &TexBufferB);
	glActiveTexture(GL_TEXTURE13);
	glBindTexture(GL_TEXTURE_2D, TexBufferB);
	unsigned char* data2 = stbi_load("awesomeface.png", &width, &height, &numChannel, 0);
	if (data2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "load image failed13." << std::endl;
	}
	stbi_image_free(data2);

	glm::mat4 trans;
	//λ�ƾ���
	//trans = glm::translate(trans, glm::vec3(-1.0, 0, 0));
	//��ת����
	//trans = glm::rotate(trans, glm::radians(45.0f),glm::vec3(0,0,1.0f));
	//���ž���
	//trans = glm::scale(trans, glm::vec3(2.0f, 2.0f, 2.0f));
	while (!glfwWindowShouldClose(window))
	{
		trans = glm::translate(trans, glm::vec3(-0.001, 0, 0));
		trans = glm::rotate(trans, glm::radians((float)glfwGetTime()), glm::vec3(0, 0, 1.0f));
		trans = glm::scale(trans, glm::vec3(1.0001f, 1.0001f, 1.0001f));
		processInput(window);
		glfwPollEvents();
		glClearColor(0.5, 0.2, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		//EBO���Ʒ�ʽ��ͨ��EBOȡVBO������
		
		
		glBindVertexArray(VAO);
		pshader->use();
		//uniform����texture��ͼ����
		glUniform1i(glGetUniformLocation(pshader->ID, "ourTextrue"), 0);
		glUniform1i(glGetUniformLocation(pshader->ID, "ourFace"), 13);
		//uniform������תλ�Ƶȱ任�������
		glUniformMatrix4fv(glGetUniformLocation(pshader->ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

	}
	//��������
	glfwTerminate();
	return 0;
}
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
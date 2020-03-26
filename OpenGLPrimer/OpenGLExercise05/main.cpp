#define GLEW_STATIC           ////////////////////5
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
//VBO�����������ߵ���������Ҫ������
float vertices[] = {
	//��һ��������
	-0.5f, -0.5f, 0.0f,	1.0f, 0.0f, 0.0f,		   //0
	 0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,		   //1
	 0.0f,  0.5f, 0.0f,	0.0f, 0.0f, 1.0f,		   //2
	 //�ڶ���������				 
	 //0.5f, -0.5f, 0.0f,		 
	 //0.0f,  0.5f, 0.0f,		 
	 0.8f,  0.8f, 0.0f, 0.5f, 0.8f, 0.3f		   //3
};
//EBO�����������ߵ�������ֻ��Ҫ�ĸ���
unsigned int indices[] = {
	0,1,3,
	1,2,3
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
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL ����ɫ", NULL, NULL);
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
	glVertexAttribPointer(15, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(15);
	//��ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glfwPollEvents();
		glClearColor(0.5, 0.2, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		//EBO���Ʒ�ʽ��ͨ��EBOȡVBO������
		glBindVertexArray(VAO);
		pshader->use();
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
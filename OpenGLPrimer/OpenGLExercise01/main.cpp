#define GLEW_STATIC                  ////////////////////1
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
//VBO绘制两个共边的三角形需要六个点
float vertices[] = {
	//第一个三角形
	-0.5f, -0.5f, 0.0f,			   //0
	 0.5f, -0.5f, 0.0f,			   //1
	 0.0f,  0.5f, 0.0f,			   //2
	 //第二个三角形				 
	 0.5f, -0.5f, 0.0f,		 
	 0.0f,  0.5f, 0.0f,		 
	 0.8f,  0.8f, 0.0f			   
};


const char* vertexShaderSource = 
"#version 330 core \n"
"layout(location=0) in vec3 aPos; \n"
"void main(){ \n"
"gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);}\n";
const char* fragmentShaderSource =
"#version 330 core							   "
"out vec4 FragColor;						   "
"											   "
"void main()								   "
"{											   "
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);  "
"}											   ";
//输入控制函数声明
void processInput(GLFWwindow* window);
int main() {
	//初始化
	glfwInit();
	//设置版本3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//设置配置
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//创建窗口
	GLFWwindow* window = glfwCreateWindow(800, 600, "firstOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//绑定窗口到当前线程
	glfwMakeContextCurrent(window);
	if (glewInit()!=GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return -1;
	}
	//设置绘图区域
	glViewport(0, 0, 800, 600);
	//设置背面剔除 逆时针绘制为正面
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	//设置只绘制线条
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	unsigned int vertexShader;
	vertexShader  = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glfwPollEvents();
		glClearColor(1.0, 0, 0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		//VBO绘制方式
		glBindVertexArray(VAO);
		glUseProgram(shaderProgram);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		
	}
	//结束绘制
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
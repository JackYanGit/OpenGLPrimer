//外部读档类
#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#define GLEW_STATIC          
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	ifstream vertexFile;
	ifstream fragmentFile;
	stringstream vertexSStream;
	stringstream fragmentSStream;

	//打开文档
	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);


	vertexFile.exceptions(ifstream::failbit | ifstream::badbit);
	fragmentFile.exceptions(ifstream::failbit | ifstream::badbit);

	try {
		if (!vertexFile.is_open() || !fragmentFile.is_open()) {
			throw exception("open file error!");
		}
		//读取文档到SStream
		vertexSStream << vertexFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();

		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();

		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		unsigned int vertext, fragment;
		//编译vertextShader
		vertext = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertext, 1, &vertexSource, NULL);
		glCompileShader(vertext);
		checkCompileErrors(vertext, "VERTEX");
		//编译fragmentShader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");
		//链接vertextShader与fragmentShader
		ID = glCreateProgram();
		glAttachShader(ID, vertext);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");
		//删除shader
		glDeleteShader(vertext);
		glDeleteShader(fragment);

	}
	catch (const std::exception& ex){
		printf(ex.what());
	}
}

void Shader::print()
{
	cout << vertexSource<<endl;
	cout << fragmentSource<<endl;
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::checkCompileErrors(unsigned int ID, std::string type)
{
	int success;
	char infoLog[512];

	if (type != "PROGRAM") {
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(ID, 512, NULL, infoLog);
			cout << "shader compile error:" << infoLog << endl;
		}
		
	}
	else {
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			cout << "program link error:" << infoLog << endl;
		}
	}
}

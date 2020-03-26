#pragma once
#include <string>
//�ⲿ�����࣬��ȡshader
class Shader
{
public:
	Shader(const char* vertexPath,const char* fragmentPath);
	~Shader();

	std::string vertexString;
	std::string fragmentString;
	const char* vertexSource;
	const char* fragmentSource;
	void print();
	unsigned int ID;//programID
	void use();

private:
	void checkCompileErrors(unsigned int ID, std::string type);
};


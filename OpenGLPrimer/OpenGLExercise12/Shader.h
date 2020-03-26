#pragma once
#include <string>
//外部读档类，读取shader
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


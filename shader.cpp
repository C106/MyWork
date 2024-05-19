#include<GL/glew.h>
#include <GLFW\glfw3.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<math.h>
#include<time.h>
#include "shader.h"
shader::shader(std::string path, unsigned int type) {
	std::ifstream file(path);
	std::string line, sharder;
	while (std::getline(file, line))
	{
		sharder += line + "\n";
	}
	this->type = type;
	file.close();
	code = sharder;
	unsigned int id = glCreateShader(type);
	const char* source = code.c_str();
	glShaderSource(id, 1, &source, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length];
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "×ÅÉ«Æ÷±àÒëÊ§°Ü" << (type == GL_VERTEX_SHADER ? "vs" : "fs") << std::endl;
		std::cout << message << std::endl;

	}
	ID = id;
}
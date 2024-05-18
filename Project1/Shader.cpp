#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Shader.h"
shader::shader(std::string path, unsigned int type)
		:type(type),path(path)
{
	std::ifstream sourcefile(path);
	std::string line;
	std::stringstream ss1;
	while (std::getline(sourcefile, line))
	{
		source += line + "\n";
	}
	std::cout << source;
	ID = glCreateShader(type);
	const char* jb = source.c_str();
	sourcefile.close();

	glShaderSource(ID, 1, &jb, NULL);
	glCompileShader(ID);
	int  success;
	char infoLog[512];
	glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR" << "Shader" << "COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}
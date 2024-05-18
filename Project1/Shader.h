#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
class shader {
public:
	unsigned int ID;
	std::string path;
	std::string source,line;
	unsigned int type;
	shader(std::string p, unsigned int type);
};
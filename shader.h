#pragma once
#include<GL/glew.h>
#include <GLFW\glfw3.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<math.h>
#include<time.h>
class shader {
public:
    std::string code;
	unsigned int ID,type;
	shader(std::string path,unsigned int type);
};
#pragma once
#include<GL/glew.h>
#include <GLFW\glfw3.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<math.h>
#include<time.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class program {
public:
	unsigned int ID;
	program();
	void link(unsigned int shader1, unsigned int shader2);
	void use();
	void setInt(const char* name,int value);
	void setFloat(const char* name, float value);
	void setMat4(const char* name,const glm::mat4& trans);
};
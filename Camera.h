#pragma once
#include<GL/glew.h>
#include <GLFW\glfw3.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<math.h>
#include<time.h>
#include"shader.h"
#include"GPUprogram.h"
#include"stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Camera {
public:
	
	glm::vec3 location;
	glm::vec3 front,up,right;
	glm::mat4 view;
	float pitch, yaw, roll,sens;
	float fov;

	void Keyboard(GLFWwindow* window);
	void MouseMove(double xmov,double ymov);
	glm::mat4 Getview();
	void setTarget(glm::vec3 target);
	void setFront(glm::vec3 f);
	Camera(glm::vec3 location, glm::vec3 front);
};
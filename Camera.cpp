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
#include "Camera.h"
void Camera::setTarget(glm::vec3 target) {
	view = glm::lookAt(location, target, up);
}
Camera::Camera(glm::vec3 location,glm::vec3 front)
	:location(location){
	up = glm::vec3(0.0, 1.0, 0.0);
	right = glm::cross(up, -front);
    sens = 0.5;
    fov = 45.0f;
}
void Camera::setFront() {
    glm::vec3 newfront;
    newfront.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    newfront.y = sin(glm::radians(pitch));
    newfront.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	front = newfront;
	right = glm::normalize(glm::cross(up, -front));
}
glm::mat4 Camera::Getview() {
	view = glm::lookAt(location, front + location, up);
	return view;
}
void Camera::Keyboard(GLFWwindow* window) {
    float speed = 0.05;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {

    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        location += speed * front;

    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        location -= speed * front;

    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        location += speed * right;

    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        location -= speed * right;

    }
    if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
    {

        location += glm::normalize(up) * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
    {
        location -= glm::normalize(up) * speed;

    }
    if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS) {
        fov -= 0.005;

    }
    if (glfwGetKey(window, GLFW_KEY_END) == GLFW_PRESS) {
        fov += 0.005;

    }
}
    void Camera::MouseMove(double xmov, double ymov) {
    pitch += ymov * sens;
    yaw += xmov * sens;
    
    if (pitch>89.0)
    {
        pitch = 89.0;
    }
    else if(pitch<-89.0)
    {
        pitch = -89.0;
    }

    setFront();
}
void Camera::changeRoll(float rollA) {
    up.y = cos(glm::radians(rollA));
    up.x = sin(glm::radians(rollA));
}

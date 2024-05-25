
#include<GL/glew.h>
#include <GLFW\glfw3.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<math.h>
#include<time.h>
#include "GPUprogram.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
program::program() {
    ID = glCreateProgram();
}
void program::link(unsigned int shader1, unsigned int shader2) {
    glAttachShader(ID, shader1);
    glAttachShader(ID, shader2);
    glLinkProgram(ID);
    glValidateProgram(ID);
}
void program::use() {
    glUseProgram(ID);
}
void program::setInt(const char *name, int value) {
    glUniform1i(glGetUniformLocation(ID, name), value);
}
void program::setFloat(const char* name, float value) {
    glUniform1f(glGetUniformLocation(ID, name), value);
}
void program::setMat4(const char* name, const glm::mat4& trans) {
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(trans));
}
void program::setVec3(const char* name, const glm::vec3& a) {
    glUniform3fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(a));
}
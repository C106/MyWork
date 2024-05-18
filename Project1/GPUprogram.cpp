#include"GPUprogram.h"
program::program(shader s1, shader s2)
{
	ID = glCreateProgram();
	glAttachShader(ID, s1.ID);
	glAttachShader(ID, s2.ID);
	glLinkProgram(ID);
}
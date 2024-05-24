
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;
layout(location = 2) in vec3 normal;
out vec3 outColor;
out vec2 outcoord;
out vec3 normA;
out vec3 FragPos;
uniform vec4 u_Position;
uniform vec4 u_color;
uniform float x_incre;
uniform mat4 trans;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main ()
{
	vec4 worldPosition = model * vec4(position, 1.0);
	worldPosition.x = floor(worldPosition.x * 100000.0) / 100000;
    worldPosition.y = floor(worldPosition.y * 100000.0) / 100000;
    worldPosition.z = floor(worldPosition.z * 100000.0) / 100000;
	gl_Position = projection * view * worldPosition;
	normA = mat3(transpose(inverse(model)))*normal;
	FragPos=vec3(model * vec4(position, 1.0));
	float fac=abs(sin(u_color.x));
	outcoord = texcoord;
};

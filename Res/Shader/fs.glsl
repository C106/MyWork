#version 330 core
out vec4 color;
in vec2 outcoord;
in vec3 normA;
in vec3 FragPos;
uniform vec3 Lightpos;
uniform vec3 lightColor;
uniform vec3 viewPos;
//uniform mat4 rot;
uniform mat4 trs;
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;
uniform Material material;
void main ()
{
	vec3 norm = normalize(normA);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);



	vec3 view = normalize(viewPos-FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(reflectDir,view),0.0),128);


    
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, outcoord));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, outcoord));
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, outcoord));
    vec3 result = specular+diffuse+ambient;
   color = vec4(result,1.0);
   //;
};
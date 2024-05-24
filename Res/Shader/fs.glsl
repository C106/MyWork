#version 330 core
out vec4 color;
in vec2 outcoord;
in vec3 normA;
in vec3 FragPos;
uniform sampler2D tex;
uniform sampler2D tex2;
uniform vec3 Lightpos;
uniform vec3 lightColor;
uniform vec3 viewPos;
//uniform mat4 rot;
uniform mat4 trs;
void main ()
{
	float specStrength =3;
	vec4 pps = trs*vec4(Lightpos,1.0);
	vec3 norm = normalize(normA);
	vec3 lightDir = normalize(pps.xyz - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;
	vec3 view = normalize(viewPos-FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(reflectDir,view),0.0),128);
	vec3 speclar = specStrength*spec * lightColor;
    vec3 result = (speclar+diff+ambient) * vec3(mix(texture(tex,outcoord),texture(tex2,outcoord),0.1));
   color = vec4(result,1.0);
   //;
};
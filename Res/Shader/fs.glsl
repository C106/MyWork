#version 330 core
in vec4 outColor;
out vec4 color;
in vec2 outcoord;
uniform sampler2D tex;
uniform sampler2D tex2;
uniform float mixvalue;
void main ()
{
   color = mix(texture(tex,vec2(mixvalue - outcoord.x,outcoord.y)),texture(tex2,outcoord),0.1);
};
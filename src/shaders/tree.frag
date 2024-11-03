#version 330 core
out vec4 FragColor;
  
in vec3 color;

uniform vec3 eye = vec3(0.0,0.0,3.0);
uniform vec3 lightPosition;

void main()
{
    FragColor = vec4(0.385 ,0.647 ,0.812 ,1.0);
}
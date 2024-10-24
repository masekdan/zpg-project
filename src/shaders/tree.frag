#version 330 core
out vec4 FragColor;
  
in vec3 color;

uniform vec3 eye = vec3(0.0,0.0,3.0);

void main()
{
    FragColor = vec4(color,1.0);
}
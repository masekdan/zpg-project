#version 330 core
out vec4 FragColor;
  
in vec4 vertexColor;

uniform vec4 myColor;

void main()
{
    FragColor = vec4(ourColor,1.0);
}
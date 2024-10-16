#version 330
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
  
out vec3 color;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

layout(location=0) in vec3 vp;
void main () {
     gl_Position = projection * view * model * vec4 (vp, 1.0);
     color = aColor;
}
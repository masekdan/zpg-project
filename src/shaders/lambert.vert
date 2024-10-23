#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 normalMatrix; //(M-1)T

out vec3 ex_worldPosition;
out vec3 ex_worldNormal;


void main(void){
    gl_Position = projection * view * model * vec4(aPos,1.0);
    ex_worldPosition = modelMatrix * vec4(aPos,1.0f);
    ex_worldNormal = normalMatrix * aNormal;
}
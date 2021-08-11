#version 330 core

out vec2 oTexCoords;

layout (location = 0) in vec3 iPos;
layout (location = 1) in vec2 iTexCoords;


void main(){
    gl_Position = vec4(iPos, 1.0);
    oTexCoords = iTexCoords;
}
#version 330 core

out vec4 fBackgroundColor;
out vec4 fBorderColor;
out vec4 fBorderRect;

layout (location = 0) in vec3 vCoords;
layout (location = 1) in vec3 vOffset;
layout (location = 2) in vec3 vScale;
layout (location = 5) in vec4 vBackgroundColor;
layout (location = 6) in vec4 vBorderColor;
layout (location = 7) in vec4 vBorderRect;

void main(){
    gl_Position = vec4(vCoords * vScale + vOffset, 1.0);
    fBackgroundColor = vBackgroundColor;
    fBorderColor = vBorderColor;
    fBorderRect = vBorderRect;
}
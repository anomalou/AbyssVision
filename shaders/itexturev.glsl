#version 330 core

out vec2 fTexCoord;
out vec4 fTexOffset;

layout (location = 0) in vec3 vCoords;
layout (location = 1) in vec3 vOffset;
layout (location = 2) in vec3 vScale;
layout (location = 3) in vec2 vTexCoord;
layout (location = 4) in vec4 vTexOffset;

void main(){
    gl_Position = vec4(vCoords * vScale + vOffset, 1.0);
    fTexCoord = vTexCoord;
    fTexOffset = vTexOffset;
}
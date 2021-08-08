#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 aTexCoord;
out vec4 vertexColor;
out vec2 texCoord;
uniform int flip;

void main(){
    gl_Position = vec4(aPos, 1.0);
    vertexColor = color;
    if(flip == 0){
        texCoord = aTexCoord;
    }
    if(flip == 1){
        texCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
    }
}
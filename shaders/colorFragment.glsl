#version 330 core

in vec4 vertexColor;
out vec4 fragColor;
uniform int useVertexColor;
uniform vec4 color;

void main(){
    if(useVertexColor == 1)
        fragColor = vertexColor;
    else
        fragColor = color;
}
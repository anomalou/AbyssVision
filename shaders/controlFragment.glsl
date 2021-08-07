#version 330 core

out vec4 fragColor;

in vec4 vertexColor;
in vec2 texCoord;
uniform sampler2D uTexture;
uniform vec4 colorModificator;

void main(){
    vec4 texel = texture(uTexture, texCoord);
    if(texel.x == 0.0){
        fragColor = colorModificator;
    }else{
        fragColor = texel;
    }
}
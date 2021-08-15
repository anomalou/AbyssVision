#version 330 core

out vec4 oFragColor;

in vec2 fTexCoord;
in vec4 fTexOffset;

uniform sampler2D fTexture;
uniform bool fFlip;

void main(){
    vec2 texCoord = fTexCoord;
    if(fFlip == true)
        texCoord = vec2(texCoord.x, 1.0 - texCoord.y);

    texCoord = texCoord * vec2(fTexOffset.z, fTexOffset.w) + vec2(fTexOffset.x, fTexOffset.y);

    oFragColor = texture(fTexture, texCoord);
}
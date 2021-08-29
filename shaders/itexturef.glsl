#version 330 core

out vec4 oFragColor;

in vec2 fTexCoord;
in vec4 fTexOffset;

uniform sampler2D fTexture;
uniform bool fFlip;

void main(){
    vec2 texCoord = fTexCoord;

    texCoord = texCoord * vec2(fTexOffset.z, fTexOffset.w) + vec2(fTexOffset.x, fTexOffset.y);

    if(fFlip == true)
        texCoord = vec2(texCoord.x, 1.0 - texCoord.y);

    vec4 texel = texture(fTexture, texCoord);

    // if(texel.w == 0)
    //     texel.x = 1;

    // texel.w = 1;

    oFragColor = texel;
}
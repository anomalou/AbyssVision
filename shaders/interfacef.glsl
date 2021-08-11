#version 330 core

out vec4 oFragColor;

layout(origin_upper_left) in vec4 gl_FragCoord;
in vec2 oTexCoords;

uniform bool textureFill;
uniform bool flipTexture;
uniform sampler2D uTexture;
uniform bool drawBorder;
uniform ivec4 borderRect;
uniform vec4 backgroundColor;
uniform vec4 borderColor;
uniform vec2 screenResolution;

void main(){
    vec2 texCoords = oTexCoords;
    if(textureFill == true){
        if(flipTexture == true)
            texCoords = vec2(texCoords.x, 1.0 - texCoords.y);

        oFragColor = texture(uTexture, texCoords);
    }else{
        oFragColor = backgroundColor;
    }

    if(drawBorder == true){
        bool border = false;
        vec4 fragCoords = gl_FragCoord;

        if((fragCoords.x - 1) < borderRect.x && fragCoords.x >= borderRect.x && fragCoords.y > borderRect.y && fragCoords.y < (borderRect.y + borderRect.w))
            border = true;

        if((fragCoords.x + 1) > (borderRect.x + borderRect.z) && fragCoords.x <= (borderRect.x + borderRect.z) && fragCoords.y > borderRect.y && fragCoords.y < (borderRect.y + borderRect.w))
            border = true;

        if((fragCoords.y - 1) < borderRect.y && fragCoords.y >= borderRect.y && fragCoords.x > borderRect.x && fragCoords.x < (borderRect.x + borderRect.z))
            border = true;
        
        if((fragCoords.y + 1) > (borderRect.y + borderRect.w) && fragCoords.y <= (borderRect.y + borderRect.w) && fragCoords.x > borderRect.x && fragCoords.x < (borderRect.x + borderRect.z))
            border = true;

        if(border == true)
            oFragColor = borderColor;
    }
}
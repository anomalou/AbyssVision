#version 330 core

out vec4 oFragColor;

in vec4 fBackgroundColor;
in vec4 fBorderColor;
in vec4 fBorderRect;

layout (origin_upper_left) in vec4 gl_FragCoord;

void main(){
    oFragColor = fBackgroundColor;

    if(fBackgroundColor != fBorderColor){
        bool drawBorder = false;
        vec4 fragCoord = gl_FragCoord;

        if((fragCoord.x - 1) < fBorderRect.x && fragCoord.x >= fBorderRect.x && fragCoord.y > fBorderRect.y && fragCoord.y < (fBorderRect.y + fBorderRect.w))
            drawBorder = true;

        if((fragCoord.x + 1) > (fBorderRect.x + fBorderRect.z) && fragCoord.x <= (fBorderRect.x + fBorderRect.z) && fragCoord.y > fBorderRect.y && fragCoord.y < (fBorderRect.y + fBorderRect.w))
            drawBorder = true;

        if((fragCoord.y - 1) < fBorderRect.y && fragCoord.y >= fBorderRect.y && fragCoord.x > fBorderRect.x && fragCoord.x < (fBorderRect.x + fBorderRect.z))
            drawBorder = true;
        
        if((fragCoord.y + 1) > (fBorderRect.y + fBorderRect.w) && fragCoord.y <= (fBorderRect.y + fBorderRect.w) && fragCoord.x > fBorderRect.x && fragCoord.x < (fBorderRect.x + fBorderRect.z))
            drawBorder = true;

        if(drawBorder == true)
            oFragColor = fBorderColor;
    }
}
#version 100

precision highp float;

varying vec2 TexCoords;

uniform sampler2D texture;
uniform float time;

void main()
{
    gl_FragColor = texture2D(texture, TexCoords +
        0.005*vec2(sin(time+1024.0*TexCoords.x),cos(time+768.0*TexCoords.y)));
}


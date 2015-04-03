#version 100

precision highp float;

uniform sampler2D texture;

varying vec2 TexCoords;

void main()
{
    gl_FragColor = texture2D(texture, TexCoords);
}

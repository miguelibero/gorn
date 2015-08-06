#version 100

precision highp float;

varying vec2 TexCoords;
varying vec3 Color;

uniform sampler2D texture;

void main()
{
    gl_FragColor = vec4(Color, 1.0)*texture2D(texture, TexCoords);
}

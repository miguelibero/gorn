#version 100

precision highp float;

attribute vec2 position;
attribute vec3 color;
attribute vec2 texCoords;

uniform float timeSin;

varying vec3 Color;
varying vec2 TexCoords;

void main()
{
    Color = color;
    TexCoords = texCoords;
    gl_Position = vec4(position, 0.0, 0.2*timeSin+1.0);
}

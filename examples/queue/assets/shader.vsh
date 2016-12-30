#version 100

precision highp float;

attribute vec2 position;
attribute vec2 texCoords;
varying vec2 TexCoords;

void main()
{
    TexCoords = texCoords;
    gl_Position = vec4(position, 0.0, 1.0);
}

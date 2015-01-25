#version 100

precision highp float;

attribute vec2 position;
attribute vec3 color;
attribute vec2 texCoords;

uniform mat4 transform;

varying vec3 Color;
varying vec2 TexCoords;

void main()
{
    Color = color;
    TexCoords = texCoords;
    gl_Position = transform * vec4(position, 0.0, 1.0);
}

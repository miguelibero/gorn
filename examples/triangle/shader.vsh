#version 100

precision highp float;

attribute vec3 color;
attribute vec2 position;

varying vec3 Color;

void main()
{
    Color = color;
    gl_Position = vec4(position, 0.0, 1.0);
}

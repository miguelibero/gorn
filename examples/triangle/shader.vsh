#version 100

precision highp float;

attribute vec3 color;
attribute vec2 position;

uniform float timeSin;

varying vec3 Color;

void main()
{
    Color = color;
    gl_Position = vec4(position, 0.0, 0.2*timeSin+1.0);
}

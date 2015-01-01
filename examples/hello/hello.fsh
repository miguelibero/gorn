#version 100

attribute vec2 position;
attribute vec3 color;

varying vec3 Color;

void main()
{
    gl_Color = vec4(Color, 1.0);
}

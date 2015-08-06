#version 100

precision highp float;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
uniform vec3 overrideColor;

attribute vec3 position;
attribute vec3 color;
attribute vec2 texCoords;

varying vec3 Color;
varying vec2 TexCoords;

void main()
{
    TexCoords = texCoords;
    Color = color*overrideColor;
    gl_Position = proj * view * model * vec4(position, 1.0);
}

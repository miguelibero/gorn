#version 100

precision highp float;

attribute vec2 position;
attribute vec2 texCoords;
uniform mat4 model;
uniform mat4 cam;
varying vec2 TexCoords;

void main()
{
    TexCoords = texCoords;
    gl_Position = cam * model * vec4(position, 0.0, 1.0);
}

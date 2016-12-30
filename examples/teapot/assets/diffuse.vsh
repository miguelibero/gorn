#version 100

precision highp float;

attribute vec3 position;
attribute vec2 texCoords;

uniform mat4 proj;
uniform mat4 view;

varying vec2 TexCoords;

void main()
{
    TexCoords = texCoords;
    gl_Position = proj * view * vec4(position, 1.0);
}

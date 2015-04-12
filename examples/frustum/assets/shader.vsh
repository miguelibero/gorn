#version 100

precision highp float;

attribute vec3 position;

uniform mat4 proj;
uniform mat4 model;
uniform mat4 view;

void main()
{
    gl_Position = proj * view * model * vec4(position, 1.0);
}

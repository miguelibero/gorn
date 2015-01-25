#version 100

precision highp float;

uniform float timeSin;

varying vec3 Color;

void main()
{
    gl_FragColor = vec4(Color, 1.0);
}

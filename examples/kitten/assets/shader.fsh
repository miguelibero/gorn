#version 100

precision highp float;

varying vec3 Color;
varying vec2 TexCoords;

uniform sampler2D texture;

void main()
{
    gl_FragColor = texture2D(texture, TexCoords) * vec4(Color, 1.0);
}

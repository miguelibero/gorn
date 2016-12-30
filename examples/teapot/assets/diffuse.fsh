#version 100

precision highp float;

uniform sampler2D texture;

varying vec2 TexCoords;

void main()
{
    gl_FragColor = texture2D(texture, TexCoords) + vec4(1.0, 0.0, 0.0, 1.0);
}

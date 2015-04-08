#version 100

precision highp float;

varying vec2 TexCoords;

uniform sampler2D texture;

vec4 sepia(in vec4 color)
{
    return vec4(
          clamp(color.r * 0.393 + color.g * 0.769 + color.b * 0.189, 0.0, 1.0)
        , clamp(color.r * 0.349 + color.g * 0.686 + color.b * 0.168, 0.0, 1.0)
        , clamp(color.r * 0.272 + color.g * 0.534 + color.b * 0.131, 0.0, 1.0)
        , color.a
    );
}

void main()
{
    gl_FragColor = texture2D(texture, TexCoords);
    gl_FragColor = mix(gl_FragColor, sepia(gl_FragColor), 0.8);
}


uniform mat4 projView;

attribute vec2 position;
attribute vec2 texCoord;
attribute vec4 color;

varying vec4 vColor;
varying vec2 vTexCoord;

void main() {
    vColor = color;
    vTexCoord = texCoord;
    gl_Position = projView * vec4(position, 0.0, 1.0);
}
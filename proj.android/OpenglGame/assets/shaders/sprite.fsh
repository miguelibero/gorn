uniform sampler2D texture;

varying vec4 vColor;
varying vec2 vTexCoord;

void main() {
    vec4 texColor = texture2D(texture, vTexCoord);
    gl_FragColor = vColor * texColor;
}

#version 150
uniform sampler2D texturesampler;

varying vec2 frag_texcoord;

void main() {
    float color = texture(texturesampler, frag_texcoord).r;
    gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0 * color);
}


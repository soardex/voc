#version 150
precision highp float;

in vec2 uv;

uniform sampler2D texturesampler;
uniform vec4 diffuse;
uniform int type;

out vec4 fragcolor;

void main() {
    if (type == 1) {
        fragcolor = texture(texturesampler, uv);
    } else {
        fragcolor = diffuse;
    }
}


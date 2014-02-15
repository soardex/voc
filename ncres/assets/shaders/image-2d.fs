#version 150
precision highp float;

uniform sampler2D texturesampler;
uniform vec4 diffuse;
uniform bool textured;

varying vec2 tc;

out vec4 fragcolor;

void main() {
    if (textured) {
        fragcolor = texture(texturesampler, tc);
    } else {
        fragcolor = diffuse;
    }
}


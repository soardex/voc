#version 150

varying vec3 nm;
varying vec2 uv;

uniform sampler2D texture;
uniform vec4 diffuse;

void main() {
    gl_FragColor = diffuse;
}


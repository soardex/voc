#version 150

attribute vec3 position;
attribute vec3 normal;
attribute vec2 tc;

uniform mat4 mvp;

varying vec2 uv;
varying vec3 nm;

void main() {
    gl_Position = mvp * vec4(position, 1.0);
    uv = tc;

    nm = normalize(normal);
}


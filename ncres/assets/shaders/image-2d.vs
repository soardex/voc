#version 150

attribute vec3 position;
attribute vec2 texcoord;
attribute float time;

uniform mat4 mvp;
out vec2 uv;

void main() {
    gl_Position = mvp * vec4(position, 1.0);
    uv = texcoord;
}


#version 150

attribute vec3 position;
attribute vec2 texcoord;
attribute float time;

uniform mat4 modelview;
uniform mat4 projection;

varying vec2 tc;

void main() {
    vec4 transformed = modelview * vec4(position, 1.0);
    gl_Position = projection * transformed;
    tc = texcoord;
}


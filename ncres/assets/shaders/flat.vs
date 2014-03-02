#version 150
attribute vec2 position;
attribute vec2 texcoord;

uniform float offset;
uniform mat4 projection;

varying vec2 frag_texcoord;

void main() {
    vec4 transformed = vec4(position.x, (position.y * -1.0) + (offset), 0.0, 1.0);
    gl_Position = projection * transformed;

    frag_texcoord = texcoord;
}

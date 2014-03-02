#version 150

attribute vec3 position;
attribute vec2 texcoord;

uniform float time;
uniform vec4 diffuse;

uniform mat4 modelview;
uniform mat4 projection;

varying vec2 frag_texcoord;
varying vec3 frag_diffuse;
varying vec3 frag_ambient;
varying vec3 frag_specular;
varying vec3 frag_emission;

void main() {
    vec4 transformed = modelview * vec4(position, 1.0);
    gl_Position = projection * transformed;

    frag_diffuse = diffuse.xyz;
    frag_texcoord = texcoord;
}


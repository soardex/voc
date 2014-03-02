#version 150
precision highp float;

uniform sampler2D texturesampler;
uniform bool textured;

varying vec2 frag_texcoord;
varying vec3 frag_diffuse;
varying vec3 frag_ambient;
varying vec3 frag_specular;
varying vec3 frag_emission;

void main() {
    if (textured) {
        vec4 color = texture(texturesampler, frag_texcoord);
        gl_FragColor = color;
    } else {
        gl_FragColor = vec4(frag_diffuse, 1.0);
    }
}


#version 400 core

#include "common"

#include <common>

in vec3 frag_color;

void main() {
    gl_FragColor = vec4(frag_color, 1.0f);
}
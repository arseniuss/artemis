#version 400 core

#include "common"

#include <common>

in vec3 position;

uniform float size;
uniform float scale;

in vec3 color;
out vec3 frag_color;

void main() {
    
    gl_PointSize = size; 
    
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1);
    
    frag_color = color;
}

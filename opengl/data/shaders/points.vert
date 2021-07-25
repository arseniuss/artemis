#version 150

in vec4 position;

uniform float size;

void main() {
    gl_Position = position;
    gl_PointSize = size;
}

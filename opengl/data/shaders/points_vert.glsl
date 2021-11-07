#include <common>
#include <project_params>
#include <color_params>

uniform float size;
uniform float scale;
void main() {
    #include <project_vertex>
    
    gl_PointSize = size;
    gl_Position = projectionMatrix * modelViewMatrix * modelMatrix * position;
    
    
}
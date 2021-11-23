#include <common>
#include <project_params>

uniform float size;
uniform float scale;

in vec3 color;
out vec3 frag_color;

void main() {
    
    gl_PointSize = size; 
    
    #include <project_vertex>  
    
    frag_color = color;
}

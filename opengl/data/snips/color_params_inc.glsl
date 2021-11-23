#if defined(USE_COLOR_ALPHA)
in vec4 color;
#if defined(VERTEX_SHADER)
out vec4 out_color;
#endif
#elif defined(USE_COLOR)
in vec3 color;
#if defined(VERTEX_SHADER)
out vec3 out_color;
#endif
#endif

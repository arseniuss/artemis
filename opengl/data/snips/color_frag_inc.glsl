#if defined(USE_COLOR_ALPHA)
gl_FragColor = color;
#elif defined(USE_COLOR)
gl_FragColor = vec4(color, 1.0);
#endif

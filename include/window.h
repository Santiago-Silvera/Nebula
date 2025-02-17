#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>

typedef struct {
  const char *name;
  unsigned int width;
  unsigned int height;
  GLFWwindow *window;
} window_t;

window_t create_window();

#endif

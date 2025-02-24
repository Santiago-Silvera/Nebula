#ifndef CAMERA_H
#define CAMERA_H

#include "shader.h"

#include "GLFW/glfw3.h"
#include <cglm/cglm.h>

typedef struct Camera {
  vec3 position;
  vec3 orientation;
  vec3 up;
  int width;
  int height;
  float speed;
  float sensitivity;
} camera_t;

camera_t create_camera(vec3 position, int width, int height, float speed,
                       float sensitivity);
void camera_matrix(camera_t *cam, float FOVdeg, float near_plane,
                   float far_plane, SHADER_ID shader, const char *uniform);

void inputs(GLFWwindow *window, camera_t *cam);

#endif

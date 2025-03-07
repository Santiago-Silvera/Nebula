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
  mat4 matrix;
} camera_t;

camera_t create_camera(vec3 position, int width, int height, float speed, float sensitivity);
void update_camera_matrix(camera_t *cam, float FOVdeg, float near_plane, float far_plane);
void apply_camera_matrix(SHADER_ID shader, const char* uniform, mat4 *m);

void inputs(GLFWwindow *window, camera_t *cam);

#endif

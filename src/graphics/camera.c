#include "camera.h"
#include "GLFW/glfw3.h"
#include "cglm/affine-pre.h"
#include "cglm/io.h"
#include "cglm/vec3.h"
#include <math.h>

camera_t create_camera(vec3 position, int width, int height, float speed, float sensitivity) {
  vec3 final_position;
  if (position) {
    glm_vec3_copy(position, final_position); // Copy the provided position
  } else {
    glm_vec3_zero(final_position);
  }
  camera_t cam = {
      .position = {final_position[0], final_position[1], final_position[2]},
      .orientation = {0.0f, 0.0f, -1.0f},
      .up = {0.0f, 1.0f, 0.0f},
      .width = width,
      .height = height,
      .speed = speed,
      .sensitivity = sensitivity,
      .matrix = GLM_MAT4_IDENTITY_INIT,
  };
  return cam;
}

void update_camera_matrix(camera_t *cam, float FOVdeg, float near_plane, float far_plane) {
  mat4 view, projection;

  vec3 target;
  glm_vec3_add(cam->position, cam->orientation, target);

  glm_lookat(cam->position, target, cam->up, view);
  glm_perspective(glm_rad(FOVdeg), (float)cam->width / cam->height, near_plane, far_plane, projection);

  glm_mat4_mul(projection, view, cam->matrix);
}

void apply_camera_matrix(SHADER_ID shader, const char* uniform, mat4 *m) {
  glUniformMatrix4fv(glGetUniformLocation(shader, uniform), 1, GL_FALSE, (float *)m);
}

void inputs(GLFWwindow *window, camera_t *cam) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    vec3 direction;
    glm_vec3_scale(cam->orientation, cam->speed, direction);
    glm_vec3_add(cam->position, direction, cam->position);
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    vec3 direction;
    glm_vec3_cross(cam->up, cam->orientation, direction);
    glm_vec3_norm(direction);
    glm_vec3_scale(direction, cam->speed, direction);
    glm_vec3_add(cam->position, direction, cam->position);
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    vec3 direction;
    glm_vec3_scale(cam->orientation, cam->speed, direction);
    glm_vec3_sub(cam->position, direction, cam->position);
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    vec3 direction;
    glm_vec3_cross(cam->up, cam->orientation, direction);
    glm_vec3_norm(direction);
    glm_vec3_scale(direction, cam->speed, direction);
    glm_vec3_sub(cam->position, direction, cam->position);
  }
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    vec3 direction;
    glm_vec3_scale(cam->up, cam->speed, direction);
    glm_vec3_add(cam->position, direction, cam->position);
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
    vec3 direction;
    glm_vec3_scale(cam->up, cam->speed, direction);
    glm_vec3_sub(cam->position, direction, cam->position);
  }  
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    cam->speed = 0.05f;
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
    cam->speed = 0.01f;
  }

  // MOUSE INPUT -------------------------------------

  if (glfwGetWindowAttrib(window, GLFW_FOCUSED) == GLFW_FALSE) {
    glfwFocusWindow(window);
  }
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  double mouseX, mouseY;
  glfwGetCursorPos(window, &mouseX, &mouseY);

  float centerX = (cam->width / 2.0f);
  float centerY = (cam->height / 2.0f);

  // First mouse movement initialization
  static bool firstMouse = true;
  if (firstMouse) {
      mouseX = centerX;
      mouseY = centerY;
      firstMouse = false;
  }

  // Calculate mouse offset
  float offsetX = ((float)mouseX - centerX) * cam->sensitivity * 0.1f;
  float offsetY = ((float)mouseY - centerY) * cam->sensitivity * 0.1f;

  // Reset cursor to center
  glfwSetCursorPos(window, centerX, centerY);

  // Calculate right vector
  vec3 right;
  glm_vec3_cross(cam->orientation, cam->up, right);
  glm_vec3_norm(right);

  // Apply rotation to orientation vector
  vec3 newOrientation;
  glm_vec3_copy(cam->orientation, newOrientation);
  glm_vec3_rotate(newOrientation, glm_rad(-offsetX), cam->up);

  if (fabsf(glm_vec3_angle(newOrientation, cam->up) - glm_rad(90.0f)) <= glm_rad(85.0f)) {
    glm_vec3_copy(newOrientation, cam->orientation);
  }
  glm_vec3_rotate(cam->orientation, glm_rad(-offsetY), right);
  glm_vec3_norm(cam->orientation);

  // printf("Orientation: "); glm_vec3_print(cam->orientation, stdout);
}

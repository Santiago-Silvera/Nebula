// glad needs to be imported BEFORE GLFW
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <stb_image.h>
#include <stdio.h>
#include <time.h>

#include "EBO.h"
#include "VAO.h"
#include "VBO.h"
#include "cglm/mat4.h"
#include "shader.h"
#include "texture.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

GLfloat vertices[] =
    { //     COORDINATES     /        COLORS      /   TexCoord  //
        -0.5f, 0.0f,  0.5f,  0.83f, 0.70f, 0.44f, 0.0f,  0.0f,  -0.5f, 0.0f,
        -0.5f, 0.83f, 0.70f, 0.44f, 5.0f,  0.0f,  0.5f,  0.0f,  -0.5f, 0.83f,
        0.70f, 0.44f, 0.0f,  0.0f,  0.5f,  0.0f,  0.5f,  0.83f, 0.70f, 0.44f,
        5.0f,  0.0f,  0.0f,  0.8f,  0.0f,  0.92f, 0.86f, 0.76f, 2.5f,  5.0f};

// Indices for vertices order
GLuint indices[] = {0, 1, 2, 0, 2, 3, 0, 1, 4, 1, 2, 4, 2, 3, 4, 3, 0, 4};

int main() {
  // Init the window
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    printf("Failed to create GLFW window\n");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD\n");
    return -1;
  }

  // Create a shader program
  // TODO: Find a better way of finding the path
  SHADER_ID shader = create_shader_program(
      "/home/santiago/projects/rendering-engine/shaders/default.vert",
      "/home/santiago/projects/rendering-engine/shaders/default.frag");

  // Create a VAO and bind it
  VAO_ID VAO = create_VAO();
  bind_VAO(&VAO);

  // Create VBO and EBO
  VBO_ID VBO = create_VBO(vertices, sizeof(vertices));
  EBO_ID EBO = create_EBO(indices, sizeof(indices));

  // Link attributes
  link_attrib(&VAO, &VBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)(0));
  link_attrib(&VAO, &VBO, 1, 3, GL_FLOAT, 8 * sizeof(float),
              (void *)(3 * sizeof(float)));
  link_attrib(&VAO, &VBO, 2, 2, GL_FLOAT, 8 * sizeof(float),
              (void *)(6 * sizeof(float)));

  // Make sure that everything is unbinded
  unbind_VAO();
  unbind_VBO();
  unbind_EBO();

  // Texture

  texture_t texture = create_texture(
      "/home/santiago/projects/rendering-engine/resources/brick.png",
      GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
  assign_texUnit(&shader, "tex0", 0);

  mat4 model, view, projection;

  glEnable(GL_DEPTH_TEST);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    activate_shader(&shader);

    bind_texture(&texture);

    glm_mat4_identity(model);
    float timeValue = (float)glfwGetTime();

    glm_rotate(model, glm_rad(timeValue * 50.0f), (vec3){0.0f, 1.0f, 0.0f});

    vec3 camPos = {0.0f, 1.5f, 2.0f};
    vec3 camTarget = {0.0f, 0.0f, 0.0f};
    vec3 camUp = {0.0f, 1.0f, 0.0f};

    glm_perspective(glm_rad(45.0f), 800.0f / 600.0f, 0.1f, 100.0f, projection);

    glm_lookat(camPos, camTarget, camUp, view);

    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE,
                       (const GLfloat *)model);
    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE,
                       (const GLfloat *)view);
    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE,
                       (const GLfloat *)projection);

    bind_VAO(&VAO);
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(typeof(indices[0])),
                   GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  delete_VAO(&VAO);
  delete_VBO(&VBO);
  delete_EBO(&EBO);
  delete_shader(&shader);
  delete_texture(&texture);
  glfwTerminate();

  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

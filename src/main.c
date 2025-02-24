// glad needs to be imported BEFORE GLFW
#include <glad/glad.h>

#include "GLFW/glfw3.h"
#include "camera.h"

#include <stb_image.h>
#include <stdio.h>
#include <time.h>

#include "EBO.h"
#include "VAO.h"
#include "VBO.h"
#include "shader.h"
#include "texture.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void error_callback(int error, const char *desc);

GLfloat vertices[] =
    { //     COORDINATES     /        COLORS      /   TexCoord  //
        -0.5f, 0.0f,  0.5f,  0.83f, 0.70f, 0.44f, 0.0f,  0.0f,  -0.5f, 0.0f,
        -0.5f, 0.83f, 0.70f, 0.44f, 5.0f,  0.0f,  0.5f,  0.0f,  -0.5f, 0.83f,
        0.70f, 0.44f, 0.0f,  0.0f,  0.5f,  0.0f,  0.5f,  0.83f, 0.70f, 0.44f,
        5.0f,  0.0f,  0.0f,  0.8f,  0.0f,  0.92f, 0.86f, 0.76f, 2.5f,  5.0f};

// Indices for vertices order
GLuint indices[] = {0, 1, 2, 0, 2, 3, 0, 1, 4, 1, 2, 4, 2, 3, 4, 3, 0, 4};

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

int main() {
  // Init the window
  printf("Initializing rendering engine\n\n\n");
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    printf("Failed to create GLFW window\n");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwFocusWindow(window);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetErrorCallback(error_callback);

  // Check if GLFW_CURSOR_DISABLED is properly set
  int mode = glfwGetInputMode(window, GLFW_CURSOR);
  if (mode == GLFW_CURSOR_DISABLED) {
    printf("GLFW_CURSOR_DISABLED successfully set.\n");
  } else {
    printf("Failed to set GLFW_CURSOR_DISABLED, current mode: %d\n", mode);
  }

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD\n");
    return -1;
  }

  // Create a shader program
  // TODO: Find a better way of finding the path
  SHADER_ID shader =
      create_shader_program("shaders/default.vert", "shaders/default.frag");

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

  texture_t texture = create_texture("resources/brick.png", GL_TEXTURE_2D,
                                     GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
  assign_texUnit(&shader, "tex0", 0);

  glEnable(GL_DEPTH_TEST);
  vec3 camPos = {0.0f, 0.0f, 1.0f};
  camera_t cam = create_camera(camPos, SCR_WIDTH, SCR_HEIGHT, 0.01f, 1.f);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    activate_shader(&shader);

    inputs(window, &cam);
    camera_matrix(&cam, 45.0f, 0.1f, 100.0f, shader, "camMatrix");

    bind_texture(&texture);

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
void error_callback(int error, const char *desc) {
  fprintf(stderr, "GLFW Error (%d): %s\n", error, desc);
}

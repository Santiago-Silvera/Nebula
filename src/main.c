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

GLfloat vertices[] ={
   //   COORDINATES       /        COLORS     / TexCoord    /    NORMALS   //
   -1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
   -1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
    1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
    1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
 };

GLuint indices[] = {
	0, 1, 2,
	0, 2, 3
};

GLfloat lightVertices[] ={
   //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] ={
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

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
  SHADER_ID shader = create_shader_program("shaders/default.vert", "shaders/default.frag");

  // Create a VAO and bind it
  VAO_ID VAO = create_VAO();
  bind_VAO(&VAO);

  // Create VBO and EBO
  VBO_ID VBO = create_VBO(vertices, sizeof(vertices));
  EBO_ID EBO = create_EBO(indices, sizeof(indices));

  // Link attributes
  link_attrib(&VAO, &VBO, 0, 3, GL_FLOAT, 11 * sizeof(float), (void *)(0));
  link_attrib(&VAO, &VBO, 1, 3, GL_FLOAT, 11 * sizeof(float), (void *)(3 * sizeof(float)));
  link_attrib(&VAO, &VBO, 2, 2, GL_FLOAT, 11 * sizeof(float), (void *)(6 * sizeof(float)));
  link_attrib(&VAO, &VBO, 3, 3, GL_FLOAT, 11 * sizeof(float), (void *)(8 * sizeof(float)));

  // Make sure that everything is unbinded
  unbind_VAO();
  unbind_VBO();
  unbind_EBO();

  SHADER_ID lightShader = create_shader_program("shaders/light.vert", "shaders/light.frag");
  VAO_ID lightVAO = create_VAO();
  bind_VAO(&lightVAO);

  VBO_ID lightVBO = create_VBO(lightVertices, sizeof(lightVertices));
  EBO_ID lightEBO = create_EBO(lightIndices, sizeof(lightIndices));

  link_attrib(&lightVAO, &lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void *)(0));

  unbind_VAO();
  unbind_VBO();
  unbind_EBO();

  vec4 lightColor = {1.0f, 1.0f, 1.0f, 1.0f};

  vec3 lightPos = {0.0f, 1.5f, -1.5f};
  mat4 lightModel = GLM_MAT4_IDENTITY_INIT;
  glm_translate(lightModel, lightPos);

  vec3 pyramidPos = {0.0f, 0.0f, -1.5f};
  mat4 pyramidModel = GLM_MAT4_IDENTITY_INIT;
  glm_translate(pyramidModel, pyramidPos);

  activate_shader(&lightShader);
  glUniformMatrix4fv(glGetUniformLocation(lightShader, "model"), 1, GL_FALSE, (float *)lightModel);
  glUniform4f(glGetUniformLocation(lightShader, "lightColor"), lightColor[0], lightColor[1], lightColor[2], lightColor[3]);
  activate_shader(&shader);
  glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, (float *)pyramidModel);
  glUniform4f(glGetUniformLocation(shader, "lightColor"), lightColor[0], lightColor[1], lightColor[2], lightColor[3]);
  glUniform3f(glGetUniformLocation(shader, "lightPos"), lightPos[0], lightPos[1], lightPos[2]);


  // Texture

  texture_t texture = create_texture("resources/planks.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
  assign_texUnit(&shader, "tex0", 0);

  glEnable(GL_DEPTH_TEST);
  vec3 camPos = {0.0f, 0.0f, 1.0f};
  camera_t cam = create_camera(camPos, SCR_WIDTH, SCR_HEIGHT, 0.01f, 1.f);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    inputs(window, &cam);
    update_camera_matrix(&cam, 45.0f, 0.1f, 100.0f);

    activate_shader(&shader);

    glUniform3f(glGetUniformLocation(shader, "camPos"), cam.position[0], cam.position[1], cam.position[2]);

    apply_camera_matrix(shader, "camMatrix", &(cam.matrix));

    bind_texture(&texture);

    bind_VAO(&VAO);
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(typeof(indices[0])), GL_UNSIGNED_INT, 0);
    unbind_texture();

    activate_shader(&lightShader);
    apply_camera_matrix(lightShader, "camMatrix", &(cam.matrix));
    bind_VAO(&lightVAO);
    glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(typeof(lightIndices[0])), GL_UNSIGNED_INT, 0);
    
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

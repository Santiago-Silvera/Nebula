#include <stdio.h>
#include <cglm/cglm.h>

#include "mesh.h"
#include "logger.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void error_callback(int error, const char *desc);

vertex_t vertices[] ={
   //   COORDINATES    /       COLORS       /     NORMALS       /  TEXCOORD   //
   {{-1.0f, 0.0f,  1.0f},	  {0.0f, 0.0f, 0.0f},		{0.0f, 1.0f, 0.0f},   {0.0f, 0.0f}},	
   {{-1.0f, 0.0f, -1.0f},		{0.0f, 0.0f, 0.0f},		{0.0f, 1.0f, 0.0f},   {0.0f, 1.0f}},	
    {{1.0f, 0.0f, -1.0f},		{0.0f, 0.0f, 0.0f},		{0.0f, 1.0f, 0.0f},   {1.0f, 1.0f}},	
    {{1.0f, 0.0f,  1.0f},		{0.0f, 0.0f, 0.0f},		{0.0f, 1.0f, 0.0f},   {1.0f, 0.0f}},
 };

GLuint indices[] = {
	0, 1, 2,
	0, 2, 3
};

vertex_t lightVertices[] ={
   //     COORDINATES     //
	{{-0.1f, -0.1f,  0.1f}},
	{{-0.1f, -0.1f, -0.1f}},
	 {{0.1f, -0.1f, -0.1f}},
	 {{0.1f, -0.1f,  0.1f}},
	{{-0.1f,  0.1f,  0.1f}},
	{{-0.1f,  0.1f, -0.1f}},
	 {{0.1f,  0.1f, -0.1f}},
	 {{0.1f,  0.1f,  0.1f}}
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
  NINFO("Initializing rendering engine\n");
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "NEBULA Engine", NULL, NULL);
  if (window == NULL) {
    NFATAL("Failed to create GLFW window\n");
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
    NINFO("GLFW_CURSOR_DISABLED successfully set.\n");
  } else {
    NERROR("Failed to set GLFW_CURSOR_DISABLED, current mode: %d\n", mode);
  }

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    NFATAL("Failed to initialize GLAD\n");
    return -1;
  }

  // FLOOR
  SHADER_ID shader = create_shader_program("shaders/default.vert", "shaders/default.frag");

  texture_t texture = create_texture("resources/planks.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE);
  texture_t tex_spec = create_texture("resources/planksSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE);
  texture_t textures[] = {texture, tex_spec};

  mesh_t floor = create_mesh(vertices, sizeof(vertices)/sizeof(vertex_t), indices, sizeof(indices)/sizeof(GLuint), textures, sizeof(textures)/sizeof(texture_t));


  SHADER_ID lightShader = create_shader_program("shaders/light.vert", "shaders/light.frag");
  mesh_t light = create_mesh(lightVertices, sizeof(lightVertices)/sizeof(vertex_t), lightIndices, sizeof(lightIndices)/sizeof(GLuint), textures, sizeof(textures)/sizeof(texture_t));


  vec4 lightColor = {1.0f, 1.0f, 1.0f, 1.0f};
  vec3 lightPos = {0.0f, 2.0f, 0.0f};
  mat4 lightModel = GLM_MAT4_IDENTITY_INIT;
  glm_translate(lightModel, lightPos);

  vec3 objPos = {0.0f, 0.0f, 0.0f};
  mat4 objModel = GLM_MAT4_IDENTITY_INIT;
  glm_translate(objModel, objPos);

  activate_shader(&lightShader);
  glUniformMatrix4fv(glGetUniformLocation(lightShader, "model"), 1, GL_FALSE, (float *)lightModel);
  glUniform4f(glGetUniformLocation(lightShader, "lightColor"), lightColor[0], lightColor[1], lightColor[2], lightColor[3]);
  activate_shader(&shader);
  glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, (float *)objModel);
  glUniform4f(glGetUniformLocation(shader, "lightColor"), lightColor[0], lightColor[1], lightColor[2], lightColor[3]);
  glUniform3f(glGetUniformLocation(shader, "lightPos"), lightPos[0], lightPos[1], lightPos[2]);

  glEnable(GL_DEPTH_TEST);
  vec3 camPos = {0.0f, 0.0f, 1.0f};
  camera_t cam = create_camera(camPos, SCR_WIDTH, SCR_HEIGHT, 0.01f, 1.f);

  NINFO("====================================RENDERING LOOP====================================\n");
  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    inputs(window, &cam);
    update_camera_matrix(&cam, 45.0f, 0.1f, 100.0f);

    draw_mesh(&floor, shader, &cam);

    unbind_texture();

    draw_mesh(&light, lightShader, &cam);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  delete_VAO(&floor.VAO);
  delete_shader(&shader);
  delete_texture(&texture);
  glfwTerminate();

  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
void error_callback(int error, const char *desc) {
  NERROR("GLFW Error (%d): %s\n", error, desc);
}

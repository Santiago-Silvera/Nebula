#include "shader.h"
#include "stdio.h"
#include "stdlib.h"

// ChatGPT gave me this
const char *get_file_contents(const char *filename) {
  printf("Opening file %s", filename);
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Failed to open file %s\n");
    return NULL;
  }

  // Seek to the end to determine file size
  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  rewind(file); // Move back to the beginning of the file

  // Allocate memory (+1 for null terminator)
  char *buffer = (char *)malloc(file_size + 1);
  if (!buffer) {
    perror("Memory allocation failed");
    fclose(file);
    return NULL;
  }

  // Read file into buffer
  fread(buffer, 1, file_size, file);
  buffer[file_size] = '\0'; // Null-terminate the string

  fclose(file);
  return buffer;
}

SHADER_ID create_shader_program(const char *vertexPath,
                                const char *fragmentPath) {

  const char *vertexSource = get_file_contents(vertexPath);
  const char *fragmentSource = get_file_contents(fragmentPath);

  // We do this to keep track of a reference of the shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  // We assign the shader source
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  // And we compile the shader
  glCompileShader(vertexShader);

  // The same goes for the fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);

  // Shader program we will use in the rendering
  SHADER_ID shader_id = glCreateProgram();
  // Attach both shaders
  glAttachShader(shader_id, vertexShader);
  glAttachShader(shader_id, fragmentShader);
  // Link means to string them together. Basically closing the prep
  glLinkProgram(shader_id);

  // Safety
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  free((void *)vertexSource);
  free((void *)fragmentSource);

  return shader_id;
}

void activate_shader(SHADER_ID *shader) { glUseProgram(*shader); }
void delete_shader(SHADER_ID *shader) { glDeleteShader(*shader); }

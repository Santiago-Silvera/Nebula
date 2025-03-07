#include "shader.h"


// ChatGPT gave me this
char *get_file_contents(const char *filename) {
  NINFO("Opening file %s\n", filename);
  FILE *file = fopen(filename, "rb");  // Use binary mode for accuracy
  if (!file) {
      NERROR("Failed to open file");
      return NULL;
  }

  // Seek to the end to determine file size
  if (fseek(file, 0, SEEK_END) != 0) {
      NERROR("fseek failed");
      fclose(file);
      return NULL;
  }

  long file_size = ftell(file);
  if (file_size < 0) {
      NERROR("ftell failed");
      fclose(file);
      return NULL;
  }

  rewind(file);  // Move back to the beginning

  // Allocate memory (+1 for null terminator)
  char *buffer = (char *)malloc(file_size + 1);
  if (!buffer) {
      NERROR("Memory allocation failed");
      fclose(file);
      return NULL;
  }

  // Read file into buffer
  size_t bytes_read = fread(buffer, 1, file_size, file);
  if (bytes_read != file_size) {
      NERROR("fread error");
      free(buffer);
      fclose(file);
      return NULL;
  }
  buffer[file_size] = '\0';  // Null-terminate the string

  fclose(file);
  return buffer;
}


SHADER_ID create_shader_program(const char *vertexPath, const char *fragmentPath) {

  const char *vertexSource = get_file_contents(vertexPath);
  const char *fragmentSource = get_file_contents(fragmentPath);

  if (!vertexSource || !fragmentSource) {
    NERROR("Failed to read shader source\n");
    free((char *)vertexSource);
    free((char *)fragmentSource);
    return 0;
  }

  // We do this to keep track of a reference of the shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  // We assign the shader source
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  // And we compile the shader
  glCompileShader(vertexShader);
  // DEBUG: Check for compilation errors
  GLint success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
      glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
      NERROR("Vertex Shader Compilation Failed: %s\nFor filename: %s\n", infoLog, vertexPath);
  }

  // The same goes for the fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);
  // DEBUG: Check for compilation errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
      glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
      NERROR("Fragment Shader Compilation Failed: %s\nFor filename: %s\n", infoLog, fragmentPath);
  }

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
  free((char *)vertexSource);
  free((char *)fragmentSource);

  return shader_id;
}

void activate_shader(SHADER_ID *shader) {
    NTRACE("Activating shader: %d\n", *shader);
    glUseProgram(*shader); 
}
void delete_shader(SHADER_ID *shader) { glDeleteShader(*shader); }

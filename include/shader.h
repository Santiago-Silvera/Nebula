#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

// Shader program ID
typedef GLuint SHADER_ID;

// Create a shader program
SHADER_ID create_shader_program(const char *vertexPath,
                                const char *fragmentPath);
// Activate a shader program
void activate_shader(SHADER_ID *shader);
// Delet a shader program
void delete_shader(SHADER_ID *shader);

#endif // !SHADER_H

#ifndef TEXTURE_H
#define TEXTURE_H

#include "shader.h"
#include <glad/glad.h>

typedef struct {
  GLuint textureID;
  GLenum type;
} texture_t;

texture_t create_texture(const char *image, GLenum textureType, GLenum slot,
                         GLenum format, GLenum pixelType);
// Assigns a texture unit to a texture
void assign_texUnit(SHADER_ID *shader, const char *uniform, GLuint texUnit);
void bind_texture(texture_t *texture);
void unbind_texture(void);
void delete_texture(texture_t *texture);

#endif

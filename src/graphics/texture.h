#pragma once

#include "shader.h"
#include <stb_image.h>
#include <stdbool.h>
#include <stdio.h>
#include "logger.h"


typedef struct Texture {
  GLuint textureID;
  const char *type;
  GLuint slot;
} texture_t;

texture_t create_texture(const char *image, const char *textureType, GLenum slot, GLenum format, GLenum pixelType);
// Assigns a texture unit to a texture
void assign_texUnit(SHADER_ID *shader, const char *uniform, GLuint texUnit);
void bind_texture(texture_t *texture);
void unbind_texture(void);
void delete_texture(texture_t *texture);

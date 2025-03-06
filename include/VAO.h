#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>

#include "VBO.h"

typedef GLuint VAO_ID;

VAO_ID create_VAO(void);
void link_attrib(VAO_ID *VAO, VBO_ID *VBO, GLuint layout, GLuint numComponents,
                 GLenum type, GLsizeiptr stride, void *offset);
void bind_VAO(VAO_ID *VAO);
void unbind_VAO(void);
void delete_VAO(VAO_ID *VAO);

#endif // !VAO_H

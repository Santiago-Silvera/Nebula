#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>

typedef GLuint VBO_ID;

VBO_ID create_VBO(GLfloat *vertices, GLsizeiptr size);
void bind_VBO(VBO_ID *VBO);
void unbind_VBO(void);
void delete_VBO(VBO_ID *VBO);

#endif // !VBO_H

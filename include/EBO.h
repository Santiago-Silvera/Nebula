#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>
typedef GLuint EBO_ID;

EBO_ID create_EBO(GLuint *indices, GLsizeiptr size);
void bind_EBO(EBO_ID *EBO);
void unbind_EBO(void);
void delete_EBO(EBO_ID *EBO);

#endif

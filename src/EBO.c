#include "EBO.h"

EBO_ID create_EBO(GLuint *indices, GLsizeiptr size) {
  EBO_ID EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
  return EBO;
}

void bind_EBO(EBO_ID *EBO) { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO); }
void unbind_EBO(void) { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
void delete_EBO(EBO_ID *EBO) { glDeleteBuffers(1, EBO); }

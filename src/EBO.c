#include "EBO.h"

EBO_ID create_EBO(GLuint *indices, GLsizeiptr size) {
  printf("Creating EBO\n");
  EBO_ID EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
  printf("Created EBO: %d\n", EBO);
  return EBO;
}

void bind_EBO(EBO_ID *EBO) {
  printf("Binding EBO: %d\n", *EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO); 
}
void unbind_EBO(void) { 
  printf("Unbinding EBO\n");
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
}
void delete_EBO(EBO_ID *EBO) {
  printf("Deleting EBO: %d\n", *EBO);
  glDeleteBuffers(1, EBO); 
}

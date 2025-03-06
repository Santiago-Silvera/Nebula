#include "VBO.h"

VBO_ID create_VBO(vertex_t *vertices, GLsizeiptr size) {
  printf("Creating VBO\n");
  VBO_ID VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  printf("Created VBO: %d\n", VBO);
  return VBO;
}
void bind_VBO(VBO_ID *VBO) { 
  printf("Binding VBO: %d\n", *VBO);
  glBindBuffer(GL_ARRAY_BUFFER, *VBO); 
}
void unbind_VBO(void) { 
  printf("Unbinding VBO\n");
  glBindBuffer(GL_ARRAY_BUFFER, 0); 
}
void delete_VBO(VBO_ID *VBO) { 
  printf("Deleting VBO: %d\n", *VBO);
  glDeleteBuffers(1, VBO); 
}

#include "VBO.h"

VBO_ID create_VBO(GLfloat *vertices, GLsizeiptr size) {
  VBO_ID VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  return VBO;
}
void bind_VBO(VBO_ID *VBO) { glBindBuffer(GL_ARRAY_BUFFER, *VBO); }
void unbind_VBO(void) { glBindBuffer(GL_ARRAY_BUFFER, 0); }
void delete_VBO(VBO_ID *VBO) { glDeleteBuffers(1, VBO); }

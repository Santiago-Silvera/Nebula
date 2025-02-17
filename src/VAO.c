#include "VAO.h"
#include "VBO.h"

VAO_ID create_VAO(void) {
  VAO_ID VAO;
  glGenVertexArrays(1, &VAO);
  return VAO;
}

void link_attrib(VAO_ID *VAO, VBO_ID *VBO, GLuint layout, GLuint numComponents,
                 GLenum type, GLsizeiptr stride, void *offset) {
  // bind VBO
  bind_VBO(VBO);

  glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
  glEnableVertexAttribArray(layout);

  // unbind VBO
  unbind_VBO();
}

void bind_VAO(VAO_ID *VAO) { glBindVertexArray(*VAO); }
void unbind_VAO(void) { glBindVertexArray(0); }
void delete_VAO(VAO_ID *VAO) { glDeleteVertexArrays(1, VAO); }

#include "VAO.h"

VAO_ID create_VAO(void) {
  NINFO("Creating VAO\n");
  VAO_ID VAO;
  glGenVertexArrays(1, &VAO);
  NTRACE("Created VAO: %d\n", VAO);
  return VAO;
}

void link_attrib(VAO_ID *VAO, VBO_ID *VBO, GLuint layout, GLuint numComponents,
                 GLenum type, GLsizeiptr stride, void *offset) {
  NINFO("Linking attribute for VAO: %d VBO: %d layout: %d\n", *VAO, *VBO, layout);
  // bind VBO
  bind_VBO(VBO);

  glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
  glEnableVertexAttribArray(layout);

  // unbind VBO
  unbind_VBO();
}

void bind_VAO(VAO_ID *VAO) { 
  NTRACE("Binding VAO: %d\n", *VAO);
  glBindVertexArray(*VAO); 
}
void unbind_VAO(void) { 
  NTRACE("Unbinding VAO\n");
  glBindVertexArray(0); 
}
void delete_VAO(VAO_ID *VAO) { 
  NTRACE("Deleting VAO: %d\n", *VAO);
  glDeleteVertexArrays(1, VAO); 
}

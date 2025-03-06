#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>
#include <cglm/cglm.h>

typedef struct Vertex {
    vec3 position;
    vec3 color;
    vec3 normal;
    vec2 texCoord;
} vertex_t;

typedef GLuint VBO_ID;

VBO_ID create_VBO(vertex_t *vertices, GLsizeiptr size);
void bind_VBO(VBO_ID *VBO);
void unbind_VBO(void);
void delete_VBO(VBO_ID *VBO);

#endif // !VBO_H

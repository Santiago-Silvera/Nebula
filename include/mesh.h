#ifndef MESH_H
#define MESH_H

#include "VAO.h"
#include "EBO.h"
#include "camera.h"
#include "texture.h"



typedef struct Mesh {
    vertex_t *vertices;
    int vertices_count;
    GLuint *indices;
    int indices_count;
    texture_t *textures;
    int textures_count;
    VAO_ID VAO;
} mesh_t;

mesh_t create_mesh( vertex_t *vertices, int vertices_count, 
                    GLuint *indices, int indices_count, 
                    texture_t *textures, int textures_count);
void draw_mesh(mesh_t *mesh, SHADER_ID shader, camera_t *camera);



#endif // MESH_H
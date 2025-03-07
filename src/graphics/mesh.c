#include "mesh.h"
#include <string.h>

mesh_t create_mesh( vertex_t *vertices, int vertices_count, 
                    GLuint *indices, int indices_count, 
                    texture_t *textures, int textures_count) {
        NINFO("Creating mesh\n");
        mesh_t mesh = {
            .vertices = vertices,
            .vertices_count = vertices_count,
            .indices = indices,
            .indices_count = indices_count,
            .textures = textures,
            .textures_count = textures_count,
            .VAO = create_VAO()
        };
        bind_VAO(&mesh.VAO);
        VBO_ID VBO = create_VBO(mesh.vertices, sizeof(vertex_t) * mesh.vertices_count);
        EBO_ID EBO = create_EBO(mesh.indices, sizeof(GLuint) * mesh.indices_count);
        link_attrib(&mesh.VAO, &VBO, 0, 3, GL_FLOAT, sizeof(vertex_t), (void *)(0));
        link_attrib(&mesh.VAO, &VBO, 1, 3, GL_FLOAT, sizeof(vertex_t), (void *)(3 * sizeof(float)));
        link_attrib(&mesh.VAO, &VBO, 2, 3, GL_FLOAT, sizeof(vertex_t), (void *)(6 * sizeof(float)));
        link_attrib(&mesh.VAO, &VBO, 3, 2, GL_FLOAT, sizeof(vertex_t), (void *)(9 * sizeof(float)));

        unbind_VAO();
        unbind_VBO();
        unbind_EBO();
        return mesh;
    }
void draw_mesh(mesh_t *mesh, SHADER_ID shader, camera_t *camera) {
    activate_shader(&shader);
    bind_VAO(&(mesh->VAO));

    // Keep track of how many of each type of textures we have
	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;
    // Bind the textures
    for (unsigned int i = 0; i < mesh->textures_count; i++)
	{
		char *num;
        char uniformName[64];
		const char *type = mesh->textures[i].type;
		if (strcmp(type, "diffuse") == 0)
		{
            num = malloc(10); // 10 is enough for an int
            if (!num) return;
            sprintf(num, "%d", numDiffuse++);
		}
		else if (strcmp(type, "specular") == 0)
		{
            num = malloc(10);
            if (!num) return;
            sprintf(num, "%d", numSpecular++);
		}
        sprintf(uniformName, "%s%s", type, num);
        assign_texUnit(&shader, uniformName, i);
		mesh->textures[i];
		bind_texture(&(mesh->textures[i]));
        free(num);
	}
    glUniform3f(glGetUniformLocation(shader, "camPos"), camera->position[0], camera->position[1], camera->position[2]);
	apply_camera_matrix(shader, "camMatrix", &(camera->matrix));

	// Draw the actual mesh
    NTRACE("Drawing mesh\n");
	glDrawElements(GL_TRIANGLES, mesh->indices_count, GL_UNSIGNED_INT, 0);
}
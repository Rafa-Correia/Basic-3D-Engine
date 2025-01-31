#ifndef MESH_HPP
#define MESH_HPP
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "shader.hpp"

using std::vector;
using std::string;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    string type;
};

class Mesh {
    public:
        vector<Vertex>              vertices;
        vector<unsigned int>        indices;
        vector<Texture>             textures;

        Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
        void Draw(Shader &shader);

    private:
        unsigned int VAO, VBO, EBO;

        void setupMesh();
};

#endif
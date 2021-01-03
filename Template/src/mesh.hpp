#ifndef MESH_HPP
#define MESH_HPP

#include <glimac/glm.hpp>
#include <glimac/Program.hpp>

#include <string>
#include <vector>

using namespace std;

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    string type;
    string path;
};

class Mesh {
public:
    // mesh Data
    vector<Vertex>       mVertices;
    vector<unsigned int> mIndices;
    vector<Texture>      mTextures;
    unsigned int VAO, VBO, IBO;

    // constructor
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
    {
        this->mVertices = vertices;
        this->mIndices = indices;
        this->mTextures = textures;

        // now that we have all the required data, set the vertex buffers and its attribute pointers.
        setupMesh();
    }

    // render the mesh
    void Draw(glimac::Program &program);

private:
    // render data 
    // unsigned int VBO, IBO;

    // initializes all the buffer objects/arrays
    void setupMesh();
};
#endif


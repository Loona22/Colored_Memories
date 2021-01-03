#ifndef MODEL_HPP
#define MODEL_HPP

#include "mesh.hpp"

#include <GL/glew.h>
#include <iostream> 
#include <string>
#include <vector>

#include <glimac/glm.hpp>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


using namespace std;

unsigned int TextureFromFile(const char *path);

class Model{
    public:
        // model data 
        vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
        vector<Mesh>    meshes;
        string directory;

        // constructor, expects a filepath to a 3D model.
        Model(const string &path)
        {
            loadModel(path);
        }

        // draws the model, and thus all its meshes
        void Draw(glimac::Program &program);
        
    private:
        // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
        void loadModel(const string &path);

        // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
        void processNode(aiNode *node, const aiScene *scene);

        Mesh processMesh(aiMesh *mesh, const aiScene *scene);

        vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
        
};

#endif


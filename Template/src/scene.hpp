#ifndef SCENE_HPP
#define SCENE_HPP

#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/glm.hpp>
#include <string>
#include <vector>

#include "structures.hpp"
#include "model.hpp"

class Scene{
    private :
        std::string monde_intro = "../Template/assets/models/intro/scene_intro.obj";
        std::string monde_rouge = "../Template/assets/models/rouge/rougelighter1.obj";
        std::string monde_bleu  = "../Template/assets/models/bleu/bleutest.obj";
        std::vector<Model> objets;

        char* musique_mondeRouge = (char*) "../Template/assets/musique/musique_rouge.wav";
        char* musique_mondeBleu = (char*) "../Template/assets/musique/musique_bleu.wav";
        std::vector<Mix_Chunk*> musiques ;
        char* bruit_collision = (char*) "../Template/assets/musique/choc.wav";
        std::vector<Mix_Chunk*> bruitages ;

        char* voix_intro = (char*) "../Template/assets/musique/intro.wav";
        char* voix_outro = (char*) "../Template/assets/musique/outro.wav";

        void loadScene(std::string &path);

    public :
        Scene(std::string &path){
            loadScene(path);
        }
        ~Scene() = default;

        void drawMyScene(ObjetProgram &program);

        void mixMyScene(std::string &path);

};

#endif
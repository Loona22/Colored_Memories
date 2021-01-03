#include "scene.hpp"
#include "stdio.h"
#include "stdlib.h"

// Comparaison entre path et les différentes string pour déterminer le monde auquel elle apprtient
// définition des différentes variables en fonction de leur type :
// Model, Mix_Chunk*
// Gestion des erreur si les pointeur Mix_chunk* sont nuls
void Scene::loadScene(std::string &path){
    std::string introStr ("intro");
    std::string monde_rougeStr ("monde_rouge");
    std::string monde_bleuStr ("monde_bleu");
    std::string outroStr ("outro");

    if(path.compare(introStr)==0){
        Model introModel(this->monde_intro);
        this->objets.push_back(introModel);

        Mix_AllocateChannels(10);
        
        Mix_Chunk *introMusique;
        introMusique = Mix_LoadWAV(this->voix_intro);
        this->musiques.push_back(introMusique);
        
        if(introMusique == NULL){
            std::cout << "Erreur introMusique" << Mix_GetError() << std::endl;
        }
    }
    else if(path.compare(monde_rougeStr)==0){
        Model monde_rougeModel(this->monde_rouge);
        this->objets.push_back(monde_rougeModel);

        Mix_AllocateChannels(10);
        
        Mix_Chunk *monde_rougeMusique;
        monde_rougeMusique = Mix_LoadWAV(this->musique_mondeRouge);
        this->musiques.push_back(monde_rougeMusique);
        Mix_Chunk *collisionBruitage;
        collisionBruitage = Mix_LoadWAV(this->bruit_collision);
        this->bruitages.push_back(collisionBruitage);
        
        if(monde_rougeMusique == NULL){
            std::cout << "Erreur monde_rougeMusique" << Mix_GetError() << std::endl;
        }
        if(collisionBruitage == NULL){
            std::cout << "Erreur  collisionBruitage" << Mix_GetError() << std::endl;
        }
    }else if(path.compare(monde_bleuStr)==0){
        Model monde_bleuModel(this->monde_bleu);
        this->objets.push_back(monde_bleuModel);

        Mix_AllocateChannels(10);
        
        Mix_Chunk *monde_bleuMusique;
        monde_bleuMusique = Mix_LoadWAV(this->musique_mondeBleu);
        this->musiques.push_back(monde_bleuMusique);
        Mix_Chunk *collisionBruitage;
        collisionBruitage = Mix_LoadWAV(this->bruit_collision);
        this->bruitages.push_back(collisionBruitage);
        
        if(monde_bleuMusique == NULL){
            std::cout << "Erreur monde_bleuMusique" << Mix_GetError() << std::endl;
        }
        if(collisionBruitage == NULL){
            std::cout << "Erreur  collisionBruitage" << Mix_GetError() << std::endl;
        }
    }else if(path.compare(outroStr)==0){
        Model outroModel(this->monde_intro);
        this->objets.push_back(outroModel);

        Mix_AllocateChannels(10);
        
        Mix_Chunk *outroMusique;
        outroMusique = Mix_LoadWAV(this->voix_outro);
        this->musiques.push_back(outroMusique);
        
        if(outroMusique == NULL){
            std::cout << "Erreur outroMusique" << Mix_GetError() << std::endl;
        }
    }
    else{
        std::cout << "Erreur loadScene" << std::endl;
    }
}

// Pour chaque éléments de objets on appelle la méthode Draw de la class Model
void Scene::drawMyScene(ObjetProgram &program){
    for(int i=0 ; i< objets.size(); i++){
        objets[i].Draw(program.m_Program);
    }

}

// permet de jouer la bonne musique en fonction de la scène
void Scene::mixMyScene(std::string &path){
    std::string ambiance ("ambiance");
    std::string choc ("choc");
    std::string intro ("intro");
    std::string outro ("outro");

    //compare l'entrée path à intro pour savoir si c'est les musiques appartenant à intro qu'il faut joueur
    if(path.compare(intro) == 0){
        for(int nbMusiques = 0 ; nbMusiques < musiques.size(); nbMusiques++){
            Mix_PlayChannel(0, musiques[nbMusiques], 0);
        }
    }
    //compare l'entrée path à ambiance pour savoir si c'est les musiques appartenant à ambiance qu'il faut joueur
    if(path.compare(ambiance) == 0){
        for(int nbMusiques = 0 ; nbMusiques < musiques.size(); nbMusiques++){
            Mix_VolumeChunk(musiques[nbMusiques], MIX_MAX_VOLUME/4);
            Mix_PlayChannel(0, musiques[nbMusiques], -1);
        }
    }
    //compare l'entrée path à choc pour savoir si c'est les bruitages appartenant à choc qu'il faut joueur
    if(path.compare(choc) == 0){
        for(int nbBruitages = 0 ; nbBruitages < bruitages.size(); nbBruitages++){
            Mix_PlayChannel(1, bruitages[nbBruitages], 0);
        }
    }
    //compare l'entrée path à outro pour savoir si c'est les musiques appartenant à outro qu'il faut joueur
    if(path.compare(outro) == 0){
        for(int nbMusiques = 0 ; nbMusiques < musiques.size(); nbMusiques++){
            Mix_PlayChannel(0, musiques[nbMusiques], 0);
        }
    }
}
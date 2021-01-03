#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <vector>

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/glm.hpp>
#include "glimac/Image.hpp"
#include "glimac/FreeflyCamera.hpp"

#include "lumieres.hpp"
#include "tresor.hpp"
#include "model.hpp"
#include "collisions.hpp"
#include "scene.hpp"
#include "game.hpp"

using namespace glimac;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "COLORED MEMORIES");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    FilePath applicationPath(argv[0]);
    ObjetProgram ObjProgram(applicationPath);
    TresorProgram tresorProgram(applicationPath);

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    glEnable(GL_DEPTH_TEST);

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    /***********
    Initilisation scene
    **********/

    initilisationTresor(tresorProgram);

    std::string intro1 ("intro");
    Scene intro(intro1);

    std::string _scene1 ("monde_rouge");
    Scene scene(_scene1);
    std::string _scene2 = "monde_bleu";
    Scene scene2(_scene2);

    std::vector<Scene> scenes = {scene, scene2};

    std::string outro1 ("outro");
    Scene outro(outro1);

    //initialisation du jeu
    Game game(1, 0, 0, 0);

    //initialise la positions des portails (cubes) et de leur couleur
    glm::vec3 cube_rouge = glm::vec3( 4.5f, 0.5f, 6.5f);
    glm::vec3 cube_bleu= glm::vec3( -6.1f, 0.5f, -3.4f);
    std::vector<glm::vec3> cubes = {cube_rouge, cube_bleu};

    //initialisation de la couleur de cubes
    glm::vec3 rouge = glm::vec3( 1.0f, 0.f, 0.f);
    glm::vec3 bleu = glm::vec3( 0.f, 0.f, 1.0f);
    std::vector<glm::vec3> couleurs = {rouge, bleu};

    /***********
    Initilisation musique
    **********/
    std::string voixIntro("intro");
    std::string ambiance("ambiance");
    std::string choc("choc");
    std::string voixOutro("outro");
    bool declencheAmbiance = false;

    //Joue le son correspondant à la première scène
    intro.mixMyScene(voixIntro);

    // Déclaration de matrices
    glm::mat4 ViewMatrix;
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 800.0f/800.0f, 0.1f, 100.f);
    glm::mat4 MVMatrix = glm::translate(glm::mat4(1.f) , glm::vec3(0., 0. , -5.));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
    glm::mat4 MVPMatrix = ProjMatrix*MVMatrix;

    //création de la trackballCamera
    FreeflyCamera camera;

    //bool qui permet de jouer le son de la dernière scène
    bool fin = true;

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

        if (game.getIntro() == 1) {
            // couleur de fond
            glClearColor(0.1, 0.1, 0.1, 0.);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            ViewMatrix = camera.getViewMatrix();
            MVMatrix = glm::mat4(1.f) * ViewMatrix;
            NormalMatrix = glm::transpose(glm::inverse(MVMatrix)); 
            MVPMatrix = ProjMatrix*MVMatrix;

            ObjProgram.m_Program.use();

            // lumières
            gestionLumiereObj(ObjProgram, ViewMatrix, camera);

            //MVMatrix = glm::rotate(MVMatrix, glm::radians(windowManager.getTime()*100), glm::vec3(0., 2., 0.));
            glUniformMatrix4fv(ObjProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
            glUniformMatrix4fv(ObjProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
            glUniformMatrix4fv(ObjProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(MVPMatrix));

            //appel de la méthode de la class scene pour afficher la scène demandée
            //ObjProgram pour gérer les lumières
            intro.drawMyScene(ObjProgram);

            //appuyer sur entrée pour lancer le jeu
            if (windowManager.isKeyPressed(SDLK_RETURN)==true) {
                game.setPlay(1);   //lance le jeu et quitte l'intro
                game.setIntro(0);
                declencheAmbiance = true;
            }
        }

        if (game.getPlay() == 1) {
            // Gestion des entrées utilisateurs
            //utilisation de checkCollision pour savoir si on doit changer de monde ou pas et jouer bruitage choc
            if(windowManager.isKeyPressed(SDLK_d)==true){
                if (CheckCollision(cubes[game.getScene()], camera.getPosCamera().x, camera.getPosCamera().y, camera.getPosCamera().z) == true) {
                    scene.mixMyScene(choc);
                }if (CheckCollision(cubes[game.getScene()], camera.getPosCamera().x, camera.getPosCamera().y, camera.getPosCamera().z) == false) {
                    camera.moveLeft(-0.1);
                }else {
                        game.setPlay(0);
                    }
            }
            if(windowManager.isKeyPressed(SDLK_q)==true){
                if (CheckCollision(cubes[game.getScene()], camera.getPosCamera().x, camera.getPosCamera().y, camera.getPosCamera().z) == true) {
                    scene.mixMyScene(choc);
                }
                if (CheckCollision(cubes[game.getScene()], camera.getPosCamera().x, camera.getPosCamera().y, camera.getPosCamera().z) == false) {
                    camera.moveLeft(0.1);
                }else {
                        game.setPlay(0);
                    }
            }
            if(windowManager.isKeyPressed(SDLK_z)==true){
                if(CheckCollision(cubes[game.getScene()], camera.getPosCamera().x, camera.getPosCamera().y, camera.getPosCamera().z) == true) {
                    scene.mixMyScene(choc);
                }if (CheckCollision(cubes[game.getScene()], camera.getPosCamera().x, camera.getPosCamera().y, camera.getPosCamera().z) == false) {
                    camera.moveFront(0.1);
                }else {
                        game.setPlay(0);
                    }
            }
            if(windowManager.isKeyPressed(SDLK_s)==true){
                if (CheckCollision(cubes[game.getScene()], camera.getPosCamera().x, camera.getPosCamera().y, camera.getPosCamera().z) == true) {
                    scene.mixMyScene(choc);
                }if (CheckCollision(cubes[game.getScene()], camera.getPosCamera().x, camera.getPosCamera().y, camera.getPosCamera().z) == false) {
                    camera.moveFront(-0.1);
                }else {
                        game.setPlay(0);
                    }
            }
            if(windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)==true){
                camera.rotateLeft(-(windowManager.getMousePosition().x - 400 )/100);
                camera.rotateUp(-(windowManager.getMousePosition().y - 300)/75);
            }

            /*********************************
            * HERE SHOULD COME THE RENDERING CODE
            *********************************/
          
            // couleur de fond
            glClearColor(0.1, 0.1, 0.1, 0.);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //Gestion ambiance sonore
            if(declencheAmbiance == true){
                scenes[game.getScene()].mixMyScene(ambiance);
            }
            declencheAmbiance = false;
            
            ViewMatrix = camera.getViewMatrix();
            MVMatrix = glm::mat4(1.f) * ViewMatrix;
            NormalMatrix = glm::transpose(glm::inverse(MVMatrix)); 
            MVPMatrix = ProjMatrix*MVMatrix;

            //Dessin du cube portail
            DrawTresor(tresorProgram, camera, couleurs[game.getScene()], MVMatrix, ProjMatrix, cubes[game.getScene()]);
            //Appel du programe pour gérer les couleurs et affichages de la scène
            ObjProgram.m_Program.use();

            // lumières
            gestionLumiereObj(ObjProgram, ViewMatrix, camera);

            glUniformMatrix4fv(ObjProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
            glUniformMatrix4fv(ObjProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
            glUniformMatrix4fv(ObjProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(MVPMatrix));

            scenes[game.getScene()].drawMyScene(ObjProgram);
            
        }

        if (game.getPlay() == 0 && game.getIntro() == 0 ) {
            glClearColor(0., 0., 0., 0.);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            if (game.getScene() == 0) {
                if (windowManager.isKeyPressed(SDLK_RETURN)==true) { 
                    //enclenche la scène suivante
                    game.setScene(1);
                    game.setPlay(1);
                    declencheAmbiance = true;
                }
            }else{
                //si on est dans le monde 2, lance la fin du jeu
                game.setEnd(1);
                //permet de changer de son
                if(fin == true){
                    declencheAmbiance = true;
                }
                fin = false;
            }
        }

        if (game.getEnd() == 1){

            // couleur de fond
            glClearColor(0.1, 0.1, 0.1, 0.);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //Gestion ambiance sonore
            if(declencheAmbiance == true){
                outro.mixMyScene(voixOutro);
            }
            declencheAmbiance = false;

            ViewMatrix = camera.getViewMatrix();
            MVMatrix = glm::mat4(1.f) * ViewMatrix;
            NormalMatrix = glm::transpose(glm::inverse(MVMatrix)); 
            MVPMatrix = ProjMatrix*MVMatrix;

            ObjProgram.m_Program.use();

            // lumières
            gestionLumiereObj(ObjProgram, ViewMatrix, camera);

            glUniformMatrix4fv(ObjProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
            glUniformMatrix4fv(ObjProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
            glUniformMatrix4fv(ObjProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(MVPMatrix));
            intro.drawMyScene(ObjProgram);

            //fin du jeu, appuyer sur entrer pour quitter
            if (windowManager.isKeyPressed(SDLK_RETURN)==true) {
                done = true;
            }
        }

        // Update the display
        windowManager.swapBuffers();

        SDL_Delay(20);
    }

    debindCube(tresorProgram);
    Mix_CloseAudio();
    return EXIT_SUCCESS;
}
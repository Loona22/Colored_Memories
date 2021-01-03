#ifndef GAME_HPP
#define GAME_HPP

#include <GL/glew.h>
#include <iostream>
#include <SDL/SDL.h>
#include <glimac/glm.hpp>


class Game {

    private:

        bool intro;
        bool play;
        bool end;
        bool scene;


    public:

        Game(bool _intro, bool _play, bool _end, bool _scene) :
            intro(_intro), play(_play), end(_end), scene(_scene) {}

        ~Game() = default;

        inline bool getIntro() {
            return intro;
        }

        inline bool getPlay() {
            return play;
        }

        inline bool getEnd() {
            return end;
        }

        inline bool getScene() {
            return scene;
        }

        inline void setIntro(bool new_intro) {
            intro = new_intro;
        }

        inline void setPlay(bool new_play) {
            play = new_play;
        }

        inline void setEnd(bool new_end) {
            end = new_end;
        }

        inline void setScene(bool new_scene) {
            scene = new_scene;
        }


};


#endif 
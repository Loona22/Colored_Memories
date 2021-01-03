#ifndef LUMIERE_HPP
#define LUMIERE_HPP

#include <GL/glew.h>
#include <iostream>
#include <SDL/SDL.h>
#include <glimac/glm.hpp>
#include <glimac/Program.hpp>

#include "structures.hpp"
#include "tresor.hpp"

// permet de gérer les lumières en fonction du programme donc des shaders
// besoin de ViewMatrix et de camera pour un affichage correcte
void gestionLumiereObj(ObjetProgram &ObjProgram, glm::mat4 ViewMatrix, glimac::FreeflyCamera camera);

void gestionLumiereTresor(TresorProgram &tresorProgram, glimac::FreeflyCamera camera);

#endif
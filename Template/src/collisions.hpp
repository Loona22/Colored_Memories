#ifndef COLLISIONS_HPP
#define COLLISIONS_HPP

#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <SDL/SDL.h>
#include <glimac/glm.hpp>
#include "glimac/FreeflyCamera.hpp"
#include <glimac/Program.hpp>

#include "tresor.hpp"

using namespace glimac;

//gestion des collisions
// cubePositions pour récupérer la position du cube
// float x, y, z pour comparer avec la position du cube
// retourne vrai ou faux pour savoir quanc il y a collision
bool CheckCollision(glm::vec3 cubePositions, float x, float y, float z);

#endif
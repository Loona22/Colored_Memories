#include "collisions.hpp"

// Gestion des collisions
// cubePositions pour récupérer la position du cube
// float x, y, z pour comparer avec la position du cube
bool CheckCollision(glm::vec3 cubePositions, float x, float y, float z) {
    if ((cubePositions.x - 0.5 <= x + 0.5 && x - 0.5 <= cubePositions.x + 0.5) && (cubePositions.y - 0.5 <= y + 0.5 && y - 0.5 <= cubePositions.y + 0.5) && (cubePositions.z - 0.5 <= z + 0.5 && z - 0.5 <= cubePositions.z + 0.5)) {
        return true;
    } else {
        return false;
    }
}
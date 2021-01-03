#include "lumieres.hpp"

// permet de gérer les lumières en fonction du programme donc des shaders
// besoin de ViewMatrix et de camera pour un affichage correcte
void gestionLumiereObj(ObjetProgram &ObjProgram, glm::mat4 ViewMatrix, glimac::FreeflyCamera camera){
        glm::vec4 lightDir(1., 1., 1., 0.);
        lightDir = lightDir * ViewMatrix;
        glUniform3f(ObjProgram.uDirlightDir, lightDir.x, lightDir.y, lightDir.z);
        glUniform3f(ObjProgram.uViewPos, camera.getPosCamera().x, camera.getPosCamera().y, camera.getPosCamera().z);

        glUniform3f(ObjProgram.uDirlightAmbient, 0.2, 0.2, 0.2);
        glUniform3f(ObjProgram.uDirlightDiffuse, 0.5, 0.5, 0.5);
        glUniform3f(ObjProgram.uDirlightSpecular, 1., 1., 1.);

        //Spotlight
        glUniform3f(ObjProgram.uSpotlightPosition, camera.getPosCamera().x, camera.getPosCamera().y, camera.getPosCamera().z);
        glUniform3f(ObjProgram.uSpotlightDir, camera.getDirCamera().x, camera.getDirCamera().y, camera.getDirCamera().z);
        glUniform3f(ObjProgram.uSpotlightAmbient, 0.05, 0.05, 0.05);
        glUniform3f(ObjProgram.uSpotlightDiffuse, 0.8, 0.8, 0.8);
        glUniform3f(ObjProgram.uSpotlightSpecular, 1., 1., 1.);
        glUniform1f(ObjProgram.uSpotlightConstant, 1.0);
        glUniform1f(ObjProgram.uSpotlightLinear, 1.0);
        glUniform1f(ObjProgram.uSpotlightQuadric, 1.0);
        glUniform1f(ObjProgram.uSpotlightCutOff, glm::cos(glm::radians(12.5)));
        glUniform1f(ObjProgram.uSpotlightOuterCutOff, glm::cos(glm::radians(15.0)));

        glUniform3f(ObjProgram.uMatSpecular, 0.5, 0.5, 0.5);
        glUniform1f(ObjProgram.uMatShininess, 32.);
}

void gestionLumiereTresor(TresorProgram &tresorProgram, glimac::FreeflyCamera camera){

    glm::vec4 lightDir(1., 1., 1., 0.);
    lightDir = lightDir * camera.getViewMatrix();
    glUniform3f(tresorProgram.uDirlightDir, lightDir.x, lightDir.y, lightDir.z);
    glUniform3f(tresorProgram.uViewPos, camera.getPosCamera().x, camera.getPosCamera().y, camera.getPosCamera().z);

    glUniform3f(tresorProgram.uDirlightAmbient, 0.5, 0.5, 0.5);
    glUniform3f(tresorProgram.uDirlightDiffuse, 0.5, 0.5, 0.5);
    glUniform3f(tresorProgram.uDirlightSpecular, 1., 1., 1.);

    //Spotlight
    glUniform3f(tresorProgram.uSpotlightPosition, camera.getPosCamera().x, camera.getPosCamera().y, camera.getPosCamera().z);
    glUniform3f(tresorProgram.uSpotlightDir, camera.getDirCamera().x, camera.getDirCamera().y, camera.getDirCamera().z);
    glUniform3f(tresorProgram.uSpotlightAmbient, 0.2, 0.2, 0.2);
    glUniform3f(tresorProgram.uSpotlightDiffuse, 0.8, 0.8, 0.8);
    glUniform3f(tresorProgram.uSpotlightSpecular, 1., 1., 1.);
    glUniform1f(tresorProgram.uSpotlightConstant, 1.0);
    glUniform1f(tresorProgram.uSpotlightLinear, 1.0);
    glUniform1f(tresorProgram.uSpotlightQuadric, 1.0);
    glUniform1f(tresorProgram.uSpotlightCutOff, glm::cos(glm::radians(12.5)));
    glUniform1f(tresorProgram.uSpotlightOuterCutOff, glm::cos(glm::radians(15.0)));

    glUniform3f(tresorProgram.uMatAmbient, 1., 0.5, 0.5);
    glUniform3f(tresorProgram.uMatDiffuse, 1., 0.5, 0.5);
    glUniform3f(tresorProgram.uMatSpecular, 0.5, 0.5, 0.5);
    glUniform1f(tresorProgram.uMatShininess, 32.);
}
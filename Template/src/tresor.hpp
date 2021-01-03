#ifndef TRESOR_HPP
#define TRESOR_HPP

#include <GL/glew.h>
#include <iostream>
#include <SDL/SDL.h>
#include <glimac/glm.hpp>
#include "glimac/FreeflyCamera.hpp"
#include <glimac/Program.hpp>

using namespace glimac;

// permet de regrouper les informations relatives aux shader tresorShader.fs.glsl et tresorShader.vs.glsl 
struct TresorProgram {

    GLuint vbo;
    GLuint vao;

    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;

    GLint uDirlightDir;
    GLint uDirlightAmbient;
    GLint uDirlightDiffuse;
    GLint uDirlightSpecular;

    GLint uSpotlightDir;
    GLint uSpotlightPosition;
    GLint uSpotlightAmbient;
    GLint uSpotlightDiffuse;
    GLint uSpotlightSpecular;
    GLint uSpotlightConstant;
    GLint uSpotlightLinear;
    GLint uSpotlightQuadric;
    GLint uSpotlightCutOff;
    GLint uSpotlightOuterCutOff;

    GLint uMatAmbient;
    GLint uMatSpecular;
    GLint uMatShininess;
    GLint uMatDiffuse;

    GLint uViewPos;

    TresorProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/tresorShader.vs.glsl",
                                applicationPath.dirPath() + "shaders/tresorShader.fs.glsl")){
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(m_Program.getGLId(), "uObjColor");

        uDirlightDir = glGetUniformLocation(m_Program.getGLId(), "dirlight.direction");
        uDirlightAmbient = glGetUniformLocation(m_Program.getGLId(), "dirlight.ambient");
        uDirlightDiffuse = glGetUniformLocation(m_Program.getGLId(), "dirlight.diffuse");
        uDirlightSpecular = glGetUniformLocation(m_Program.getGLId(), "dirlight.specular");

        uSpotlightDir = glGetUniformLocation(m_Program.getGLId(), "spotlight.direction");
        uSpotlightAmbient = glGetUniformLocation(m_Program.getGLId(), "spotlight.ambient");
        uSpotlightDiffuse = glGetUniformLocation(m_Program.getGLId(), "spotlight.diffuse");
        uSpotlightSpecular = glGetUniformLocation(m_Program.getGLId(), "spotlight.specular");
        uSpotlightConstant = glGetUniformLocation(m_Program.getGLId(), "spotlight.constant");
        uSpotlightLinear = glGetUniformLocation(m_Program.getGLId(), "spotlight.linear");
        uSpotlightQuadric = glGetUniformLocation(m_Program.getGLId(), "spotlight.dquadric");
        uSpotlightCutOff = glGetUniformLocation(m_Program.getGLId(), "spotlight.cutOff");
        uSpotlightOuterCutOff = glGetUniformLocation(m_Program.getGLId(), "spotlight.outerCutOff");

        uMatAmbient = glGetUniformLocation(m_Program.getGLId(), "material.ambient");
        uMatSpecular = glGetUniformLocation(m_Program.getGLId(), "material.specular");
        uMatShininess = glGetUniformLocation(m_Program.getGLId(), "material.shininess");
        uMatDiffuse = glGetUniformLocation(m_Program.getGLId(), "material.diffuse");

        uViewPos = glGetUniformLocation(m_Program.getGLId(), "viewPos");

        }
};

void initilisationTresor(TresorProgram &tresorProgram);

void DrawTresor(TresorProgram &tresorProgram, glimac::FreeflyCamera camera, glm::vec3 color, glm::mat4 MVMatrix, glm::mat4 ProjMatrix, glm::vec3 cubePositions);

void debindCube(TresorProgram &tresorProgram);

#endif
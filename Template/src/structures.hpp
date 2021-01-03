#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include "glimac/Image.hpp"

using namespace glimac;

// permet de regrouper les informations relatives aux sahder lightShader.vs.glsl et multipleLights.fs.glsl
struct ObjetProgram {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;

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

    GLint uMatSpecular;
    GLint uMatShininess;
    GLint uMatDiffuse;

    GLint uViewPos;

    ObjetProgram(const FilePath& applicationPath):
            m_Program(loadProgram(applicationPath.dirPath() + "shaders/lightShader.vs.glsl",
                                applicationPath.dirPath() + "shaders/multipleLights.fs.glsl")){
            uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
            uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
            uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");

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

            uMatSpecular = glGetUniformLocation(m_Program.getGLId(), "material.specular");
            uMatShininess = glGetUniformLocation(m_Program.getGLId(), "material.shininess");
            uMatDiffuse = glGetUniformLocation(m_Program.getGLId(), "material.diffuse");

            uViewPos = glGetUniformLocation(m_Program.getGLId(), "viewPos");
            }
};

#endif

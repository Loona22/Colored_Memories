#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

#include "glm.hpp"
#include "FilePath.hpp"

namespace glimac {

    class TrackballCamera {
        private:
            float m_fDistance; 
            float m_fAngleX;
            float m_fAngleY;

        public:
            TrackballCamera(){
                m_fDistance = 5.0;
                m_fAngleX = 0.0;
                m_fAngleY = 0.0;
            }

            inline void moveFront(float delta){
                m_fDistance = m_fDistance + delta;
            }

            inline void rotateUp(float degrees){
                m_fAngleX = m_fAngleX + degrees;
            }

            inline void rotateLeft(float degrees){
                m_fAngleY = m_fAngleY + degrees;
            }

            inline glm::mat4 getViewMatrix() const {
                glm::mat4 ViewMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, - m_fDistance));
                ViewMatrix = glm::rotate(ViewMatrix, glm::radians(m_fAngleX), glm::vec3(1.0, 0.0, 0.0));
                ViewMatrix = glm::rotate(ViewMatrix, glm::radians(m_fAngleY), glm::vec3(0.0, 1.0, 0.0));

                return ViewMatrix;
            }

    };

}

//
// Created by Theo Fanet on 26/02/2017.
//

#include "Light.h"


namespace Gnin{
    namespace Graphics{

        Light::Light() {
            _shader   = new Shader("Assets/Shaders/shader");
            _size     = GSize(Gnin::SCREEN_WIDTH, Gnin::SCREEN_HEIGHT) * 20;
            _power    = 20;
            _position = GPos();
        }

        Light::~Light() {
            delete(_shader);
        }

        void Light::draw() {
            glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
            glStencilFunc(GL_EQUAL, 0, 1);
            glColorMask(true, true, true, true);

            _shader->bind();

            glUniform2f(glGetUniformLocation(_shader->getProgram(), "lightLocation"), _position.x, _position.y);
            glUniform3f(glGetUniformLocation(_shader->getProgram(), "lightColor"), _color.r, _color.g, _color.b);
            glUniform1f(glGetUniformLocation(_shader->getProgram(), "lightPower"), _power);

            glBlendFunc(GL_SRC_ALPHA, GL_ONE);

            Geometry::drawRect(_position, _size * 20);

            _shader->unbind();

            glClear(GL_STENCIL_BUFFER_BIT);
        }

        void Light::drawSadows(Physics::World *world) {
            glColorMask(false, false, false, true);
            glStencilFunc(GL_ALWAYS, 1, 1);
            glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

            std::vector<Physics::Body*> bodies = world->getBodies();

            for(std::vector<Physics::Body*>::iterator it = bodies.begin(); it != bodies.end(); ++it){
                Physics::Fixture* fixture = (*it)->getFixtures();
                while(fixture) {
                    std::vector<GVector> vertices = (*it)->getVertices();
                    glBegin(GL_QUADS);
                    for (std::vector<GVector>::iterator pti = vertices.begin(); pti != vertices.end(); ++pti)
                        glVertex3f((*pti).x, (*pti).y, 1.0);
                    glEnd();
                    fixture = fixture->getNext();
                }
            }

            GPos pos = (_position / Gnin::getCamera()->getZoom()) + Gnin::getCamera()->getPosition();

            for(std::vector<Physics::Body*>::iterator it = bodies.begin(); it != bodies.end(); ++it){
                Physics::Fixture* fixture = (*it)->getFixtures();
                while(fixture){
                    std::vector<GVector> vertices = (*it)->getVertices();
                    int i = 0;
                    for(std::vector<GVector>::iterator pti = vertices.begin(); pti != vertices.end(); ++pti){
                        GVector currentVertex = (*pti);
                        GVector nextVertex = vertices[(i + 1) % vertices.size()];
                        GVector edge = (currentVertex - nextVertex);
                        GVector normal = GVector(edge.y, -edge.x);
                        GVector lightToCurrent = (pos - currentVertex).asVector();
                        if(lightToCurrent.dotproduct(normal) > 0) {
                            GVector point1 = (currentVertex + ((currentVertex - pos.asVector()) * 800)) ;
                            GVector point2 = (nextVertex + ((nextVertex - pos.asVector()) * 800));

                            glBegin(GL_QUADS); {
                                glVertex2f(currentVertex.x, currentVertex.y);
                                glVertex2f(point1.x, point1.y);
                                glVertex2f(point2.x, point2.y);
                                glVertex2f(nextVertex.x, nextVertex.y);
                            } glEnd();
                        }
                        i++;
                    }
                    fixture = fixture->getNext();
                }
            }

            glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
            glStencilFunc(GL_LEQUAL, 1, 0xFF);
            glColorMask(true, true, true, true);
        }

    }
}
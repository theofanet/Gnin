//
// Created by Theo Fanet on 14/11/2016.
//

#include "World.h"


namespace Gnin{
    namespace Physics{

        World::World(GForce gravity) {
            _gravity = gravity * 5;
        }

        World::~World() {
            for(size_t i = 0; i < _bodies.size(); i++)
                delete(_bodies.at(i));
        }

		/*
		Create a body from fixtures
		Add gravity force
		Add the body to the word and return it
		*/
        Body* World::createBody(GPos position, Fixture *fixtures, BodyType type) {
            Body *body = new Body();

            body->setPosition(position);
            body->addFixture(fixtures);
			body->setBodyType(type);

			body->addForce("gravity", _gravity);

            _bodies.push_back(body);

            return body;
        }

        void World::destroyBody(Body *b) {
            _toDelete.push_back(b);
        }

		/*
		Update world
		*/
        void World::update(float elapsedTime) {
			// Update every bodies
            for(std::vector<Body*>::iterator b = _bodies.begin(); b != _bodies.end(); ++b)
                (*b)->update(elapsedTime);

			// Check collisions between bodies
            for(std::vector<Body*>::iterator b1 = _bodies.begin(); b1 != _bodies.end(); ++b1){
                for(std::vector<Body*>::iterator b2 = _bodies.begin(); b2 != _bodies.end(); ++b2){
                    if(b1 != b2){
                        if(Collision::checkBodyCollision((*b1), (*b2))){
                            (*b1)->setColliding(true);
                            (*b2)->setColliding(true);
                        }
                    }
                }
            }


            if(_toDelete.size()){
                std::vector<Body*> tmp;
                for(int i = 0; i < _bodies.size(); i++){
                    if(std::find(_toDelete.begin(), _toDelete.end(), _bodies[i]) == _toDelete.end())
                        tmp.push_back(_bodies[i]);
                    else
                        delete _bodies[i];
                }
                _bodies = tmp;
                _toDelete.clear();
            }
        }

		/*
		Draw world
		*/
        void World::draw() {
            for(std::vector<Body*>::iterator it = _bodies.begin(); it != _bodies.end(); ++it)
                (*it)->draw();
        }

    }
}
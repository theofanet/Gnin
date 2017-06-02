//
// Created by Theo Fanet on 14/11/2016.
//

#ifndef GLTEST_WORLD_H
#define GLTEST_WORLD_H

#include "Body.h"
#include "Collision.h"

#include <algorithm>

namespace Gnin{
    namespace Physics{

        class World {
        public:
            World(GForce gravity);
            ~World();

			/*
			Add body to the world
			*/
            Body* createBody(GPos position, Fixture *fixtures, BodyType type = BODY_DYNAMIC);
            void destroyBody(Body *b);

            // Returns bodies list
            inline std::vector<Body*> getBodies(){ return _bodies; }

			/*
			Update and draw methods
			*/
            void update(float elapsedTime);
            void draw();

        private:
			GForce _gravity;

            std::vector<Body*> _bodies;
            std::vector<Body*> _toDelete;
        };

    }
}

#endif //GLTEST_WORLD_H

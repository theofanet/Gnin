//
// Created by Theo Fanet on 14/11/2016.
//

#ifndef GLTEST_FIXTURE_H
#define GLTEST_FIXTURE_H

#include <vector>
#include <GLFW/glfw3.h>

#include "Physics.h"

namespace Gnin{
    namespace Physics{

		/*
		Basic Fixture class
		*/
        class Fixture {
        public:
            Fixture();
            ~Fixture();

            void draw();

			/*
			Colliding functions
			*/
            inline void setColliding(bool c){ _colliding = c; }
            inline bool isColliding(){ return _colliding; }

			/*
			Vertices functions
			*/
            inline void addVertex(GPoint v){ _vertices.push_back(v); }
            inline std::vector<GPoint> getVertices() { return _vertices; }

			/*
			Position function
			*/
            inline GPos getPosition(){ return _position; }
            inline void setPosition(GPos pos){ _position = pos; }
            inline void setPositionX(float x){ _position.x = x; }
            inline void setPositionY(float y){ _position.y = y; }

			/*
			Linked List functions
			*/
            inline Fixture* getNext(){ return _next; }
            inline void setNext(Fixture* f){ _next = f; }

        private:
            std::vector<GPoint> _vertices;

            GPos _position;

            bool _colliding;

            Fixture *_next;
        };

    }
}


#endif //GLTEST_FIXTURE_H

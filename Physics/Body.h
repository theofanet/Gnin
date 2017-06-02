//
// Created by Theo Fanet on 14/11/2016.
//

#ifndef GLTEST_BODY_H
#define GLTEST_BODY_H

#include <GLFW/glfw3.h>

#include "Physics.h"
#include "Fixture.h"

namespace Gnin{
    namespace Physics{

		enum BodyType {
			BODY_STATIC, 
			BODY_DYNAMIC
		};

        class Body {
        public:
            Body();
            ~Body();

			/*
			Update and Draw functions
			*/
            void draw();
            void update(float elapsedTime);
			
			/*
			Colliding state functions
			*/
            inline void setColliding(bool c){ _colliding = c; }
            inline bool isColliding(){ return _colliding; }

			/*
			Fixtures functions
			*/
            void addFixture(Fixture* f);
            inline Fixture* getFixtures(){ return _fixtures; }

			/*
			Positions functions
			*/
            inline GPos getPosition(){ return _position; }
            inline void setPosition(GPos pos){ _position = pos; }
            inline void setPositionX(float x){ _position.x = x; }
            inline void setPositionY(float y){ _position.y = y; }

			// Size getter
            inline GSize getSize(){ return _size; }

			/*
			Forces functions
			*/
			inline GForceList getForces() { return _forces; }
			GForce getForce(std::string name);
			inline void addForce(std::string name, GForce f) { _forces[name] = f; }

			/*
			Body type functions
			*/
			inline BodyType getBodyType() { return _type; }
			inline void setBodyType(BodyType t) { _type = t; }

			/*
			Velocity functions
			*/
			inline void setVelocity(GForce v) { _velocity = v; }
			inline void setVelocityX(float x) { _velocity.x = x; }
			inline void setVelocityY(float y) { _velocity.y = y; }
			inline GForce getVelocity() { return _velocity; }
			inline void applyImpulse(GForce impulse) { _impulses.push_back(impulse); }

			/*
			Grounded functions
			*/
			inline bool isGrounded() { return _grounded; }
			inline void setGrounded(bool g = true) { _grounded = g; }

			/*
			 * Custom data functions
			 */
			inline void setCustomData(void *d){ _custom_data = d; }
			inline void* getCustomData(){ return _custom_data; }


			inline std::vector<GVector> getVertices(){
				std::vector<GVector> vec;
				vec.push_back(GVector(_position.x - _size.w / 2, _position.y - _size.h / 2));
				vec.push_back(GVector(_position.x - _size.w / 2, _position.y + _size.h / 2));
				vec.push_back(GVector(_position.x + _size.w / 2, _position.y + _size.h / 2));
				vec.push_back(GVector(_position.x + _size.w / 2, _position.y - _size.h / 2));
				return vec;
			}

        private:
            void calculateSize();

            Fixture    *_fixtures;
			GForceList  _forces;

			GForce _velocity;
			std::vector<GForce> _impulses;

            bool _colliding;
			bool _grounded;

			void *_custom_data;

            GPos  _position;
            GSize _size;

			BodyType _type;
        };

    }
}


#endif //GLTEST_BODY_H

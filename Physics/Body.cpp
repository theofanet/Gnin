//
// Created by Theo Fanet on 14/11/2016.
//

#include "Body.h"
#include "../Graphics/Geometry.h"


namespace Gnin{
    namespace Physics{

        Body::Body() {
            _fixtures  = NULL;
            _colliding = false;
			_type = BODY_DYNAMIC;
			_grounded = false;
            _custom_data = NULL;
        }

        Body::~Body() {
            Fixture *f = _fixtures;
            while(f){
                Fixture *tmp = f;
                f = f->getNext();
                delete(tmp);
            }
        }

		/*
		Draw body;
		For debug
		*/
        void Body::draw() {
			// Saving Matrix
            glPushMatrix();

			// Moving to body position
            glTranslatef(_position.x, _position.y, 0);

			// Drawing fixtures
            Fixture *f = _fixtures;
            while(f){
                f->draw();
                f = f->getNext();
            }

			// Restoring Matrix
            glPopMatrix();


			// Getting color to draw body border
            Graphics::GColor color;
            color.r = (_colliding ? 1.0f : 0.0f);
            color.g = (!_colliding ? 1.0f : 0.0f);

			// Drawing body border
            Graphics::Geometry::drawStripRect(
                    _position,
                    _size,
                    color
            );
        }

		/*
		Update body
		Called by World
		*/
        void Body::update(float elapsedTime) {
			// Reseting colliding state
            _colliding = false;
            Fixture *f = _fixtures;
            while(f){
                f->setColliding(false);
                f = f->getNext();
            }

			if (_type == BODY_DYNAMIC) {
				// Getting acceleration due to forces
				GForce a;
				for (GForceList::iterator it = _forces.begin(); it != _forces.end(); ++it) 
					a += (*it).second;

				// Updating the velocity with acceleration and elapsedTime
				_velocity += a * (elapsedTime / 1000);

				// Applying impulses
				for (std::vector<GForce>::iterator it = _impulses.begin(); it != _impulses.end(); ++it)
					_velocity += (*it);
				_impulses.clear();

				// Finaly updating the position with velocity
				_position.x += _velocity.x;
				_position.y += _velocity.y;

				_grounded = false;
			}
        }

		/*
		Add fixture to body and then update the size
		*/
        void Body::addFixture(Fixture *f) {
			// Is fixture first or not
            if(!_fixtures)
                _fixtures = f;
            else{
                f->setNext(_fixtures);
                _fixtures = f;
            }

			// Updating body size
            calculateSize();
        }

		/*
		Calculate the size of the body 
		by iterating throw fixtures
		*/
        void Body::calculateSize() {
            Fixture *f = _fixtures;

			//Default min max
            float minx = _position.x;
            float maxx = _position.x;
            float miny = _position.y;
            float maxy = _position.y;

			/*
			Getting min and max X Y
			by checking every fixtures vertices
			*/
            while(f){
				std::vector<GPoint> vertices = f->getVertices();
				for(std::vector<GPoint>::iterator it = vertices.begin(); it != vertices.end(); ++it){
					float px = _position.x + f->getPosition().x;
                    float py = _position.y + f->getPosition().y;
               
					if(px + (*it).x < minx)
                        minx = px + (*it).x;
                    else if(px + (*it).x > maxx)
                        maxx = px + (*it).x;

                    if(py + (*it).y < miny)
                        miny = py + (*it).y;
                    else if(py + (*it).y > maxy)
                        maxy = py + (*it).y;
                }

                f = f->getNext();
            }

			// Getting size with min max
            _size.w = maxx - minx;
            _size.h = maxy - miny;
        }

		/*
		Get a force applied to body by it's name
		If it doesn't exists return an empty force
		*/
		GForce Body::getForce(std::string name) {
			GForce f;

			if (_forces.find(name) != _forces.end())
				f = _forces[name];

			return f;
		}

    }
}
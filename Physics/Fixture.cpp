//
// Created by Theo Fanet on 14/11/2016.
//

#include "Fixture.h"
#include "Gnin/Graphics/Geometry.h"

namespace Gnin{
    namespace Physics{

        Fixture::Fixture() {
            _next = NULL;
            _colliding = false;
        }

        Fixture::~Fixture() {

        }

		/*
		Draw function
		For debug
		*/
        void Fixture::draw() {
            Graphics::GColor color;
            color.r = (_colliding ? 1.0f : 0.0f);
            color.b = (!_colliding ? 1.0f : 0.0f);
			color.a = 0.3f;

            Gnin::Graphics::Geometry::drawPolygon(
                    _position,
                    _vertices,
                    color
            );
        }

    }
}
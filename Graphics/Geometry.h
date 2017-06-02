//
// Created by Theo Fanet on 14/11/2016.
//

#ifndef GLTEST_GEOMETRY_H
#define GLTEST_GEOMETRY_H

#include <GLFW/glfw3.h>
#include <vector>

#include "Gnin/Physics/Physics.h"

namespace Gnin{
    namespace Graphics{

		/*
		GColor structure
		*/
        struct GColor{
            GColor() : r(0.0f), g(0.0f), b(0.0f), a(1.0f){}
            GColor(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a){ }

            float r, g, b, a;
        };

		/*
		Basic geometry helper class
		*/
        class Geometry {
        public:
			/*
			Basic shapes draw functions
			*/
            static void drawPolygon(GPos pos, std::vector<GPoint> vertices, GColor color);
            static void drawRect(GPos pos, GSize size, GColor color = GColor());
            static void drawStripRect(GPos pos, GSize size, GColor color, float width = 1.0f);
            static void drawLine(GPos p1, GPos p2, float width = 1.0f, GColor color = GColor(1.0f, 1.0f, 1.0f));
        };

    }
}


#endif //GLTEST_GEOMETRY_H

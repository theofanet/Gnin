//
// Created by Theo Fanet on 14/11/2016.
//

#include "Geometry.h"


namespace Gnin{
    namespace Graphics{

		/*
		Draw a polygon to the screen
		At position pos
		Of color color
		with vertices list 
		*/
        void Geometry::drawPolygon(GPos pos, std::vector<GPoint> vertices, GColor color) {
            glPushMatrix();

            glTranslatef(pos.x, pos.y, 0);
            glColor4f(color.r, color.g, color.b, color.a);

            glBegin(GL_TRIANGLE_FAN);
            for (std::vector<GPoint>::iterator it = vertices.begin(); it != vertices.end(); ++it)
                glVertex2f((*it).x, (*it).y);
            glEnd();

            glPopMatrix();
        }

		/*
		Draw a rectangle on the screen
		At position pos
		Of size size
		Of color color
		*/
        void Geometry::drawRect(GPos pos, GSize size, GColor color) {
            glPushMatrix();

            glTranslatef(pos.x, pos.y, 0);
            glColor4f(color.r, color.g, color.b, color.a);

            float midW = size.w / 2;
            float midH = size.h / 2;

            glBegin(GL_QUADS);
            glVertex2d(-midW, -midH);
            glVertex2d(-midW,  midH);
            glVertex2d(midW,   midH);
            glVertex2d(midW,  -midH);
            glEnd();

            glPopMatrix();
        }

		/*
		Draw a stripped rectangle on the screen
		At position pos
		Of size size
		Of color color
		With line width of width
		*/
        void Geometry::drawStripRect(GPos pos, GSize size, GColor color, float width) {

            glPushMatrix();

            glTranslatef(pos.x, pos.y, 0);
            glColor4f(color.r, color.g, color.b, color.a);

            float midW = size.w / 2;
            float midH = size.h / 2;

            glLineWidth(width);
            glBegin(GL_LINE_LOOP);
            glVertex2d(-midW, -midH);
            glVertex2d(-midW,  midH);
            glVertex2d(midW,   midH);
            glVertex2d(midW,  -midH);
            glEnd();

            glPopMatrix();

        }

        /*
         * Draw a line to the screen
         * From p1 to p2 of width width
         * and color color
         */
        void Geometry::drawLine(GPos p1, GPos p2, float width, GColor color) {

            glPushMatrix();

            glColor4f(color.r, color.g, color.b, color.a);

            glLineWidth(width);
            glBegin(GL_LINES);
            glVertex2d(p1.x, p1.y);
            glVertex2d(p2.x, p2.y);
            glEnd();

            glPopMatrix();

        }

    }
}
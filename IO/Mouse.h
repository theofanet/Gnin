//
// Created by Theo Fanet on 14/11/2016.
//

#ifndef GLTEST_MOUSE_H
#define GLTEST_MOUSE_H

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "Gnin/Physics/Physics.h"

namespace Gnin{
    namespace IO{

        class Mouse {
        public:
			/*
			Callbacks for mouse buttons and position
			*/
            static void mousePosCallback(GLFWwindow* window, double x, double y);
            static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

			/*
			Getters for mouse position
			*/
            static GPos getMousePos();
            static double getMouseX();
            static double getMouseY();

			/*
			Getters for mouse buttons state
			*/
            static bool isButtonDown(int button);
            static bool isButtonUp(int button);
            static bool isButtonHeld(int button);

        private:
            static double _x;
            static double _y;

            static bool _buttonsHeld[];
            static bool _buttonsDown[];
            static bool _buttonsUp[];
        };

    }
}


#endif //GLTEST_MOUSE_H

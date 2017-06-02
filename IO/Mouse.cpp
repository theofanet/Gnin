//
// Created by Theo Fanet on 14/11/2016.
//

#include "Mouse.h"
#include "../Gnin.h"
#include <iostream>

namespace Gnin{
    namespace IO{

        double Mouse::_x = 0;
        double Mouse::_y = 0;

        bool Mouse::_buttonsHeld[GLFW_MOUSE_BUTTON_LAST] = { 0 };
        bool Mouse::_buttonsDown[GLFW_MOUSE_BUTTON_LAST] = { 0 };
        bool Mouse::_buttonsUp[GLFW_MOUSE_BUTTON_LAST]   = { 0 };

        /**
         * Get the mouse position and update handler
         */
        void Mouse::mousePosCallback(GLFWwindow *window, double x, double y) {
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);

            _x = x * (width / Gnin::SCREEN_WIDTH);
            _y = height - y * (height / Gnin::SCREEN_HEIGHT);
        }

        /**
         * Update mouse button handler
         */
        void Mouse::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
            if (button < 0)
                return;

            if (action != GLFW_RELEASE && !_buttonsHeld[button])
            {
                _buttonsDown[button] = true;
                _buttonsUp[button] = false;
            }

            if (action == GLFW_RELEASE && !_buttonsHeld[button])
            {
                _buttonsDown[button] = false;
                _buttonsUp[button] = true;
            }

            _buttonsHeld[button] = action != GLFW_RELEASE;
        }

        GPos Mouse::getMousePos() {
            return GPos((float)_x, (float)_y);
        }

        double Mouse::getMouseX() {
            return _x;
        }

        double Mouse::getMouseY() {
            return _y;
        }

        bool Mouse::isButtonDown(int button) {
            bool x = _buttonsDown[button];
            _buttonsDown[button] = false;
            return x;
        }

        bool Mouse::isButtonUp(int button) {
            bool x = _buttonsUp[button];
            _buttonsUp[button] = false;
            return x;
        }

        bool Mouse::isButtonHeld(int button) {
            return _buttonsHeld[button];
        }

    }
}
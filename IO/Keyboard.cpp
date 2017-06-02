//
// Created by Theo Fanet on 14/11/2016.
//

#include "Keyboard.h"

namespace Gnin{

    namespace IO{
        bool Keyboard::_keysUp[GLFW_KEY_LAST] = { 0 };
        bool Keyboard::_keysDown[GLFW_KEY_LAST] = { 0 };
        bool Keyboard::_keysHeld[GLFW_KEY_LAST] = { 0 };

		/*
		Is triggered when keyboard key is up or down
		Update keyboard keys state
		*/
        void Keyboard::keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
            if (key < 0)
                return;

            if (action != GLFW_RELEASE && !_keysHeld[key]){
                _keysDown[key] = true;
                _keysUp[key] = false;
            }

            if (action == GLFW_RELEASE){
                _keysDown[key] = false;
                _keysUp[key] = true;
            }

            _keysHeld[key] = action != GLFW_RELEASE;
        }

        bool Keyboard::isKeyDown(int key) {
            bool x = _keysDown[key];
            _keysDown[key] = false;
            return x;
        }

        bool Keyboard::isKeyUp(int key) {
            bool x = _keysUp[key];
            _keysUp[key] = false;
            return x;
        }

        bool Keyboard::isKeyHeld(int key) {
            return _keysHeld[key];
        }
    }

}
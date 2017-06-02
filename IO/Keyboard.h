//
// Created by Theo Fanet on 14/11/2016.
//

#ifndef GLTEST_KEYBOARD_H
#define GLTEST_KEYBOARD_H

#include <GLFW/glfw3.h>

namespace Gnin{

    namespace IO{
        class Keyboard {
        public:
			// Callback for keyboard keys events
            static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

			/*
			Getters for keys state
			*/
            static bool isKeyDown(int key);
            static bool isKeyUp(int key);
            static bool isKeyHeld(int key);

        private:
            static bool _keysDown[];
            static bool _keysUp[];
            static bool _keysHeld[];
        };
    }

}


#endif //GLTEST_KEYBOARD_H

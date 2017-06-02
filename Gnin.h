//
// Created by Theo Fanet on 14/11/2016.
//

#ifndef GLTEST_GNIN_H
#define GLTEST_GNIN_H

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

#include "IO/Keyboard.h"
#include "IO/Mouse.h"
#include "Game/Scene.h"
#include "Graphics/Geometry.h"
#include "Graphics/Sprite.h"
#include "Graphics/Camera.h"

namespace Gnin{

    class Gnin {
    public:
        static int SCREEN_WIDTH;
        static int SCREEN_HEIGHT;
		static float FPS;

        Gnin();
        ~Gnin();

		/*
		Initialisation of engine
		*/
        bool init(std::string title);

		// When screen is resized
        static void resize(GLFWwindow *window, int width, int height);

		/*
		Run function
		Lunch main loop
		*/
        void run();

		/*
		Update, draw function
		*/
		void update();
        void draw();

		/*
		Set the current scene
		Engine needs to work with
		*/
        inline void setScene(Game::Scene *scene){ _scene = scene; }

		/*
		Get elapsed time of frame
		*/
		inline static float getDT() { return _dt; }

		/*
		 * Camera functions
		 */
		inline static Graphics::Camera* getCamera(){ return Graphics::Camera::getInstance(); }

    private:
        static GLFWwindow *_window;

		static float _dt;
		float _lastTime;
		int _nbFrame;

		std::string _title;

        Game::Scene *_scene;
    };

}

#endif //GLTEST_GNIN_H

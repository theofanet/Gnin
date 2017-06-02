//
// Created by Theo Fanet on 14/11/2016.
//

#include "Gnin.h"
#include <sstream>
#ifdef __WIN32__
#include <Windows.h>
#define SLEEP(t) Sleep(t)
#else
#include <unistd.h>
#define SLEEP(t) usleep(t)
#endif

namespace Gnin{
    int Gnin::SCREEN_WIDTH  = 1024;
    int Gnin::SCREEN_HEIGHT = 768;
	float Gnin::FPS = 60.0f;
	float Gnin::_dt = 0.0f;

    GLFWwindow* Gnin::_window = NULL;

    Gnin::Gnin() {
        _scene = NULL;
    }

    Gnin::~Gnin() {
        if(_window)
            glfwDestroyWindow(_window);
    }

/**
 * Initialize function,
 * Create window and initialize GLFW, GL, ...
 */
    bool Gnin::init(std::string title) {
        if(!glfwInit()){
            std::cout << "Enable to initialize GLFW" << std::endl;
            return false;
        }

        _window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, title.c_str(), NULL, NULL);
        if(!_window){
            std::cout << "Error creating the window" << std::endl;
            return false;
        }

		_title = title;

        /**
         * GLFW / GLEW Setup
         */
        glfwMakeContextCurrent(_window);

        /**
         * GLEW
         */
        glewExperimental = GL_TRUE;
        if(glewInit() != GLEW_OK){
            std::cout << "Error initiating GLEW" << std::endl;
            return false;
        }


        int w, h;
        glfwGetFramebufferSize(_window, &w, &h);
        glfwSwapInterval(1);

        /**
         * Center the window on the monitor
         */
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        int xPos = (mode->width - SCREEN_WIDTH) / 2;
        int yPos = (mode->height - SCREEN_HEIGHT) / 2;
        glfwSetWindowPos(_window, xPos, yPos);

        //Callbacks functions
        glfwSetKeyCallback(_window, IO::Keyboard::keyboardCallback);
        glfwSetMouseButtonCallback(_window, IO::Mouse::mouseButtonCallback);
        glfwSetCursorPosCallback(_window, IO::Mouse::mousePosCallback);
        glfwSetWindowSizeCallback(_window, Gnin::resize);
		//glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        /**
         * GL Setup
         *
         * Viewport
         */
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, w, 0, h, -10, 10);
        glDepthRange(-10, 10);
        glMatrixMode(GL_MODELVIEW);

        /**
         * Alpha Blending
         */
        glEnable(GL_ALPHA_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_STENCIL_TEST);

        return true;
    }

/**
 * Triggered when window is resized
 * Reset the view and updates the screen width and height
 */
    void Gnin::resize(GLFWwindow *window, int width, int height) {
        SCREEN_WIDTH  = width;
        SCREEN_HEIGHT = height;

        glfwMakeContextCurrent(window);
        int w, h;
        glfwGetFramebufferSize(window, &w, &h);

        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, w, 0, h, -10, 10);
        glDepthRange(-10, 10);
        glMatrixMode(GL_MODELVIEW);
    }

/**
 * Main loop,
 * Engine updates Scene and Draw it
 * Check if exit status has been triggered
 */
    void Gnin::run() {
        bool exit = false;

		_lastTime = (float)glfwGetTime() * 1000.0f;
		_nbFrame = 0;

        while(!exit){
			float now = (float)glfwGetTime() * 1000.0f;
			_dt = now - _lastTime;
			_lastTime = now;

			update();

			/**
			* Exit status
			* Escape key
			* Else scene IO Handle session
			*/
			if (IO::Keyboard::isKeyDown(GLFW_KEY_ESCAPE))
				exit = true;
			else if (_scene)
				_scene->handleIO();

			draw();

			_nbFrame++;

			if (_dt < (1000.0f / FPS))
				SLEEP((1000.0f / FPS) - _dt);
        }
    }

/**
 * Update function,
 * Update scene
 */
    void Gnin::update() {

        glfwPollEvents();

        if(_scene)
            _scene->update(_dt);
    }

/**
 * Draw function,
 * Draw scene
 */
    void Gnin::draw() {
        glClearColor(0.0f, 0.0f, 0.0f, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        getCamera()->bind();

        if(_scene)
            _scene->draw();

        getCamera()->unbind();

        glfwSwapBuffers(_window);
    }
}

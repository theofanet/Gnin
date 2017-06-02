//
// Created by Theo Fanet on 14/11/2016.
//

#ifndef GLTEST_SCENE_H
#define GLTEST_SCENE_H

#include <stdio.h>

#include "Gnin/Physics/World.h"

namespace Gnin{

    namespace Game{

        class Scene;

        /**
         * Scene Delegate
         */
        class SceneDelegate{
        public:
            virtual void sceneEnded(Scene *scene){}
        };


        /**
         * Base Scene class
         */
        class Scene {
        public:
            Scene(){
				_delegate = NULL;
				_world = NULL;
			}
            virtual ~Scene(){}

			/*
			Update and draw functions
			pure virtual
			*/
            virtual void update(float elapsedTime) = 0;
            virtual void draw() = 0;

			// Handle IO function
			virtual void handleIO() { }

			// Delegate setter
            void setDelagate(SceneDelegate *delegate){ _delegate = delegate; }

        protected:
            SceneDelegate *_delegate;

			Physics::World *_world;
        };

    }
}



#endif //GLTEST_SCENE_H

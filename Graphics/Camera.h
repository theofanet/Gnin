//
// Created by Theo on 17/12/2016.
//

#ifndef TESTGNIN_CAMERA_H
#define TESTGNIN_CAMERA_H

#include "GL/glew.h"
#include "Gnin/Physics/Physics.h"

namespace Gnin{
    namespace Graphics{

        class Camera {
        public:
            static Camera* getInstance();

            inline void setPosition(Gnin::GPos pos){ _position = pos; }
            inline Gnin::GPos getPosition(){ return _position; }
            inline void setZoom(GLfloat z){ _zoom = z; }
            inline GLfloat getZoom(){ return _zoom; }

            void bind();
            void unbind();

        private:
            static Camera *_instance;

            Camera();

        protected:
            GLfloat _zoom;
            Gnin::GPos _position;
        };

    }
}

#endif //TESTGNIN_CAMERA_H

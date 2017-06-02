//
// Created by Theo on 17/12/2016.
//

#include "Camera.h"


namespace Gnin{
    namespace Graphics{

        Camera* Camera::_instance = NULL;

        Camera::Camera() {
            _zoom = 1.0;
        }

        Camera* Camera::getInstance() {
            if(_instance == NULL)
                _instance = new Camera();

            return _instance;
        }

        void Camera::bind() {
            glPushMatrix();

            glScaled(_zoom, _zoom, _zoom);
            glTranslatef(-_position.x, -_position.y, 0.0);
        }

        void Camera::unbind() {
            glPopMatrix();
        }

    }
}
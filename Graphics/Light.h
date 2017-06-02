//
// Created by Theo Fanet on 26/02/2017.
//

#ifndef GNINGAME_LIGHT_H
#define GNINGAME_LIGHT_H

#include <Gnin/Gnin.h>
#include <Gnin/Physics/Physics.h>
#include "Geometry.h"
#include "Shader.h"

namespace Gnin{
    namespace Graphics{

        class Light {
        public:
            Light();
            ~Light();

            void draw();
            void drawSadows(Physics::World *world);

            inline void setPosition(GPos pos){ _position = pos; }
            inline void setPosition(float x, float y){ setPosition(GPos(x, y)); }
            inline GPos getPosition(){ return _position; }

            inline void  setPower(float p){ _power = p; }
            inline float getPower(){ return _power; }

            inline void   setColor(GColor color){ _color = color; }
            inline void   setColor(float r, float g, float b){ setColor(GColor(r, g, b)); }
            inline GColor getColor(){ return _color; }

        protected:
            GPos   _position;
            GColor _color;
            float  _power;
            GSize  _size;

            Graphics::Shader *_shader;
        };

    }
}


#endif //GNINGAME_LIGHT_H

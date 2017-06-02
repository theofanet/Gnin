//
// Created by Theo on 28/11/2016.
//

#ifndef TESTGNIN_SHADER_H
#define TESTGNIN_SHADER_H

#include "GL/glew.h"
#include <string>

namespace Gnin{
    namespace Graphics{

        class Shader {
        public:
            Shader(){}
            Shader(std::string fileName);
            ~Shader();

            void bind();
            void unbind();
            inline GLuint getProgram(){ return _program; }

        private:
            enum{
                VERTEX_SH,
                FRAGMENT_SH,

                NUM_SHADERS
            };

            std::string LoadShader(const std::string& fileName);
            void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
            GLuint CreateShader(const std::string& text, unsigned int type);

            GLuint _program;
            GLuint _shaders[NUM_SHADERS];
        };

    }
}

#endif //TESTGNIN_SHADER_H

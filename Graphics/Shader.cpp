//
// Created by Theo on 28/11/2016.
//

#include "Shader.h"

#include <iostream>
#include <fstream>

namespace Gnin{
    namespace Graphics{

        Shader::Shader(std::string fileName) {
            _program = glCreateProgram();

            _shaders[VERTEX_SH] = CreateShader(LoadShader(fileName + ".gvs"), GL_VERTEX_SHADER);
            _shaders[FRAGMENT_SH] = CreateShader(LoadShader(fileName + ".gfs"), GL_FRAGMENT_SHADER);

            for(unsigned int i = 0; i < NUM_SHADERS; i++)
                glAttachShader(_program, _shaders[i]);

            glBindAttribLocation(_program, 0, "position");
            glBindAttribLocation(_program, 1, "texCoord");

            glLinkProgram(_program);
            CheckShaderError(_program, GL_LINK_STATUS, true, "Shader error : program failed to link => ");

            glValidateProgram(_program);
            CheckShaderError(_program, GL_VALIDATE_STATUS, true, "Shader error : Invalid program => ");
        }

        Shader::~Shader() {
            for(unsigned int i = 0; i < NUM_SHADERS; i++){
                glDetachShader(_program, _shaders[i]);
                glDeleteShader(_shaders[i]);
            }

            glDeleteProgram(_program);
        }

        void Shader::bind(){
            glUseProgram(0);
            glUseProgram(_program);
        }

        void Shader::unbind(){
            glUseProgram(0);
        }

        std::string Shader::LoadShader(const std::string& fileName) {
            std::ifstream file;
            file.open((fileName).c_str());

            std::string output;
            std::string line;

            if(file.is_open()) {
                while(file.good()) {
                    getline(file, line);
                    output.append(line + "\n");
                }
            }
            else
                std::cerr << "Unable to load shader: " << fileName << std::endl;

            return output;
        }



        void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage) {
            GLint success = 0;
            GLchar error[1024] = { 0 };

            if(isProgram)
                glGetProgramiv(shader, flag, &success);
            else
                glGetShaderiv(shader, flag, &success);

            if(success == GL_FALSE) {
                if(isProgram)
                    glGetProgramInfoLog(shader, sizeof(error), NULL, error);
                else
                    glGetShaderInfoLog(shader, sizeof(error), NULL, error);

                std::cerr << errorMessage << ": '" << error << "'" << std::endl;
            }

        }

        GLuint Shader::CreateShader(const std::string& text, unsigned int type) {
            GLuint shader = glCreateShader(type);

            if(shader == 0)
                std::cerr << "Error compiling shader type " << type << std::endl;

            const GLchar* p[1];
            p[0] = text.c_str();
            GLint lengths[1];
            lengths[0] = text.length();

            glShaderSource(shader, 1, p, lengths);
            glCompileShader(shader);

            CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");

            return shader;
        }

    }
}
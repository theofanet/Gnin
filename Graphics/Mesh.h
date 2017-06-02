//
// Created by Theo on 28/11/2016.
//

#ifndef TESTGNIN_MESH_H
#define TESTGNIN_MESH_H

#include "GL/glew.h"
#include "Texture.h"

namespace Gnin{
    namespace Graphics{

        struct Vert3{
            Vert3(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) { }
            GLfloat x, y, z;
        };

        struct Vert2{
            Vert2(GLfloat x, GLfloat y) : x(x), y(y) { }
            GLfloat x, y;
        };

        struct Vertex{
            Vertex(GLfloat x, GLfloat y, GLfloat z) : pos(x, y, z), texCoord(1.0, 1.0){ }
            Vertex(GLfloat x, GLfloat y, GLfloat z, GLfloat tx, GLfloat ty) : pos(x, y, z), texCoord(tx, ty){ }

            Vert3 pos;
            Vert2 texCoord;
        };

        class Mesh {
        public:
            Mesh(){}
            Mesh(Vertex *vertices, size_t numVertex);
            ~Mesh();

            void draw();

        private:

            enum {
                POSITION_VB,
                TEXCOORD_VB,

                NUM_BUFFERS
            };

            GLuint _vertexArrayObject;
            GLuint _vertexArrayBuffers[NUM_BUFFERS];


            Texture _texture;

            int _numVertex;
        };

    }
}


#endif //TESTGNIN_MESH_H

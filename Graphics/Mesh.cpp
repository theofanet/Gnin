//
// Created by Theo on 28/11/2016.
//

#include "Mesh.h"
#include <vector>

namespace Gnin{
    namespace Graphics{

        Mesh::Mesh(Vertex *vertices, size_t numVertex) {
            _numVertex = (int)numVertex;

            glGenVertexArrays(1, &_vertexArrayObject);
            glBindVertexArray(_vertexArrayObject);

            std::vector<Vert3> positions;
            std::vector<Vert2> texCoords;

            positions.reserve(numVertex);
            texCoords.reserve(numVertex);

            for(unsigned int i = 0; i < numVertex; i++){
                positions.push_back(vertices[i].pos);
                texCoords.push_back(vertices[i].texCoord);
            }

            glGenBuffers(NUM_BUFFERS, _vertexArrayBuffers);

            glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[POSITION_VB]);
            glBufferData(GL_ARRAY_BUFFER, numVertex * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

            glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[TEXCOORD_VB]);
            glBufferData(GL_ARRAY_BUFFER, numVertex * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

            glBindVertexArray(0);
        }

        Mesh::~Mesh() {
            glDeleteVertexArrays(1, &_vertexArrayObject);
        }

        void Mesh::draw() {
            glBindVertexArray(_vertexArrayObject);

            glDrawArrays(GL_TRIANGLES, 0, _numVertex);

            glBindVertexArray(0);
        }

    }
}
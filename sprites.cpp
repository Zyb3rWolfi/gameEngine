//
// Created by Zyb3rWolfi on 08/01/2024.
//

#include "sprites.h"
#include "vertex.h"
#include <cstddef>

sprites::sprites() {
    _vboID = 0;
}
sprites::~sprites() {
    if (_vboID != 0) {
        glDeleteBuffers(2, &_vboID);
    }
}

void sprites::init(float x, float y, float width, float height) {

    _x = x;
    _y = y;
    _height = height;
    _width = width;

    if (_vboID == 0) {
        glGenBuffers(2, &_vboID);
    }

    vertex vertexData[6];

    // First triangle
    vertexData[0].position.x = x + width;
    vertexData[0].position.y = y + height;

    vertexData[1].position.x = x;
    vertexData[1].position.y = y + height;

    vertexData[2].position.x = x;
    vertexData[2].position.y = y;

    // Second triangle
    vertexData[3].position.x = x;
    vertexData[3].position.y = y;

    vertexData[4].position.x = x + width;
    vertexData[4].position.y = y;

    vertexData[5].position.x = x + width;
    vertexData[5].position.y = y + height;

    // colors
    vertexData[5].color.g = 100;
    vertexData[5].color.r = 50;
    vertexData[5].color.b = 40;

    vertexData[2].color.b = 240;
    vertexData[2].color.r = 100;
    vertexData[2].color.b = 80;

    vertexData[1].color.b = 60;
    vertexData[1].color.r = 20;
    vertexData[1].color.b = 120;

    vertexData[3].color.b = 200;
    vertexData[3].color.r = 200;
    vertexData[3].color.b = 255;


    vertexData[4].color.b = 255;
    vertexData[4].color.r = 60;
    vertexData[4].color.b = 175;

    vertexData[0].color.b = 30;
    vertexData[0].color.r = 100;
    vertexData[0].color.b = 199;

    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void sprites::draw() {

    glBindBuffer(GL_ARRAY_BUFFER, _vboID);

    glEnableVertexAttribArray(0);

    // this is the posititon atr pointer
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, position));
    // This the color atr pointer
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(vertex), (void*) offsetof(vertex, color));

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
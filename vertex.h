//
// Created by Zyb3rWolfi on 08/01/2024.
//

#ifndef UNTITLED_VERTEX_H
#define UNTITLED_VERTEX_H
#include <glew.h>
struct Position {
    float x;
    float y;
};

struct Color {
    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;
};

struct vertex {
    Position position;
    Color color;
};

#endif //UNTITLED_VERTEX_H

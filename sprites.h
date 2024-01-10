//
// Created by Zyb3rWolfi on 08/01/2024.
//

#ifndef UNTITLED_SPRITES_H
#define UNTITLED_SPRITES_H
#include<glew.h>

class sprites {
public:
    sprites();
    ~sprites();



    void init(float x, float y, float width, float height);
    void draw();
private:
    int _x;
    int _y;
    int _height;
    int _width;
    GLuint _vboID;
};


#endif //UNTITLED_SPRITES_H

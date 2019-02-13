#include "main.h"

#ifndef SCREEN_H
#define SCREEN_H

class Screen{
    public:
        Screen() {}
        Screen(float x, float y, float z);
        glm::vec3 position;
        void draw(glm::mat4 VP);
        void clear(glm::mat4 VP);
        float radius;
        float bottom;
        void set_position(float x,float y);
        float ret_x();
        float ret_y();
        float ret_z();
        int move();
    private:
        VAO *object_base;
        VAO *object_clear;
};

#endif
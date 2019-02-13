#include "main.h"

#ifndef MOUNTAIN_H
#define MOUNTAIN_H


class Mountain {
public:
    Mountain() {}
    Mountain(float x, float y,float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *object_base;
    VAO *object_top;
};

#endif // BALL_H
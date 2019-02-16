#include "main.h"

#ifndef MOUNTAIN_H
#define MOUNTAIN_H


class Mountain {
public:
    Mountain() {}
    Mountain(float x, float y,float z,float r1,float h);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float radius;
    double speed;
    float height;
private:
    VAO *object;
    VAO *object_base;
    VAO *object_top;
    VAO *object_second;
};

#endif // BALL_H
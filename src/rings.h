#include "main.h"

#ifndef RINGS_H
#define RINGS_H


class Rings {
public:
    Rings() {}
    Rings(float x, float y,float z,float r1,float h);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float radius;
    double speed;
private:
    VAO *object_outer_base;
    VAO *object_outer_top;
    VAO *object_outer_c1;
    VAO *object_outer_c2;
    VAO *object_inner_base;
    VAO *object_inner_top;
    VAO *object_inner_c1;
    VAO *object_inner_c2;
};

#endif // BALL_H
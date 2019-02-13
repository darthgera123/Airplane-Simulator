#include "main.h"

#ifndef CYLINDER_H
#define CYLINDER_H


class Cylinder {
public:
    Cylinder() {}
    Cylinder(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object_1;
    VAO *object_2;
    VAO *object_rectangles;
    VAO *object_tr1;
    VAO *object_tr2;
};

#endif // BALL_H
#include "main.h"

#ifndef CONE_H
#define CONE_H


class Cone {
public:
    Cone() {}
    Cone(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *object_base;
};

#endif // BALL_H
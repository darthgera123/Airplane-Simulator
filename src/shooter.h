#include "main.h"

#ifndef SHOOTER_H
#define SHOOTER_H


class Shooter {
public:
    Shooter() {}
    Shooter(float x, float y,float z,float r1,float h);
    glm::vec3 position;
    float rotation;
    void draw(glm::vec3 t,glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float radius;
    double speed;
private:
    VAO *object_shooter_base;
    VAO *object_shooter_top;
    VAO *object_shooter_c1;
    VAO *object_shooter_c2;
};

#endif // BALL_H
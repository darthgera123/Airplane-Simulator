#include "main.h"

#ifndef COMPASS_H
#define COMPASS_H


class Compass {
public:
    Compass() {}
    Compass(float x, float y,float r1);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    float radius;
    float radius_rx;
    void change_angle();
    double speed;
private:
    VAO *object_outer_base;
    VAO *object_outer_top;
};

#endif // BALL_H
#include "main.h"

#ifndef DASHS_H
#define DASHS_H


class Dashsticks {
public:
    Dashsticks() {}
    Dashsticks(float x, float y,float r1,float max_value,int type);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    float radius;
    void change_angle();
    double speed;
    float max;
    float curr_value;
private:
    VAO *object_outer_base;
    VAO *object_outer_top;
    VAO *object_outer_c1;
};

#endif // BALL_H
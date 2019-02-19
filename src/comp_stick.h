#include "main.h"

#ifndef COMPS_H
#define COMPS_H


class Compsticks {
public:
    Compsticks() {}
    Compsticks(float x, float y,float r1);
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
    
};

#endif // BALL_H
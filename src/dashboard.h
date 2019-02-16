#include "main.h"

#ifndef DASH_H
#define DASH_H


class Dashboard {
public:
    Dashboard() {}
    Dashboard(float x, float y,float r1,int type);
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
    VAO *object_outer_c1;
    VAO *object_outer_c2;
    VAO *object_inner_base;
    VAO *object_inner_top;
    VAO *object_inner_c1;
    VAO *object_inner_c2;
};

#endif // BALL_H
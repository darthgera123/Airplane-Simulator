#include "main.h"

#ifndef MISSILE_H
#define MISSILE_H


class Missile {
public:
    Missile() {}
    Missile(float x, float y,float z,glm::mat4 rotate, glm::vec3 speed_dir);
    glm::vec3 position;
    glm::vec3 speed_dir;
    glm::mat4 rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void move_forward();
    float radius;
    double speed;
private:
    VAO *object_missile_base;
    VAO *object_missile_top;
    VAO *object_missile_c1;
    VAO *object_missile_c2;
    VAO *object_missile_tip;
};

#endif // BALL_H
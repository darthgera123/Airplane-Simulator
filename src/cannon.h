#include "main.h"

#ifndef CANNON_H
#define CANNON_H


class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y,float z,glm::vec3 dir);
    glm::vec3 position;
    glm::vec3 speed_dir;
    glm::mat4 rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void fall_down();
    float radius;
    double speed;
    void set_dir(glm::vec3 dir);
    void move();
private:
    VAO *object;
};

#endif // BALL_H
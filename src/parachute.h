#include "main.h"

#ifndef PARACHUTE_H
#define PARACHUTE_H


class Parachute {
public:
    Parachute() {}
    Parachute(float x, float y,float z);
    glm::vec3 position;
    glm::vec3 speed_dir;
    glm::mat4 rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void fall_down();
    float radius;
    double speed;
private:
    VAO *object_parachute_base;
    VAO *object_parachute_top;
    VAO *object_parachute_c1;
    VAO *object_parachute_c2;
    VAO *object_parachute_tip;
};

#endif // BALL_H
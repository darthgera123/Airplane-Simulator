#include "main.h"

#ifndef AIRPLANE_H
#define AIRPLANE_H


class Airplane {
public:
    Airplane() {}
    Airplane(float x, float y, float z);
    glm::vec3 position;
    glm::mat4 totalRot;
    glm::mat4 totalUp;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    void move_forward();
    void fall();
    void lift();
    void tilt_left();
    void tilt_right();
    void dive_down();
    void dive_up();
    void move_left();
    void move_right();
    float dir_rotation;
    float rotation_x;
    float rotation_y;
    float rotation_z;
    float radius;
    float fuel;
    float score;
    glm::vec4 set_eye(glm::vec4 E);
    glm::vec4 set_speed(glm::vec4 S);
    glm::vec4 set_top(glm::vec4 T);
    glm::vec4 set_up(glm::vec4 U);
    void reset_rotation();
    
private:
    VAO *object_1;
    VAO *object_2;
    VAO *object_rectangles;
    VAO *object_tr1;
    VAO *object_tr2;
    VAO *object_cone;
    VAO *object_cone_base;
    VAO *object_wings;
    VAO *object_tail;
    VAO *object_back;
};

#endif
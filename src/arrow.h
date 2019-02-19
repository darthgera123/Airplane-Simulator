#include "main.h"

#ifndef ARROW_H
#define ARROW_H


class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y,float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float radius;
    double speed;
private:
    VAO *object_base;
    VAO *object_top;
    
};

#endif // BALL_H
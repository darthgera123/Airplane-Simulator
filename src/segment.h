#include "main.h"

#ifndef SEGMENT_H
#define SEGMENT_H

class Segment{
    public:
        Segment() {}
        Segment(float x, float y,int type,float zoom);
        glm::vec3 position;
        void draw(glm::mat4 VP);
        void draw_0(glm::mat4 VP);
        void draw_1(glm::mat4 VP);
        void draw_2(glm::mat4 VP);
        void draw_3(glm::mat4 VP);
        void draw_4(glm::mat4 VP);
        void draw_5(glm::mat4 VP);
        void draw_6(glm::mat4 VP);
        void draw_7(glm::mat4 VP);
        void draw_8(glm::mat4 VP);
        void draw_9(glm::mat4 VP);
        void clear(glm::mat4 VP);
        float radius;
        float bottom;
        void set_position(float x,float y);
        float ret_x();
        float ret_y();
        int type;
        
    private:
        VAO *object_a;
        VAO *object_b;
        VAO *object_c;
        VAO *object_d;
        VAO *object_e;
        VAO *object_f;
        VAO *object_g;
        VAO *object_clear;
};

#endif
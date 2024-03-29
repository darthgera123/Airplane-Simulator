#include "bomb.h"
#include "main.h"

Bomb::Bomb(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    float speed = 0.5;
    float h = 0.1;
    this->depth = this->height = this->width = h/2;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -h/2,-h/2,-h/2, // triangle 1 : begin
        -h/2,-h/2, h/2,
        -h/2, h/2, h/2, // triangle 1 : end
        h/2, h/2,-h/2, // triangle 2 : begin
        -h/2,-h/2,-h/2,
        -h/2, h/2,-h/2, // triangle 2 : end
        h/2,-h/2, h/2,
        -h/2,-h/2,-h/2,
        h/2,-h/2,-h/2,
        h/2, h/2,-h/2,
        h/2,-h/2,-h/2,
        -h/2,-h/2,-h/2,
        -h/2,-h/2,-h/2,
        -h/2, h/2, h/2,
        -h/2, h/2,-h/2,
        h/2,-h/2, h/2,
        -h/2,-h/2, h/2,
        -h/2,-h/2,-h/2,
        -h/2, h/2, h/2,
        -h/2,-h/2, h/2,
        h/2,-h/2, h/2,
        h/2, h/2, h/2,
        h/2,-h/2,-h/2,
        h/2, h/2,-h/2,
        h/2,-h/2,-h/2,
        h/2, h/2, h/2,
        h/2,-h/2, h/2,
        h/2, h/2, h/2,
        h/2, h/2,-h/2,
        -h/2, h/2,-h/2,
        h/2, h/2, h/2,
        -h/2, h/2,-h/2,
        -h/2, h/2, h/2,
        h/2, h/2, h/2,
        -h/2, h/2, h/2,
        h/2,-h/2, h/2
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_HOT_RED, GL_FILL);
}

void Bomb::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Bomb::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Bomb::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
void Bomb::fall_down(){
    this->position.y -= 0.025;
}


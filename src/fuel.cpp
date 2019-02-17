#include "fuel.h"
#include "main.h"

Fuel::Fuel(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    float speed = 0.5;
    float h = 0.2;
    float height,width,depth;
    height = width = depth = 2*h;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        -width/2.0f ,-height/2.0f ,-depth/2.0f, // triangle 1 : begin
        -width/2.0f ,-height/2.0f , depth/2.0f,
        -width/2.0f , height/2.0f , depth/2.0f, // triangle 1 : end

        width/2.0f , height/2.0f ,-depth/2.0f, // triangle 2 : begin
        -width/2.0f ,-height/2.0f ,-depth/2.0f,
        -width/2.0f , height/2.0f ,-depth/2.0f, // triangle 2 : end

        width/2.0f ,-height/2.0f , depth/2.0f,
        -width/2.0f ,-height/2.0f ,-depth/2.0f,
        width/2.0f ,-height/2.0f ,-depth/2.0f,

        width/2.0f , height/2.0f ,-depth/2.0f,
        width/2.0f ,-height/2.0f ,-depth/2.0f,
        -width/2.0f ,-height/2.0f ,-depth/2.0f,

        -width/2.0f ,-height/2.0f ,-depth/2.0f,
        -width/2.0f , height/2.0f , depth/2.0f,
        -width/2.0f , height/2.0f ,-depth/2.0f,

        width/2.0f ,-height/2.0f , depth/2.0f,
        -width/2.0f ,-height/2.0f , depth/2.0f,
        -width/2.0f ,-height/2.0f ,-depth/2.0f,

        -width/2.0f , height/2.0f , depth/2.0f,
        -width/2.0f ,-height/2.0f , depth/2.0f,
        width/2.0f ,-height/2.0f , depth/2.0f,

        width/2.0f , height/2.0f , depth/2.0f,
        width/2.0f ,-height/2.0f ,-depth/2.0f,
        width/2.0f , height/2.0f ,-depth/2.0f,

        width/2.0f ,-height/2.0f ,-depth/2.0f,
        width/2.0f , height/2.0f , depth/2.0f,
        width/2.0f ,-height/2.0f , depth/2.0f,

        width/2.0f , height/2.0f , depth/2.0f,
        width/2.0f , height/2.0f ,-depth/2.0f,
        -width/2.0f , height/2.0f ,-depth/2.0f,

        width/2.0f , height/2.0f , depth/2.0f,
        -width/2.0f , height/2.0f ,-depth/2.0f,
        -width/2.0f , height/2.0f , depth/2.0f,

        width/2.0f , height/2.0f , depth/2.0f,
        -width/2.0f , height/2.0f , depth/2.0f,
        width/2.0f ,-height/2.0f , depth/2.0f
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_NEON, GL_FILL);
}

void Fuel::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Fuel::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Fuel::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

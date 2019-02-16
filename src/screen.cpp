#include "screen.h"
#include "main.h"


using namespace std;

Screen::Screen(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    float r =1200;
    GLfloat vertex_buffer_data[] = {
        -r,0.0f,r, // triangle 1 : begin
        r,0.0f,r, 
         -r,0.0f, -r, // triangle 1 : end
        -r,0.0f, -r, // triangle 2 : begin
        r,0.0f,-r,
        r,0.0f, r // triangle 2 : end
    };
    this->object_clear = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_SEA, GL_FILL);
}

void Screen::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    //rotate          = rotate * glm::translate(glm::vec3(0, 5.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_clear);
}

float Screen::ret_x(){
    return this->position.x;
}
float Screen::ret_y(){
    return this->position.y;
}
float Screen::ret_z(){
    return this->position.z;
}

#include "comp_stick.h"
#include "main.h"

Compsticks::Compsticks(float x, float y,float r1) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    this->radius = r1;
    double r=this->radius;
    //this->platform_y = platform_y+0.45*r;
    //this->ceiling_y = ceiling_y-0.45*this->radius;
    //this->rotation = 0;
    const double PI = 3.141592;
    
	int n = 50;
    int i;
    //black Rings on top
    float h = 0.05;
    float R = r;
	
    float rx = 2.5*r/4;
     GLfloat vertex_buffer_data[] = {
        0.0f,3*rx,0.0f, // triangle 1 : begin
        -rx,0.0f, 0.0f,
        rx, 0.0f, 0.0f, // triangle 1 : end
        
    };
    GLfloat vertex_buffer_data_1[] = {
                         // triangle 1 : end
        rx, 0.0f,0.0f, // triangle 2 : begin
        -rx,0.0f,0.0f,
        0.0f, -3*rx,0.0f, // triangle 2 : end
    };
    //this->object_outer_base = create3DObject(GL_TRIANGLES, 3*n, circle_vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object_outer_top = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_BRIGHT_RED, GL_FILL);
    this->object_outer_base = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_1, COLOR_SMOKE, GL_FILL);
    //this->object_outer_c1 = create3DObject(GL_TRIANGLES, 3*n, Rings_tr1_vertex_buffer_data, COLOR_BLACK, GL_FILL);
}

void Compsticks::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation*M_PI/180.0f ), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate*rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    //draw3DObject(this->object_inner_top);
    draw3DObject(this->object_outer_top);
    draw3DObject(this->object_outer_base);
}

void Compsticks::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Compsticks::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

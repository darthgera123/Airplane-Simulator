#include "rings.h"
#include "main.h"

Rings::Rings(float x, float y,float z,float r1,float h) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 90;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    double r=r1;
    this->position = glm::vec3(x, y, z);
    //this->platform_y = platform_y+0.45*r;
    //this->ceiling_y = ceiling_y-0.45*this->radius;
    //this->rotation = 0;
    const double PI = 3.141592;
    
	int n = 50;
    int i;
    //black Rings on top
    float H = h/10;
    float R = r/10;
    R= 6*R/7;
    this->radius = R;
    //R= R/2;
    //inner rings
    GLfloat inner_circle_vertex_buffer_data[30*n];
    GLfloat inner_tr1_vertex_buffer_data[30*n];
    float ry = 24*R/25;
    for(i=0;i<n;i++)
	{
		inner_circle_vertex_buffer_data[18*i] =ry*cos(2*((i+1)%n)*(PI/n));
		inner_circle_vertex_buffer_data[18*i+1] = ry*sin(2*((i+1)%n)*(PI/n));
		inner_circle_vertex_buffer_data[18*i+2] =0.0f+2*h+0.01f;
		
		inner_circle_vertex_buffer_data[18*i+3] =R*cos(2*(PI/n)*i);
		inner_circle_vertex_buffer_data[18*i+4] =R*sin(2*(PI/n)*i);
		inner_circle_vertex_buffer_data[18*i+5] =0.0f+2*h+0.01f;
		
		inner_circle_vertex_buffer_data[18*i+6] =R*cos(2*((i+1)%n)*(PI/n));
		inner_circle_vertex_buffer_data[18*i+7] =R*sin(2*((i+1)%n)*(PI/n));
		inner_circle_vertex_buffer_data[18*i+8] =0.0f+2*h+0.01f;

        inner_circle_vertex_buffer_data[18*i+9] =R*cos(2*((i+1)%n)*(PI/n));
		inner_circle_vertex_buffer_data[18*i+10] =R*sin(2*((i+1)%n)*(PI/n));
		inner_circle_vertex_buffer_data[18*i+11] =0.0f+2*h+0.01f;

        inner_circle_vertex_buffer_data[18*i+12] =R*cos(2*(PI/n)*i);
		inner_circle_vertex_buffer_data[18*i+13] =R*sin(2*(PI/n)*i);
		inner_circle_vertex_buffer_data[18*i+14] =0.0f+2*h+0.01f;

        inner_circle_vertex_buffer_data[18*i+15] =ry*cos(2*(PI/n)*i);
		inner_circle_vertex_buffer_data[18*i+16] =ry*sin(2*(PI/n)*i);
		inner_circle_vertex_buffer_data[18*i+17] =0.0f+2*h+0.01f;
        
    }     
    GLfloat inner_base_vertex_buffer_data[30*n];
    // GLfloat inner_tr2_vertex_buffer_data[30*n];
    this->object_inner_base = create3DObject(GL_TRIANGLES, 6*n, inner_circle_vertex_buffer_data, COLOR_SMOKE, GL_FILL);
    
}

void Rings::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (-this->rotation ), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate*rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    draw3DObject(this->object_inner_base);
    
}

void Rings::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Rings::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
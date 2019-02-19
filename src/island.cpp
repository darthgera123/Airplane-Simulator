#include "island.h"
#include "main.h"

Island::Island(float x, float y,float z,float r1) {
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
    this->radius = r1;
    //R= R/2;
    //inner rings
    GLfloat circle_vertex_buffer_data[30*n];
    GLfloat inner_tr1_vertex_buffer_data[30*n];
    for(i=0;i<n;i++)
	{
		circle_vertex_buffer_data[9*i] =0.0f;
		circle_vertex_buffer_data[9*i+1] =0.0f;
		circle_vertex_buffer_data[9*i+2] = 0.0f;
		
		circle_vertex_buffer_data[9*i+3] =r*cos(2*(PI/n)*i);
		circle_vertex_buffer_data[9*i+4] =0.0f;
		circle_vertex_buffer_data[9*i+5] =r*sin(2*(PI/n)*i);
		
		circle_vertex_buffer_data[9*i+6] =r*cos(2*((i+1)%n)*(PI/n));
		circle_vertex_buffer_data[9*i+7] =0.0f;
		circle_vertex_buffer_data[9*i+8] =r*sin(2*((i+1)%n)*(PI/n));
        
    }     
    GLfloat inner_base_vertex_buffer_data[30*n];
    // GLfloat inner_tr2_vertex_buffer_data[30*n];
    this->object_inner_base = create3DObject(GL_TRIANGLES, 3*n, circle_vertex_buffer_data, COLOR_FOREST, GL_FILL);
    
}

void Island::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (-this->rotation ), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    draw3DObject(this->object_inner_base);
    
}

void Island::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Island::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
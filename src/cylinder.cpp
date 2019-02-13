#include "cylinder.h"
#include "main.h"

Cylinder::Cylinder(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    double r=0.40;
    this->position = glm::vec3(x, y, 0);
    //this->platform_y = platform_y+0.45*r;
    //this->ceiling_y = ceiling_y-0.45*this->radius;
    //this->rotation = 0;
    const double PI = 3.141592;
    
	int n = 50;
	GLfloat circle_vertex_buffer_data[30*n];
    GLfloat tr1_vertex_buffer_data[30*n];
    GLfloat tr2_vertex_buffer_data[30*n];
    int i;
    for(i=0;i<n;i++)
	{
		circle_vertex_buffer_data[9*i] =0.0f;
		circle_vertex_buffer_data[9*i+1] =0.0f;
		circle_vertex_buffer_data[9*i+2] = 0.0f;
		
		circle_vertex_buffer_data[9*i+3] =r*cos(2*(PI/n)*i);
		circle_vertex_buffer_data[9*i+4] =r*sin(2*(PI/n)*i);
		circle_vertex_buffer_data[9*i+5] =0.0f;
		
		circle_vertex_buffer_data[9*i+6] =r*cos(2*((i+1)%n)*(PI/n));
		circle_vertex_buffer_data[9*i+7] =r*sin(2*((i+1)%n)*(PI/n));
		circle_vertex_buffer_data[9*i+8] =0.0f;
        tr1_vertex_buffer_data[9*i] = r*cos(2*(PI/n)*i);
        tr1_vertex_buffer_data[9*i+1] = r*sin(2*(PI/n)*i);
        tr1_vertex_buffer_data[9*i+2] = 0.0f;
        tr1_vertex_buffer_data[9*i+3] = r*cos(2*((i+1)%n)*(PI/n));
        tr1_vertex_buffer_data[9*i+4] = r*sin(2*((i+1)%n)*(PI/n));
        tr1_vertex_buffer_data[9*i+5] = 0.0f;
        tr1_vertex_buffer_data[9*i+6] = r*cos(2*(PI/n)*i);
        tr1_vertex_buffer_data[9*i+7] = r*sin(2*(PI/n)*i);
        tr1_vertex_buffer_data[9*i+8] = 4*r;
        
    }     
    GLfloat base_vertex_buffer_data[30*n];
    for(i=0;i<n;i++)
	{
		base_vertex_buffer_data[9*i] =0.0f;
		base_vertex_buffer_data[9*i+1] =0.0f;
		base_vertex_buffer_data[9*i+2] = 4*r;
		
		base_vertex_buffer_data[9*i+3] =r*cos(2*(PI/n)*i);
		base_vertex_buffer_data[9*i+4] =r*sin(2*(PI/n)*i);
		base_vertex_buffer_data[9*i+5] =4*r;
		
		base_vertex_buffer_data[9*i+6] =r*cos(2*((i+1)%n)*(PI/n));
		base_vertex_buffer_data[9*i+7] =r*sin(2*((i+1)%n)*(PI/n));
		base_vertex_buffer_data[9*i+8] =4*r;
        
        tr2_vertex_buffer_data[9*i] = r*cos(2*(PI/n)*i);
        tr2_vertex_buffer_data[9*i+1] = r*sin(2*(PI/n)*i);
        tr2_vertex_buffer_data[9*i+2] = 4*r;
        tr2_vertex_buffer_data[9*i+3] = r*cos(2*((i+1)%n)*(PI/n));
        tr2_vertex_buffer_data[9*i+4] = r*sin(2*((i+1)%n)*(PI/n));
        tr2_vertex_buffer_data[9*i+5] = 4*r;
        tr2_vertex_buffer_data[9*i+6] = r*cos(2*((i+1)%n)*(PI/n));
        tr2_vertex_buffer_data[9*i+7] = r*sin(2*((i+1)%n)*(PI/n));
        tr2_vertex_buffer_data[9*i+8] = 0.0f;
    }       
    this->object_1 = create3DObject(GL_TRIANGLES, 3*n, circle_vertex_buffer_data, COLOR_RED, GL_FILL);
    this->object_2 = create3DObject(GL_TRIANGLES, 3*n, base_vertex_buffer_data, COLOR_GREEN, GL_FILL);
    this->object_tr1 = create3DObject(GL_TRIANGLES, 3*n, tr1_vertex_buffer_data, COLOR_BLACK, GL_LINE);
    this->object_tr2 = create3DObject(GL_TRIANGLES, 3*n, tr2_vertex_buffer_data, COLOR_BLACK, GL_LINE);
}

void Cylinder::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_1);
    draw3DObject(this->object_2);
    draw3DObject(this->object_tr1);
    draw3DObject(this->object_tr2);
    
}

void Cylinder::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Cylinder::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
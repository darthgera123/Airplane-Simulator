#include "dashboard.h"
#include "main.h"

Dashboard::Dashboard(float x, float y,float r1,int type) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 30*M_PI/180.0f;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    this->radius = r1;
    double r=this->radius;
    this->position = glm::vec3(x, y, 0);
    //this->platform_y = platform_y+0.45*r;
    //this->ceiling_y = ceiling_y-0.45*this->radius;
    //this->rotation = 0;
    const double PI = 3.141592;
    
	int n = 50;
    int i;
    //black Rings on top
    float h = 0.05;
    float R = r;
	GLfloat circle_vertex_buffer_data[30*n];
    GLfloat Rings_tr1_vertex_buffer_data[30*n];
    for(i=0;i<n;i++)
	{
		circle_vertex_buffer_data[9*i] =0.0f;
		circle_vertex_buffer_data[9*i+1] = 0.0f;
		circle_vertex_buffer_data[9*i+2] =0.0f;
		
		circle_vertex_buffer_data[9*i+3] =R*cos(2*(PI/n)*i);
		circle_vertex_buffer_data[9*i+4] =R*sin(2*(PI/n)*i);
		circle_vertex_buffer_data[9*i+5] =0.0f;
		
		circle_vertex_buffer_data[9*i+6] =R*cos(2*((i+1)%n)*(PI/n));
		circle_vertex_buffer_data[9*i+7] =R*sin(2*((i+1)%n)*(PI/n));
		circle_vertex_buffer_data[9*i+8] =0.0f;
        
    }     
    GLfloat Rings_base_vertex_buffer_data[30*n];
    R= 2.5*R/4;
    //inner rings
    GLfloat inner_circle_vertex_buffer_data[30*n];
    for(i=0;i<n;i++)
	{
		inner_circle_vertex_buffer_data[9*i] =0.0f;
		inner_circle_vertex_buffer_data[9*i+1] = 0.0f;
		inner_circle_vertex_buffer_data[9*i+2] =0.0f;
		
		inner_circle_vertex_buffer_data[9*i+3] =R*cos(2*(PI/n)*i);
		inner_circle_vertex_buffer_data[9*i+4] =R*sin(2*(PI/n)*i);
		inner_circle_vertex_buffer_data[9*i+5] =0.0f;
		
		inner_circle_vertex_buffer_data[9*i+6] =R*cos(2*((i+1)%n)*(PI/n));
		inner_circle_vertex_buffer_data[9*i+7] =R*sin(2*((i+1)%n)*(PI/n));
		inner_circle_vertex_buffer_data[9*i+8] =0.0f;
        
    }
    R = 10*R/11;
    GLfloat inner_base_vertex_buffer_data[30*n];
    // GLfloat inner_tr2_vertex_buffer_data[30*n];
    for(i=0;i<n;i++)
	{
		inner_base_vertex_buffer_data[9*i] =0.0f;
		inner_base_vertex_buffer_data[9*i+1] = 0.0f;
		inner_base_vertex_buffer_data[9*i+2] =0.0f;
		
		inner_base_vertex_buffer_data[9*i+3] =R*cos(2*(PI/n)*i);
		inner_base_vertex_buffer_data[9*i+4] =R*sin(2*(PI/n)*i);
		inner_base_vertex_buffer_data[9*i+5] =0.0f;
		
		inner_base_vertex_buffer_data[9*i+6] =R*cos(2*((i+1)%n)*(PI/n));
		inner_base_vertex_buffer_data[9*i+7] =R*sin(2*((i+1)%n)*(PI/n));
		inner_base_vertex_buffer_data[9*i+8] =0.0f;
        
    }
    float rx = 2.5*r/4;
     GLfloat vertex_buffer_data[] = {
        -rx,-rx,0.0f, // triangle 1 : begin
        rx,-rx, 0.0f,
        -rx, 0.0f, 0.0f, // triangle 1 : end
        -rx, 0.0f,0.0f, // triangle 2 : begin
        rx,0.0f,0.0f,
        rx, -rx,0.0f, // triangle 2 : end
    };
    this->radius_rx = rx;
    this->object_outer_base = create3DObject(GL_TRIANGLES, 3*n, circle_vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object_outer_top = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    if(type == 1)
        this->object_inner_base = create3DObject(GL_TRIANGLES, 3*n, inner_circle_vertex_buffer_data, COLOR_NEON, GL_FILL);
    else if(type==2)
        this->object_inner_base = create3DObject(GL_TRIANGLES, 3*n, inner_circle_vertex_buffer_data, COLOR_NEON_YELLOW, GL_FILL);
    this->object_inner_top = create3DObject(GL_TRIANGLES, 3*n, inner_base_vertex_buffer_data, COLOR_BLACK, GL_FILL);
}

void Dashboard::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (-this->rotation ), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_outer_base);
    draw3DObject(this->object_inner_base);
    draw3DObject(this->object_inner_top);
    draw3DObject(this->object_outer_top);
    //draw3DObject(this->object_outer_c1);
}

void Dashboard::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Dashboard::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
void Dashboard::change_angle() {
    this->rotation -= 30.0*M_PI/180.0f;
}
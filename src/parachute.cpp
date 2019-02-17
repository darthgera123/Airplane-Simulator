#include "parachute.h"
#include "main.h"

Parachute::Parachute(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
    this->speed_dir = glm::vec3(speed_dir);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    this->radius = 0.05;
    double r=this->radius;
    const double PI = 3.141592;
    int n = 50;
    this->speed = 0.1;
    //black shooter on top
    int i;
	GLfloat circle_vertex_buffer_data_cone[30*n];
    for(i=0;i<n;i++)
	{
		circle_vertex_buffer_data_cone[9*i] =0.0f;
		circle_vertex_buffer_data_cone[9*i+1] = 0.0f+r;
		circle_vertex_buffer_data_cone[9*i+2] =0.0f;
		
		circle_vertex_buffer_data_cone[9*i+3] =4*r*cos(2*(PI/n)*i);
		circle_vertex_buffer_data_cone[9*i+4] =0.0f+3*r;
		circle_vertex_buffer_data_cone[9*i+5] =4*r*sin(2*(PI/n)*i);
		
		circle_vertex_buffer_data_cone[9*i+6] =4*r*cos(2*((i+1)%n)*(PI/n));
		circle_vertex_buffer_data_cone[9*i+7] =0.0f+3*r;
		circle_vertex_buffer_data_cone[9*i+8] =4*r*sin(2*((i+1)%n)*(PI/n));
    }  
    GLfloat top_vertex_buffer_data_cone[30*n];
    for(i=0;i<n;i++)
	{
		top_vertex_buffer_data_cone[9*i] =0.0f;
		top_vertex_buffer_data_cone[9*i+1] = 0.0f+5*r;
		top_vertex_buffer_data_cone[9*i+2] =0.0f;
		
		top_vertex_buffer_data_cone[9*i+3] =4*r*cos(2*(PI/n)*i);
		top_vertex_buffer_data_cone[9*i+4] =0.0f+3*r;
		top_vertex_buffer_data_cone[9*i+5] =4*r*sin(2*(PI/n)*i);
		
		top_vertex_buffer_data_cone[9*i+6] =4*r*cos(2*((i+1)%n)*(PI/n));
		top_vertex_buffer_data_cone[9*i+7] =0.0f+3*r;
		top_vertex_buffer_data_cone[9*i+8] =4*r*sin(2*((i+1)%n)*(PI/n));
    }     
    GLfloat vertex_buffer_data[90000];
    int sides = 100;
    float angle = (2*M_PI)/float(sides);
    float radius = r;
    for(int j=0;j<sides;j++)
        for(int i=0;i<sides;i++)
        {
            int k = sides*i + j;
            vertex_buffer_data[9*k] = 0.0f;
            vertex_buffer_data[9*k + 1] = 0.0f;  
            vertex_buffer_data[9*k + 2] = radius*sin(j*angle);
            vertex_buffer_data[9*k + 3] = radius*cos(i*angle)*cos(j*angle); 
            vertex_buffer_data[9*k + 4] = radius*sin(i*angle)*cos(j*angle);
            vertex_buffer_data[9*k + 5] = radius*sin(j*angle); 
            vertex_buffer_data[9*k + 6] = radius*cos((i+1)*angle)*cos(j*angle); 
            vertex_buffer_data[9*k + 7] = radius*sin((i+1)*angle)*cos(j*angle); 
            vertex_buffer_data[9*k + 8] = radius*sin(j*angle); 
        }
    this->object_parachute_base = create3DObject(GL_TRIANGLES, sides*sides*3, vertex_buffer_data, COLOR_RUBY, GL_FILL);
    this->object_parachute_top = create3DObject(GL_TRIANGLES, 3*n, circle_vertex_buffer_data_cone, COLOR_BLACK, GL_LINE);
    this->object_parachute_tip = create3DObject(GL_TRIANGLES, 3*n, top_vertex_buffer_data_cone, COLOR_PURPLE, GL_FILL);
    // this->object_missile_c1 = create3DObject(GL_TRIANGLES, 3*n, tr1_vertex_buffer_data, COLOR_NEON_YELLOW, GL_FILL);
    // this->object_missile_c2 = create3DObject(GL_TRIANGLES, 3*n, tr2_vertex_buffer_data, COLOR_NEON_YELLOW, GL_FILL);
    // this->object_missile_top = create3DObject(GL_TRIANGLES, 3*n, circle_vertex_buffer_data_cone, COLOR_RUBY, GL_FILL);

}

void Parachute::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (-this->rotation ), glm::vec3(0, 1, 0));
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate*this->rotation);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_parachute_top);
    draw3DObject(this->object_parachute_base);
    draw3DObject(this->object_parachute_tip);
    // draw3DObject(this->object_parachute_c1);
    // draw3DObject(this->object_parachute_c2);
    // draw3DObject(this->object_parachute_top);
    
}


void Parachute::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
void Parachute::fall_down(){
    this->position.y -= 0.01;
}

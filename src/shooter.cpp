#include "shooter.h"
#include "main.h"

Shooter::Shooter(float x, float y,float z,float r1,float h) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    this->radius = r1;
    double r=this->radius;
    this->position = glm::vec3(x, y, z);
    //this->platform_y = platform_y+0.45*r;
    //this->ceiling_y = ceiling_y-0.45*this->radius;
    //this->rotation = 0;
    const double PI = 3.141592;
    
	int n = 50;
    int i;
    //black shooter on top
    float H = h/2;
    float R = r/20;
	GLfloat shooter_circle_vertex_buffer_data[30*n];
    GLfloat shooter_tr1_vertex_buffer_data[30*n];
    for(i=0;i<n;i++)
	{
		shooter_circle_vertex_buffer_data[9*i] =0.0f;
		shooter_circle_vertex_buffer_data[9*i+1] =0.0f+2*h;
		shooter_circle_vertex_buffer_data[9*i+2] = 0.0f;
		
		shooter_circle_vertex_buffer_data[9*i+3] =R*cos(2*(PI/n)*i);
		shooter_circle_vertex_buffer_data[9*i+4] =0.0f+2*h;
		shooter_circle_vertex_buffer_data[9*i+5] =R*sin(2*(PI/n)*i);
		
		shooter_circle_vertex_buffer_data[9*i+6] =R*cos(2*((i+1)%n)*(PI/n));
		shooter_circle_vertex_buffer_data[9*i+7] =0.0f+2*h;
		shooter_circle_vertex_buffer_data[9*i+8] =R*sin(2*((i+1)%n)*(PI/n));
        
        shooter_tr1_vertex_buffer_data[9*i] = R*cos(2*(PI/n)*i);
        shooter_tr1_vertex_buffer_data[9*i+1] = 0.0f+2*h;
        shooter_tr1_vertex_buffer_data[9*i+2] =R*sin(2*(PI/n)*i);
        shooter_tr1_vertex_buffer_data[9*i+3] = R*cos(2*((i+1)%n)*(PI/n));
        shooter_tr1_vertex_buffer_data[9*i+4] = 0.0f+2*h;
        shooter_tr1_vertex_buffer_data[9*i+5] = R*sin(2*((i+1)%n)*(PI/n));
        shooter_tr1_vertex_buffer_data[9*i+6] = R*cos(2*(PI/n)*i);
        shooter_tr1_vertex_buffer_data[9*i+7] = 0.0f+2*h+2*H;
        shooter_tr1_vertex_buffer_data[9*i+8] = R*sin(2*(PI/n)*i);
        
    }     
    GLfloat shooter_base_vertex_buffer_data[30*n];
    GLfloat shooter_tr2_vertex_buffer_data[30*n];
    for(i=0;i<n;i++)
	{
		shooter_base_vertex_buffer_data[9*i] =0.0f;
		shooter_base_vertex_buffer_data[9*i+1] =0.0f+2*h+2*H;
		shooter_base_vertex_buffer_data[9*i+2] = 0.0f;
		
		shooter_base_vertex_buffer_data[9*i+3] =R*cos(2*(PI/n)*i);
		shooter_base_vertex_buffer_data[9*i+4] =0.0f+2*h+2*H;
		shooter_base_vertex_buffer_data[9*i+5] =R*sin(2*(PI/n)*i);
		
		shooter_base_vertex_buffer_data[9*i+6] =R*cos(2*((i+1)%n)*(PI/n));
		shooter_base_vertex_buffer_data[9*i+7] =0.0f+2*h+2*H;
		shooter_base_vertex_buffer_data[9*i+8] =R*sin(2*((i+1)%n)*(PI/n));
        
        shooter_tr2_vertex_buffer_data[9*i] = R*cos(2*(PI/n)*i);
        shooter_tr2_vertex_buffer_data[9*i+1] = 0.0f+2*h+2*H;
        shooter_tr2_vertex_buffer_data[9*i+2] =R*sin(2*(PI/n)*i);
        shooter_tr2_vertex_buffer_data[9*i+3] = R*cos(2*((i+1)%n)*(PI/n));
        shooter_tr2_vertex_buffer_data[9*i+4] = 0.0f+2*h+2*H;
        shooter_tr2_vertex_buffer_data[9*i+5] = R*sin(2*((i+1)%n)*(PI/n));
        shooter_tr2_vertex_buffer_data[9*i+6] = R*cos(2*((i+1)%n)*(PI/n));
        shooter_tr2_vertex_buffer_data[9*i+7] = 0.0f+2*h;
        shooter_tr2_vertex_buffer_data[9*i+8] = R*sin(2*((i+1)%n)*(PI/n));
    }
    
    this->object_shooter_base = create3DObject(GL_TRIANGLES, 3*n, shooter_circle_vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object_shooter_top = create3DObject(GL_TRIANGLES, 3*n, shooter_base_vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object_shooter_c1 = create3DObject(GL_TRIANGLES, 3*n, shooter_tr1_vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object_shooter_c2 = create3DObject(GL_TRIANGLES, 3*n, shooter_tr2_vertex_buffer_data, COLOR_BLACK, GL_FILL);
}

void Shooter::draw(glm::vec3 t,glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    float dot = 0*t.x+1*t.y+0*t.z;
    dot = ( dot < -1.0 ? -1.0 : ( dot > 1.0 ? 1.0 : dot ) );
    float len1 = 1;
    float len2 = t.x*t.x+t.y*t.y+t.z*t.z;
    float angle = acos(dot/sqrt(len1*len2));
    this->rotation = angle;
    if(angle == NAN){
        angle = M_PI/2;
    }
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (-this->rotation ), glm::vec3(0, 1, 0));
    this->rotation = 0;
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate*rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_shooter_base);
    draw3DObject(this->object_shooter_top);
    draw3DObject(this->object_shooter_c1);
    draw3DObject(this->object_shooter_c2);
}

void Shooter::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Shooter::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
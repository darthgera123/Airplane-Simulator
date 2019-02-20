#include "shooter.h"
#include "main.h"

Shooter::Shooter(float x, float y,float z,float r1,float h) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    this->actual_radius = r1;
    double r=this->actual_radius;
    this->position = glm::vec3(x, y, z);
    //this->platform_y = platform_y+0.45*r;
    //this->ceiling_y = ceiling_y-0.45*this->radius;
    //this->rotation = 0;
    const double PI = 3.141592;
    
	int n = 50;
    int i;
    //black shooter on top
    float H = h/2;
    float R = r/10;
    this->radius =R;
    this->height = H;
	GLfloat shooter_circle_vertex_buffer_data[30*n];
    GLfloat shooter_tr1_vertex_buffer_data[30*n];
    for(i=0;i<n;i++)
	{
		shooter_circle_vertex_buffer_data[9*i] =0.0f;
		shooter_circle_vertex_buffer_data[9*i+1] =0.0f+0.01f;
		shooter_circle_vertex_buffer_data[9*i+2] = 0.0f;
		
		shooter_circle_vertex_buffer_data[9*i+3] =R*cos(2*(PI/n)*i);
		shooter_circle_vertex_buffer_data[9*i+4] =0.0f+0.01f;
		shooter_circle_vertex_buffer_data[9*i+5] =R*sin(2*(PI/n)*i);
		
		shooter_circle_vertex_buffer_data[9*i+6] =R*cos(2*((i+1)%n)*(PI/n));
		shooter_circle_vertex_buffer_data[9*i+7] =0.0f+0.01f;
		shooter_circle_vertex_buffer_data[9*i+8] =R*sin(2*((i+1)%n)*(PI/n));
        
        shooter_tr1_vertex_buffer_data[9*i] = R*cos(2*(PI/n)*i);
        shooter_tr1_vertex_buffer_data[9*i+1] = 0.0f;
        shooter_tr1_vertex_buffer_data[9*i+2] =R*sin(2*(PI/n)*i);
        shooter_tr1_vertex_buffer_data[9*i+3] = R*cos(2*((i+1)%n)*(PI/n));
        shooter_tr1_vertex_buffer_data[9*i+4] = 0.0f;
        shooter_tr1_vertex_buffer_data[9*i+5] = R*sin(2*((i+1)%n)*(PI/n));
        shooter_tr1_vertex_buffer_data[9*i+6] = R*cos(2*(PI/n)*i);
        shooter_tr1_vertex_buffer_data[9*i+7] = 0.0f+2*H;
        shooter_tr1_vertex_buffer_data[9*i+8] = R*sin(2*(PI/n)*i);
        
    }     
    GLfloat shooter_base_vertex_buffer_data[30*n];
    GLfloat shooter_tr2_vertex_buffer_data[30*n];
    for(i=0;i<n;i++)
	{
		shooter_base_vertex_buffer_data[9*i] =0.0f;
		shooter_base_vertex_buffer_data[9*i+1] =0.0f+2*H;
		shooter_base_vertex_buffer_data[9*i+2] = 0.0f;
		
		shooter_base_vertex_buffer_data[9*i+3] =R*cos(2*(PI/n)*i);
		shooter_base_vertex_buffer_data[9*i+4] =0.0f+2*H;
		shooter_base_vertex_buffer_data[9*i+5] =R*sin(2*(PI/n)*i);
		
		shooter_base_vertex_buffer_data[9*i+6] =R*cos(2*((i+1)%n)*(PI/n));
		shooter_base_vertex_buffer_data[9*i+7] =0.0f+2*H;
		shooter_base_vertex_buffer_data[9*i+8] =R*sin(2*((i+1)%n)*(PI/n));
        
        shooter_tr2_vertex_buffer_data[9*i] = R*cos(2*(PI/n)*i);
        shooter_tr2_vertex_buffer_data[9*i+1] = 0.0f+2*H;
        shooter_tr2_vertex_buffer_data[9*i+2] =R*sin(2*(PI/n)*i);
        shooter_tr2_vertex_buffer_data[9*i+3] = R*cos(2*((i+1)%n)*(PI/n));
        shooter_tr2_vertex_buffer_data[9*i+4] = 0.0f+2*H;
        shooter_tr2_vertex_buffer_data[9*i+5] = R*sin(2*((i+1)%n)*(PI/n));
        shooter_tr2_vertex_buffer_data[9*i+6] = R*cos(2*((i+1)%n)*(PI/n));
        shooter_tr2_vertex_buffer_data[9*i+7] = 0.0f;
        shooter_tr2_vertex_buffer_data[9*i+8] = R*sin(2*((i+1)%n)*(PI/n));
    }
    
    this->object_shooter_base = create3DObject(GL_TRIANGLES, 3*n, shooter_circle_vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object_shooter_top = create3DObject(GL_TRIANGLES, 3*n, shooter_base_vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object_shooter_c1 = create3DObject(GL_TRIANGLES, 3*n, shooter_tr1_vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object_shooter_c2 = create3DObject(GL_TRIANGLES, 3*n, shooter_tr2_vertex_buffer_data, COLOR_BLACK, GL_FILL);
}

void Shooter::draw(glm::vec3 t,glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::vec3 dir,axis,original;
    original = glm::vec3(0,1,0);
    dir = glm::vec3(t.x-this->position.x, t.y-this->position.y, t.z-this->position.z);
    float dot = 0*dir.x+1*dir.y+0*dir.z;
    float len1 = 1;
    float len2 = dir.x*dir.x+dir.y*dir.y+dir.z*dir.z;
    float len2sqrt = sqrt(len2);
    this->dir = glm::vec3(dir.x/len2sqrt,dir.y/len2sqrt,dir.z/len2sqrt);
    float p = sqrt(this->dir.x*this->dir.x+this->dir.y*this->dir.y+this->dir.z*this->dir.z);
    float angle = acos(dot/sqrt(len1*len2));
    this->rotation = angle;
    float temp_angle = angle*(180.0f/M_PI);
    if(temp_angle >= 90){
        angle = M_PI/2;
    }
    axis = glm::cross(original,dir);
    //std::cout<<axis.x<<" "<<axis.y<<" "<<axis.z<<" "<<angle<<"\n";
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (-this->rotation ), glm::vec3(0, 1, 0));
    this->rotation = angle;
    glm::mat4 rotate    = glm::rotate((float) (this->rotation ), axis);
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
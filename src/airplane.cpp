#include "airplane.h"
#include "main.h"

Airplane::Airplane(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation_x = 0;
    this->rotation_y =0;
    this->rotation_z =0;
    this->dir_rotation =0;
    this->totalRot = glm::mat4(1.0f);
    this->totalUp = glm::mat4(1.0f);
    this->speed = 0.05;
    this->health = 5;
    this->type =1;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    double r=0.30;
    this->radius = r;
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
	GLfloat circle_vertex_buffer_data_cone[30*n];
    for(i=0;i<n;i++)
	{
		circle_vertex_buffer_data_cone[9*i] =0.0f;
		circle_vertex_buffer_data_cone[9*i+1] =0.0f;
		circle_vertex_buffer_data_cone[9*i+2] = 0.0f+6*r;
		
		circle_vertex_buffer_data_cone[9*i+3] =r*cos(2*(PI/n)*i);
		circle_vertex_buffer_data_cone[9*i+4] =r*sin(2*(PI/n)*i);
		circle_vertex_buffer_data_cone[9*i+5] =0.0f+4*r;
		
		circle_vertex_buffer_data_cone[9*i+6] =r*cos(2*((i+1)%n)*(PI/n));
		circle_vertex_buffer_data_cone[9*i+7] =r*sin(2*((i+1)%n)*(PI/n));
		circle_vertex_buffer_data_cone[9*i+8] =0.0f+4*r;
    }     
    GLfloat base_vertex_buffer_data_cone[30*n];
    for(i=0;i<n;i++)
	{
		base_vertex_buffer_data_cone[9*i] =0.0f-0.01f;
		base_vertex_buffer_data_cone[9*i+1] =0.0f-0.01f;
		base_vertex_buffer_data_cone[9*i+2] = 0.0f+0.01f;
		
		base_vertex_buffer_data_cone[9*i+3] =r*cos(2*(PI/n)*i)-0.01f;
		base_vertex_buffer_data_cone[9*i+4] =r*sin(2*(PI/n)*i)-0.01f;
		base_vertex_buffer_data_cone[9*i+5] =0.0f+0.01f;
		
		base_vertex_buffer_data_cone[9*i+6] =r*cos(2*((i+1)%n)*(PI/n))-0.01f;
		base_vertex_buffer_data_cone[9*i+7] =r*sin(2*((i+1)%n)*(PI/n))-0.01f;
		base_vertex_buffer_data_cone[9*i+8] =0.0f+0.01f;
    }
    GLfloat back_vertex_buffer_data_cone[30*n];
    for(i=0;i<n;i++)
	{
		back_vertex_buffer_data_cone[9*i] =0.0f;
		back_vertex_buffer_data_cone[9*i+1] =0.0f;
		back_vertex_buffer_data_cone[9*i+2] = 0.0f-0.5*r;
		
		back_vertex_buffer_data_cone[9*i+3] =r*cos(2*(PI/n)*i);
		back_vertex_buffer_data_cone[9*i+4] =r*sin(2*(PI/n)*i);
		back_vertex_buffer_data_cone[9*i+5] =0.0f;
		
		back_vertex_buffer_data_cone[9*i+6] =r*cos(2*((i+1)%n)*(PI/n));
		back_vertex_buffer_data_cone[9*i+7] =r*sin(2*((i+1)%n)*(PI/n));
		back_vertex_buffer_data_cone[9*i+8] =0.0f;
    }
    GLfloat upper_vertex[] = {
        0.0f-r,0.0f,0.0f+2.5*r, // triangle 1 : begin
        -2.5*r-r,0.0f,0.0f+2.5*r,
        0.0f-r, 0.0f,1*r+3*r,
        0.0f+r,0.0f,0.0f+2.5*r, // triangle 1 : begin
        2.5*r+r,0.0f,0.0f+2.5*r,
        0.0f+r, 0.0f,1*r+3*r// triangle 1 : end
    };
    GLfloat new_vertex[] = {
        0.0f+0.25*r,0.0f+r,0.0f, // triangle 1 : begin
        0.0f+0.25*r,2.5*r,0.0f,
        0.0f+0.25*r, 0.0f+r,r,
         // triangle 1 : end
    };
    color_t body;
    if(type==1){
        body = COLOR_GOLD;
    }
    else{
        body = COLOR_HOT_RED;
    }
    
    this->object_cone = create3DObject(GL_TRIANGLES, 3*n, circle_vertex_buffer_data_cone, COLOR_RED, GL_FILL);
    this->object_cone_base = create3DObject(GL_TRIANGLES, 3*n, base_vertex_buffer_data_cone, COLOR_GOLD, GL_FILL);  
    this->object_1 = create3DObject(GL_TRIANGLES, 3*n, circle_vertex_buffer_data, COLOR_GOLD, GL_FILL);
    this->object_2 = create3DObject(GL_TRIANGLES, 3*n, base_vertex_buffer_data, COLOR_GOLD, GL_FILL);
    this->object_danger_back = create3DObject(GL_TRIANGLES, 3*n, circle_vertex_buffer_data, COLOR_HOT_RED, GL_FILL);
    this->object_tr1 = create3DObject(GL_TRIANGLES, 3*n, tr1_vertex_buffer_data, body, GL_FILL);
    this->object_tr2 = create3DObject(GL_TRIANGLES, 3*n, tr2_vertex_buffer_data, body, GL_FILL);
    this->object_danger_tr1 = create3DObject(GL_TRIANGLES, 3*n, tr1_vertex_buffer_data, COLOR_HOT_RED, GL_FILL);
    this->object_danger_tr2 = create3DObject(GL_TRIANGLES, 3*n, tr2_vertex_buffer_data, COLOR_HOT_RED, GL_FILL);
    this->object_wings = create3DObject(GL_TRIANGLES, 6, upper_vertex, COLOR_GREEN, GL_FILL);
    this->object_tail = create3DObject(GL_TRIANGLES, 3, new_vertex, COLOR_GREEN, GL_FILL);
    this->object_back = create3DObject(GL_TRIANGLES, 3*n,back_vertex_buffer_data_cone, COLOR_RED, GL_FILL);
}

void Airplane::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 yaw    = glm::rotate((float) (this->rotation_z * M_PI / 180.0f), glm::vec3(0,0,1));
    glm::mat4 roll    = glm::rotate((float) (this->rotation_y * M_PI / 180.0f), glm::vec3(0,1,0));
    glm::mat4 pitch    = glm::rotate((float) (this->rotation_x * M_PI / 180.0f), glm::vec3(1,0,0));
    this->totalRot *= yaw*pitch*roll;
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * this->totalRot);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_2);
    
    if(this->type==1){
        draw3DObject(this->object_tr1);
        draw3DObject(this->object_tr2);
        draw3DObject(this->object_1);
    }else{
        draw3DObject(this->object_danger_tr1);
        draw3DObject(this->object_danger_tr2);
        draw3DObject(this->object_danger_back);
    }
    draw3DObject(this->object_cone);
    draw3DObject(this->object_cone_base);
    draw3DObject(this->object_wings);
    draw3DObject(this->object_tail);
}

void Airplane::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}
void Airplane::move_forward(){
    this->position.z += 0.05;
}
void Airplane::fall(){
    this->position.y -= 0.05;
}
void Airplane::lift(){
    this->position.y += 0.05;
}
void Airplane::tilt_left(){
    this->rotation_z += 0.30;
}
void Airplane::tilt_right(){
    this->rotation_z -= 0.30;
}
void Airplane::dive_down(){
    this->rotation_x +=0.30;
}
void Airplane::dive_up(){
    this->rotation_x -=0.30;
}
void Airplane::move_left(){
    this->rotation_y += 0.60;
}
void Airplane::move_right(){
    this->rotation_y -= 0.60;
}
void Airplane::reset_rotation(){
    this->rotation_x =0;
    this->rotation_y=0;
    this->rotation_z=0;
}
glm::vec4 Airplane::set_eye(glm::vec4 E){
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position); // glTranslatef
    glm::mat4 yaw    = glm::rotate((float) (-this->rotation_z * M_PI / 180.0f), glm::vec3(0,0,1));
    glm::mat4 roll    = glm::rotate((float) (this->rotation_y * M_PI / 180.0f), glm::vec3(0,1,0));
    glm::mat4 pitch    = glm::rotate((float) (this->rotation_x * M_PI / 180.0f), glm::vec3(1,0,0));
    glm::vec4 ans = translate*this->totalRot*E;
    //glm::vec4 ans = (this->totalRot*E);
    return ans;
}
glm::vec4 Airplane::set_speed(glm::vec4 S){
    Matrices.model = glm::mat4(1.0f);
    //glm::mat4 translate = glm::translate (this->position); // glTranslatef
    glm::mat4 yaw    = glm::rotate((float) (this->rotation_z * M_PI / 180.0f), glm::vec3(0,0,1));
    glm::mat4 roll    = glm::rotate((float) (this->rotation_y * M_PI / 180.0f), glm::vec3(0,1,0));
    glm::mat4 pitch    = glm::rotate((float) (this->rotation_x * M_PI / 180.0f), glm::vec3(1,0,0));
    //glm::vec4 ans = this->totalRot*S;
    glm::vec4 ans = (yaw*pitch*roll*S);
    return ans;
}
glm::vec4 Airplane::set_top(glm::vec4 T){
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position); // glTranslatef
    //glm::vec4 ans = this->totalRot*S;
    glm::vec4 ans = (translate*T);
    return ans;
}
glm::vec4 Airplane::set_up(glm::vec4 U){
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position); // glTranslatef
    glm::mat4 yaw    = glm::rotate((float) (this->rotation_z * M_PI / 180.0f), glm::vec3(0,0,1));
    glm::mat4 roll    = glm::rotate((float) (this->rotation_y * M_PI / 180.0f), glm::vec3(0,1,0));
    glm::mat4 pitch    = glm::rotate((float) (this->rotation_x * M_PI / 180.0f), glm::vec3(1,0,0));
    this->totalUp *= yaw;
    glm::vec4 ans = this->totalUp*U;
    //glm::vec4 ans = (yaw*U);
    return ans;
}
#include "segment.h"
#include "main.h"


using namespace std;

Segment::Segment(float x, float y,int type,float zoom) {
    this->position = glm::vec3(x, y, 0);
    float r =0.04*zoom;
    this->radius = r;
    this->type = type;
    const double PI = 3.141592;
    GLfloat vertex_buffer_data_g[] = {
        -3*r,0.25*r,0.0f, // triangle 1 : begin
        3*r,0.25*r, 0.0f,
        -3*r, -0.25*r, 0.0f, // triangle 1 : end
        -3*r, -0.25*r,0.0f, // triangle 2 : begin
        3*r,-0.25*r,0.0f,
        3*r, 0.25*r,0.0f, // triangle 2 : end
    };
    GLfloat vertex_buffer_data_a[] = {
        -3*r,0.25*r+7*r,0.0f, // triangle 1 : begin
        3*r,0.25*r+7*r, 0.0f,
        -3*r, -0.25*r+7*r, 0.0f, // triangle 1 : end
        -3*r, -0.25*r+7*r,0.0f, // triangle 2 : begin
        3*r,-0.25*r+7*r,0.0f,
        3*r, 0.25*r+7*r,0.0f, // triangle 2 : end
    };
    GLfloat vertex_buffer_data_d[] = {
        -3*r,0.25*r-7*r,0.0f, // triangle 1 : begin
        3*r,0.25*r-7*r, 0.0f,
        -3*r, -0.25*r-7*r, 0.0f, // triangle 1 : end
        -3*r, -0.25*r-7*r,0.0f, // triangle 2 : begin
        3*r,-0.25*r-7*r,0.0f,
        3*r, 0.25*r-7*r,0.0f, // triangle 2 : end
    };
    GLfloat vertex_buffer_data_b[] = {
        3*r,6.5*r,0.0f, // triangle 1 : begin
        3*r,0.5*r, 0.0f,
        3.5*r, 6.5*r, 0.0f, // triangle 1 : end
        3.5*r, 0.5*r,0.0f, // triangle 2 : begin
        3*r,0.5*r,0.0f,
        3.5*r, 6.5*r,0.0f, // triangle 2 : end
    };
    GLfloat vertex_buffer_data_f[] = {
        3*r-6.5*r,6.5*r,0.0f, // triangle 1 : begin
        3*r-6.5*r,0.5*r, 0.0f,
        3.5*r-6.5*r, 6.5*r, 0.0f, // triangle 1 : end
        3.5*r-6.5*r, 0.5*r,0.0f, // triangle 2 : begin
        3*r-6.5*r,0.5*r,0.0f,
        3.5*r-6.5*r, 6.5*r,0.0f, // triangle 2 : end
    };
    GLfloat vertex_buffer_data_e[] = {
        3*r-6.5*r,6.5*r-7*r,0.0f, // triangle 1 : begin
        3*r-6.5*r,0.5*r-7*r, 0.0f,
        3.5*r-6.5*r, 6.5*r-7*r, 0.0f, // triangle 1 : end
        3.5*r-6.5*r, 0.5*r-7*r,0.0f, // triangle 2 : begin
        3*r-6.5*r,0.5*r-7*r,0.0f,
        3.5*r-6.5*r, 6.5*r-7*r,0.0f, // triangle 2 : end
    };
    GLfloat vertex_buffer_data_c[] = {
        3*r,6.5*r-7*r,0.0f, // triangle 1 : begin
        3*r,0.5*r-7*r, 0.0f,
        3.5*r, 6.5*r-7*r, 0.0f, // triangle 1 : end
        3.5*r, 0.5*r-7*r,0.0f, // triangle 2 : begin
        3*r,0.5*r-7*r,0.0f,
        3.5*r, 6.5*r-7*r,0.0f, // triangle 2 : end
    };
    GLfloat vertex_buffer_data_clear[] = {
        3.5*r,7.25*r,0.0f, // triangle 1 : begin
        -3.5*r,7.25*r, 0.0f,
        -3.5*r, -7.25*r, 0.0f, // triangle 1 : end
        3.5*r, 7.25*r,0.0f, // triangle 2 : begin
        3.5*r,-7.25*r,0.0f,
        -3.5*r, -7.25*r,0.0f, // triangle 2 : end
    };
    // vector<color_t> COLOR_type;
    // COLOR_type[0] = COLOR_MALACHITE;
    // COLOR_type[1] = COLOR_LASER_YELLOW;
    // COLOR_type[2] = COLOR_FIRE;
    color_t color_type[] = {COLOR_GREEN,COLOR_BLACK,COLOR_RUBY};
    this->object_g = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_g, color_type[type], GL_FILL);
    this->object_a = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_a, color_type[type], GL_FILL);
    this->object_d = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_d, color_type[type], GL_FILL);
    this->object_b = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_b, color_type[type], GL_FILL);
    this->object_f = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_f, color_type[type], GL_FILL);
    this->object_e = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_e, color_type[type], GL_FILL);
    this->object_c = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_c, color_type[type], GL_FILL);
    this->object_clear = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_clear, COLOR_BLACK, GL_FILL);
}

void Segment::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    //rotate          = rotate * glm::translate(glm::vec3(0, 5.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //draw3DObject(this->object_g);
    draw3DObject(this->object_a);
    draw3DObject(this->object_d);
    draw3DObject(this->object_b);
    draw3DObject(this->object_f);
    draw3DObject(this->object_e);
    draw3DObject(this->object_c);   
}
void Segment::draw_0(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    //rotate          = rotate * glm::translate(glm::vec3(0, 5.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //draw3DObject(this->object_clear);
    //draw3DObject(this->object_g);
    draw3DObject(this->object_a);
    draw3DObject(this->object_d);
    draw3DObject(this->object_b);
    draw3DObject(this->object_f);
    draw3DObject(this->object_e);
    draw3DObject(this->object_c);
       
}
void Segment::draw_1(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    //rotate          = rotate * glm::translate(glm::vec3(0, 5.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //draw3DObject(this->object_clear);  
    //draw3DObject(this->object_g);
    //draw3DObject(this->object_a);
    //draw3DObject(this->object_d);
    draw3DObject(this->object_b);
    //draw3DObject(this->object_f);
    //draw3DObject(this->object_e);
    draw3DObject(this->object_c); 
    
}
void Segment::draw_2(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    //rotate          = rotate * glm::translate(glm::vec3(0, 5.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //draw3DObject(this->object_clear); 
    draw3DObject(this->object_g);
    draw3DObject(this->object_a);
    draw3DObject(this->object_d);
    draw3DObject(this->object_b);
    //draw3DObject(this->object_f);
    draw3DObject(this->object_e);
    
    
}
void Segment::draw_3(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    //rotate          = rotate * glm::translate(glm::vec3(0, 5.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //draw3DObject(this->object_clear); 
    draw3DObject(this->object_g);
    draw3DObject(this->object_a);
    draw3DObject(this->object_d);
    draw3DObject(this->object_b);
    //draw3DObject(this->object_f);
    //draw3DObject(this->object_e);
    draw3DObject(this->object_c);     
}
void Segment::draw_4(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    //rotate          = rotate * glm::translate(glm::vec3(0, 5.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //draw3DObject(this->object_clear); 
    draw3DObject(this->object_g);
    //draw3DObject(this->object_a);
    //draw3DObject(this->object_d);
    draw3DObject(this->object_b);
    draw3DObject(this->object_f);
    //draw3DObject(this->object_e);
    draw3DObject(this->object_c);     
}
void Segment::draw_5(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    //rotate          = rotate * glm::translate(glm::vec3(0, 5.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //draw3DObject(this->object_clear); 
    draw3DObject(this->object_g);
    draw3DObject(this->object_a);
    draw3DObject(this->object_d);
    //draw3DObject(this->object_b);
    draw3DObject(this->object_f);
    //draw3DObject(this->object_e);
    draw3DObject(this->object_c);  
}
void Segment::draw_6(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    //rotate          = rotate * glm::translate(glm::vec3(0, 5.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //draw3DObject(this->object_clear); 
    draw3DObject(this->object_g);
    draw3DObject(this->object_a);
    draw3DObject(this->object_d);
    //draw3DObject(this->object_b);
    draw3DObject(this->object_f);
    draw3DObject(this->object_e);
    draw3DObject(this->object_c);  
}
void Segment::draw_7(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    //rotate          = rotate * glm::translate(glm::vec3(0, 5.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //draw3DObject(this->object_clear); 
    //draw3DObject(this->object_g);
    draw3DObject(this->object_a);
    //draw3DObject(this->object_d);
    draw3DObject(this->object_b);
    //draw3DObject(this->object_f);
    //draw3DObject(this->object_e);
    draw3DObject(this->object_c);  
}
void Segment::draw_8(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    //rotate          = rotate * glm::translate(glm::vec3(0, 5.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //draw3DObject(this->object_clear); 
    draw3DObject(this->object_g);
    draw3DObject(this->object_a);
    draw3DObject(this->object_d);
    draw3DObject(this->object_b);
    draw3DObject(this->object_f);
    draw3DObject(this->object_e);
    draw3DObject(this->object_c);  
}
void Segment::draw_9(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    //rotate          = rotate * glm::translate(glm::vec3(0, 5.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //draw3DObject(this->object_clear); 
    draw3DObject(this->object_g);
    draw3DObject(this->object_a);
    draw3DObject(this->object_d);
    draw3DObject(this->object_b);
    draw3DObject(this->object_f);
    //draw3DObject(this->object_e);
    draw3DObject(this->object_c);  
}
// float Segment::ret_x(){
//     return this->position.x;
// }
// float Segment::ret_y(){
//     return this->position.y;
// }

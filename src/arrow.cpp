#include "arrow.h"
#include "main.h"

Arrow::Arrow(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    double r=1;
    this->position = glm::vec3(x, y, z);
    //this->platform_y = platform_y+0.45*r;
    //this->ceiling_y = ceiling_y-0.45*this->radius;
    //this->rotation = 0;
    const double PI = 3.141592;
    
	int n = 50;
    int i;
    //black Rings on top
    //R= R/2;
    //inner rings
    GLfloat vertex_buffer_data[] = {
        -r,0.0f,r, // triangle 1 : begin
        r,0.0f,r, 
         -r,0.0f, -r, // triangle 1 : end
        -r,0.0f, -r, // triangle 2 : begin
        r,0.0f,-r,
        r,0.0f, r // triangle 2 : end
    };
    GLfloat inner_vertex_buffer_data[] = {
        0.0f,-r,r, // triangle 1 : begin
        0.0f,r,r, 
        0.0f, -r, -r, // triangle 1 : end
        0.0f,-r, -r, // triangle 2 : begin
        0.0f,r,-r,
        0.0f,r, r // triangle 2 : end
    };
    float height,width,depth;
    height=width=depth=1;
    height = 3;
    GLfloat vertex_buffer_data_1[] = {
        -width/2.0f ,-height/2.0f ,-depth/2.0f, // triangle 1 : begin
        -width/2.0f ,-height/2.0f , depth/2.0f,
        -width/2.0f , height/2.0f , depth/2.0f, // triangle 1 : end

        width/2.0f , height/2.0f ,-depth/2.0f, // triangle 2 : begin
        -width/2.0f ,-height/2.0f ,-depth/2.0f,
        -width/2.0f , height/2.0f ,-depth/2.0f, // triangle 2 : end

        width/2.0f ,-height/2.0f , depth/2.0f,
        -width/2.0f ,-height/2.0f ,-depth/2.0f,
        width/2.0f ,-height/2.0f ,-depth/2.0f,

        width/2.0f , height/2.0f ,-depth/2.0f,
        width/2.0f ,-height/2.0f ,-depth/2.0f,
        -width/2.0f ,-height/2.0f ,-depth/2.0f,

        -width/2.0f ,-height/2.0f ,-depth/2.0f,
        -width/2.0f , height/2.0f , depth/2.0f,
        -width/2.0f , height/2.0f ,-depth/2.0f,

        width/2.0f ,-height/2.0f , depth/2.0f,
        -width/2.0f ,-height/2.0f , depth/2.0f,
        -width/2.0f ,-height/2.0f ,-depth/2.0f,

        -width/2.0f , height/2.0f , depth/2.0f,
        -width/2.0f ,-height/2.0f , depth/2.0f,
        width/2.0f ,-height/2.0f , depth/2.0f,

        width/2.0f , height/2.0f , depth/2.0f,
        width/2.0f ,-height/2.0f ,-depth/2.0f,
        width/2.0f , height/2.0f ,-depth/2.0f,

        width/2.0f ,-height/2.0f ,-depth/2.0f,
        width/2.0f , height/2.0f , depth/2.0f,
        width/2.0f ,-height/2.0f , depth/2.0f,

        width/2.0f , height/2.0f , depth/2.0f,
        width/2.0f , height/2.0f ,-depth/2.0f,
        -width/2.0f , height/2.0f ,-depth/2.0f,

        width/2.0f , height/2.0f , depth/2.0f,
        -width/2.0f , height/2.0f ,-depth/2.0f,
        -width/2.0f , height/2.0f , depth/2.0f,

        width/2.0f , height/2.0f , depth/2.0f,
        -width/2.0f , height/2.0f , depth/2.0f,
        width/2.0f ,-height/2.0f , depth/2.0f
    };
    GLfloat vertex_buffer_data_2[] = {
        -width/2.0f ,-height/2.0f ,-depth/2.0f, // triangle 1 : begin
        -width/2.0f ,-height/2.0f , depth/2.0f,
        0.0f-2, height/2.0f -2, 0.0f-2,    
    };
    //depth = 6;
      GLfloat vertex_buffer_data_3[] = {
       0.0f, -2.0f-height/2.0f,0.0f,
       -0.75f,0.0f-height/2.0f,0.75f,
       -0.75f,0.0f-height/2.0f,-0.75f,

       0.0f, -2.0f-height/2.0f,0.0f,
       -0.75f,0.0f-height/2.0f,0.75f,
        0.75f,0.0f-height/2.0f,0.75f,

        0.0f, -2.0f-height/2.0f,0.0f,
        0.75f,0.0f-height/2.0f,-0.75f,
       -0.75f,0.0f-height/2.0f,-0.75f,

       0.0f, -2.0f-height/2.0f,0.0f,
       0.75f,0.0f-height/2.0f,-0.75f,
       0.75f,0.0f-height/2.0f,0.75f,
    };

    this->object_top = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data_3, COLOR_NEON, GL_FILL);
    this->object_base = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data_1, COLOR_NEON_YELLOW, GL_FILL);
    //this->object_top = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data_2, COLOR_NEON, GL_FILL);
    
    GLfloat inner_base_vertex_buffer_data[30*n];
    // GLfloat inner_tr2_vertex_buffer_data[30*n];
    //this->object_base = create3DObject(GL_TRIANGLES, 6, inner_vertex_buffer_data, COLOR_HOT_RED, GL_FILL);
    //this->object_top = create3DObject(GL_TRIANGLES, 3*n, circle_vertex_buffer_data, COLOR_FOREST, GL_FILL);
    
}

void Arrow::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (-this->rotation ), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    draw3DObject(this->object_base);
    draw3DObject(this->object_top);
    
}

void Arrow::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Arrow::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
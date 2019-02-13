#include "main.h"
#include "timer.h"
#include "ball.h"
#include "cone.h"
#include "cylinder.h"
#include "screen.h"
#include "airplane.h"
#include "mountain.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
glm::vec3 initEye;
Ball ball1;
Cone cone;
Cylinder cyl;
Screen forest;
Airplane airforce;
Mountain mt;
vector<Mountain> mount;
// follow camera = 1, top view =2, tower view = 3
int camera_flag = 1;
float e1,e2,e3;
float tx,ty,tz;
float u1,u2,u3;
float temp_tx,temp_ty,temp_tz;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
glm::vec4 eye_mov;
glm::vec4 tar_mov;
glm::vec4 speed;
glm::vec3 dummy(0,0,0);
Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);
    eye_mov = glm::vec4(e1,e2,e3,1);
    tar_mov = glm::vec4(tx,ty,tz,1);
    glm::vec4 up_mov = glm::vec4(u1,u2,u3,1);
    // Eye - Location of camera. Don't change unless you are sure!!
    //glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    //glm::vec3 eye(0,-2.5,2);
    glm::vec3 eye(e1,e2,e3);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (tx, ty, tz);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (u1, u2, u3);
    target = airforce.position;
    // Compute Camera matrix (view)
    glm::vec4 temp_eye = airforce.set_eye(eye_mov);
    glm::vec4 temp_tar = airforce.set_eye(tar_mov);
    glm::vec4 temp_up = airforce.set_eye(up_mov);
    glm::vec3 E1 = glm::vec3(temp_eye.x,temp_eye.y,temp_eye.z);
    glm::vec3 T1 = glm::vec3(temp_tar.x,temp_tar.y,temp_tar.z);
    glm::vec3 U1 = glm::vec3(temp_up.x,temp_up.y,temp_up.z);
    Matrices.view = glm::lookAt( E1, T1, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model
    forest.draw(VP);
    mt.draw(VP);
    //cone.draw(VP);
    //cyl.draw(VP);
    // for(int i=0;i<mount.size();i++)
    // {
    //     mount[i].draw(VP);
    // }
    
    airforce.draw(VP);
    
    airforce.reset_rotation();
    eye_mov = glm::vec4(initEye,1);
    //cout<<"e1 "<<e1<<" e2 "<<e2<<" e3 "<<e3<<endl;
    // Scene render
    //ball1.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    //raise
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    //tilt
    int l = glfwGetKey(window, GLFW_KEY_L);
    int k = glfwGetKey(window, GLFW_KEY_K);
    
    int w = glfwGetKey(window, GLFW_KEY_W);
    int a = glfwGetKey(window, GLFW_KEY_A);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int z = glfwGetKey(window, GLFW_KEY_Z);
    int e = glfwGetKey(window, GLFW_KEY_E);
    int c = glfwGetKey(window, GLFW_KEY_C);
    int r = glfwGetKey(window, GLFW_KEY_R);
    int y = glfwGetKey(window, GLFW_KEY_Y);
    int t = glfwGetKey(window, GLFW_KEY_T);
    if (left) {
       airforce.move_left();
        glm::vec4 temp_speed = airforce.set_speed(speed);
        speed.x = temp_speed.x;
        speed.y = temp_speed.y;
        speed.z = temp_speed.z;
        
    }
    if (right) {
      airforce.move_right();
        glm::vec4 temp_speed = airforce.set_speed(speed);
        speed.x = temp_speed.x;
        speed.y = temp_speed.y;
        speed.z = temp_speed.z;
    }
    if (up) {
       airforce.position.x += speed.x;
       airforce.position.y += speed.y;
       airforce.position.z += speed.z;
       cout<<airforce.position.x<<" "<<airforce.position.y<<" "<<airforce.position.z<<endl;
       
    }
    if (down) {
       airforce.fall();
       //if(airforce)
       airforce.dive_down();
       glm::vec4 temp_speed = airforce.set_speed(speed);
        speed.x = temp_speed.x;
        speed.y = temp_speed.y;
        speed.z = temp_speed.z;
    }
    if(space){
        airforce.lift();
        airforce.dive_up();
        glm::vec4 temp_speed = airforce.set_speed(speed);
        speed.x = temp_speed.x;
        speed.y = temp_speed.y;
        speed.z = temp_speed.z;
    }
    if(l){
        airforce.tilt_left();
        glm::vec4 temp_speed = airforce.set_speed(speed);
        speed.x = temp_speed.x;
        speed.y = temp_speed.y;
        speed.z = temp_speed.z;
        
    }
    if(k){
        airforce.tilt_right();
        glm::vec4 temp_speed = airforce.set_speed(speed);
        speed.x = temp_speed.x;
        speed.y = temp_speed.y;
        speed.z = temp_speed.z;

    }
    // along x axis
    if(z){
        e1 += 0.01;
    }
    if(c){
        e1 -= 0.01;
    }
    //along y axis
    if(a){
        e2 += 0.01;
        cout<<e2<<endl;
    }
    if(d){
        e2 -= 0.01;
        cout<<e2<<endl;
    }
    //along z axis
    if(w){
        e3 += 0.01;
    }   
    if(e){
        e3 -= 0.01;
    }
    //follow the camera view from far
    if (r) {
       e1 =0.0;
       e2=0.04;
       e3 = -1.49;
    }
    //follow the camera view
    if(y){
        e1=0.04;
    e2=1.47;
    e3=-1.49;
    initEye = glm::vec3(e1, e2, e3);
    }
    //top view
    if(t){
        e1=0.0001;
        e2 = 10;
        e3=0;
    }

}

void tick_elements() {
    //ball1.tick();
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    e1=e2=e3=tx=ty=tz=u1=u3=0;
    u2=1;
    speed = glm::vec4(0,0,0.05,1);
    //ball1       = Ball(0, 0, COLOR_RED);
    cone = Cone(0,-1.5,1.6);
    cyl = Cylinder(0,-1.5,0);
    airforce = Airplane(0,0,-2);
    forest = Screen(0,-5,0);
    mt = Mountain(0,-5,7);
    for(int i=0;i<5;i++){
        mount.push_back(Mountain(2*i,0,4));
    }
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    float angle = M_PI/2;
    // angle is field of view, aspect ratio, near and far
    Matrices.projection = glm::perspective(angle, 1.0f, 1.0f, 500.0f);
}

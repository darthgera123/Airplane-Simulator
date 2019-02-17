#include "main.h"
#include "timer.h"
#include "ball.h"
#include "cone.h"
#include "cylinder.h"
#include "screen.h"
#include "airplane.h"
#include "mountain.h"
#include "shooter.h"
#include "rings.h"
#include "dashboard.h"
#include "dash_stick.h"
#include "missile.h"
#include "bomb.h"
#include "fuel.h"
#include "parachute.h"

using namespace std;

GLMatrices Matrices,MatricesDashboard;
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
Shooter shoot;

vector<Rings>smoke;
Dashboard dash_fuel,dash_altitude;
Dashsticks dash_stick_fuel,dash_stick_altitude;
vector<Mountain> mount;
vector<Missile> missile;
vector<Bomb> bomb;
vector<Fuel> fuel;
vector<Parachute> para;
bounding_box_t airplane_box;
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
Timer t60(1.0 / 60);
double GenerateRandom(double min, double max)
{
    static bool first = true;
    if (first)
    {
        srand(time(NULL));
        first = false;
    }
    if (min > max)
    {
        std::swap(min, max);
    }
    return min + (double)rand() * (max - min) / (double)RAND_MAX;
}
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void collision_ring(){
    vector<Rings>::iterator vit;
    glm::vec3 tail = airforce.position;
    tail.z = tail.z + airforce.radius*4;
    //cout<<tail.z<<" "<<smoke[0].position.z<<endl;
    for(vit = smoke.begin();vit!=smoke.end();vit++)
    {
        float radius = vit->radius;
        //cout<<tail.z<<" "<<vit->position.z<<endl;
        if(abs(tail.z-vit->position.z) <= 0.1)
        {
            float in = sqrt(pow((vit->position.x-tail.x),2)+pow((vit->position.y-tail.y),2));
            //cout<<"Dist "<<in<<" "<<radius<<endl;
            if(in <=radius)
            {
                cout<<"Collide"<<endl;
                airforce.score += 10;
                smoke.erase(vit);
                vit--;
            }
        }
    }  
    
}
void generate_ring(){
    
        float x = GenerateRandom(-30,30);
        float y = GenerateRandom(3,14);
        float z = GenerateRandom(3,100);
        smoke.push_back(Rings(x,y,z,10,0.05));
    
}
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
    glm::vec3 eyeScore(0,0,1);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (tx, ty, tz);
    glm::vec3 targetScore(0,0,0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (u1, u2, u3);
    glm::vec3 upScore(0,1,0);
    target = airforce.position;
    // Compute Camera matrix (view)
    if(camera_flag==1){
        glm::vec4 temp_eye = airforce.set_eye(eye_mov);
        glm::vec4 temp_tar = airforce.set_eye(tar_mov);
        glm::vec4 temp_up = airforce.set_up(up_mov);
        glm::vec3 E1 = glm::vec3(temp_eye.x,temp_eye.y,temp_eye.z);
        glm::vec3 T1 = glm::vec3(temp_tar.x,temp_tar.y,temp_tar.z);
        glm::vec3 U1 = glm::vec3(temp_up.x,temp_up.y,temp_up.z);
        Matrices.view = glm::lookAt( E1, T1, up );
    }
    else if(camera_flag==2){
        glm::vec4 temp_eye = airforce.set_top(eye_mov);
        glm::vec4 temp_tar = airforce.set_top(tar_mov);
        glm::vec3 E1 = glm::vec3(temp_eye.x,temp_eye.y,temp_eye.z);
        glm::vec3 T1 = glm::vec3(temp_tar.x,temp_tar.y,temp_tar.z);
        Matrices.view = glm::lookAt( E1, T1, up );
    } 
    else if(camera_flag==3){
        Matrices.view = glm::lookAt( eye, glm::vec3(0,0,0), up );
    }
    else if(camera_flag==4){
        glm::vec4 temp_eye = airforce.set_eye(eye_mov);
        glm::vec4 temp_tar = airforce.set_eye(tar_mov);
        glm::vec4 temp_up = airforce.set_up(up_mov);
        glm::vec3 E1 = glm::vec3(temp_eye.x,temp_eye.y,temp_eye.z);
        glm::vec3 T1 = glm::vec3(temp_tar.x,temp_tar.y,temp_tar.z);
        glm::vec3 U1 = glm::vec3(temp_up.x,temp_up.y,temp_up.z);
        Matrices.view = glm::lookAt( E1, T1, U1 );
    }
    MatricesDashboard.view = glm::lookAt(eyeScore,targetScore,upScore);
    // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 VPScore = MatricesDashboard.projection * MatricesDashboard.view;
    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model
    glm::mat4 MVPScore;
    forest.draw(VP);
    mt.draw(VP);
    glm::vec3 shootpos = glm::vec3(airforce.position.x - shoot.position.x,airforce.position.y - shoot.position.y,airforce.position.z - shoot.position.z);
    shoot.draw(shootpos,VP);
    airplane_box.x = airforce.position.x;
    airplane_box.y = airforce.position.y;
    airplane_box.z = airforce.position.z;
    vector<Fuel>::iterator fit;
    for(fit=fuel.begin();fit!=fuel.end();fit++)
    {
        bounding_box_t temp;
        temp.height = fit->height;
        temp.width = fit->width;
        temp.depth = fit->depth;
        temp.x = fit->position.x;
        temp.y = fit->position.y;
        temp.z = fit->position.z;
        if(detect_collision(temp,airplane_box))
        {
            fuel.erase(fit);
            fit--;
            airforce.fuel += 5;
            continue;
        }
        fit->draw(VP);
    }
    
    //cone.draw(VP);
    //cyl.draw(VP);
    // for(int i=0;i<mount.size();i++)
    // {
    //     mount[i].draw(VP);
    // }
    collision_ring();
    for(int i=0;i<smoke.size();i++)
    {
        smoke[i].draw(VP);
    }
    glm::vec4 temp_speed = airforce.set_speed(speed);
    speed.x = temp_speed.x;
    speed.y = temp_speed.y;
    speed.z = temp_speed.z;
    float unit = sqrt(pow(speed.x,2) + pow(speed.y,2) + pow(speed.z,2));
    //divide by unit vector and multiply by 5
    speed.x = (speed.x/unit) ;
    speed.y = (speed.y/unit) ;
    speed.z = (speed.z/unit) ;
    
    airforce.draw(VP);
    vector<Parachute>::iterator pit;
    for(pit=para.begin();pit!=para.end();pit++)
    {
        bounding_box_t temp;
        temp.height = 2*pit->radius;
        temp.width = 2*pit->radius;
        temp.depth = 2*pit->radius;
        temp.x = pit->position.x;
        temp.y = pit->position.y;
        temp.z = pit->position.z;
        if(pit->position.y < -5)
        {
            para.erase(pit);
            pit--;
            continue;
        }
        if(detect_collision(temp,airplane_box)){
            airforce.health--;
            if(airforce.health==0){
                cout<<"Kill"<<endl;
                quit(window);
            }
            else{
                airforce.set_position(0,0.5594,0.2999);
            }
            
        }
        //pit->fall_down();
        pit->draw(VP);
    }
    vector<Missile>::iterator mit;
    for(mit=missile.begin();mit!=missile.end();mit++){
            mit->move_forward();
            
            bounding_box_t temp;
            temp.height = 2*mit->radius;
            temp.width = 2*mit->radius;
            temp.depth = 6*mit->radius;
            temp.x = mit->position.x;
            temp.y = mit->position.y;
            temp.z = mit->position.z;
            int flag=1;
            ///cout<<temp.x<<" "<<temp.y<<" "<<temp.z<<endl;
            for(pit = para.begin();pit!=para.end();pit++)
            {
                bounding_box_t tempy;
                tempy.height = 2*pit->radius;
                tempy.width = 2*pit->radius;
                tempy.depth = 2*pit->radius;
                tempy.x = pit->position.x;
                tempy.y = pit->position.y;
                tempy.z = pit->position.z;
                //cout<<tempy.x<<" "<<tempy.y<<" "<<tempy.z<<endl;
                if(detect_collision(temp,tempy)){
                    para.erase(pit);
                    pit--;
                    flag=0;
                    break;
                }
            }
                if(!flag){
                    missile.erase(mit);
                    mit--;
                    continue;
                }
                float dis_x = airplane_box.x-temp.x;
                float dis_y = airplane_box.y-temp.y;
                float dis_z = airplane_box.z-temp.z;
                float distance = sqrt(dis_x*dis_x+dis_y*dis_y+dis_z*dis_z);
                if(distance >= 20)
                {
                    missile.erase(mit);
                    mit--;
                    continue;   
                }
                mit->draw(VP);
            }
            cout<<missile.size()<<endl;
    

   vector<Bomb>::iterator bit;
   for(bit=bomb.begin();bit!=bomb.end();bit++){
       bit->fall_down();
       bit->draw(VP);
   }

    dash_fuel.draw(VPScore);
    dash_stick_fuel.draw(VPScore);
    dash_altitude.draw(VPScore);
    dash_stick_altitude.curr_value = airforce.position.y+4;
    //cout<<dash_stick_altitude.curr_value<<endl;
    dash_stick_altitude.draw(VPScore);
    
    
    airforce.reset_rotation();
    //dash.set_position(e1,e2,e3);
    //eye_mov = glm::vec4(initEye,1);
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
    int u = glfwGetKey(window, GLFW_KEY_U);
    int f = glfwGetKey(window, GLFW_KEY_F);
    int h = glfwGetKey(window, GLFW_KEY_H);
    int m = glfwGetKey(window, GLFW_KEY_M);
    if (left) {
       airforce.move_left();
    }
    if (right) {
      airforce.move_right();
    }
    if (up) {
       airforce.position.x += speed.x*airforce.speed;
       airforce.position.y += speed.y*airforce.speed;
       airforce.position.z += speed.z*airforce.speed;
    }
    if (down) {
       airforce.fall();
       //if(airforce)
       airforce.dive_down();
       
    }
    if(space){
        if(airforce.position.y < 16){
            airforce.lift();
            airforce.dive_up();
        }
    }
    if(m){
        
        glm::vec3 missile_pos = glm::vec3(airforce.position.x,airforce.position.y - 1.2*airforce.radius,airforce.position.z);
        missile.push_back(Missile(missile_pos.x,missile_pos.y,missile_pos.z,airforce.totalRot,glm::vec3(speed.x,speed.y,speed.z)));
    }
    if(l){
        airforce.tilt_left();
        
    }
    if(k){
        airforce.tilt_right();

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
    //follow the camera view from ass
    if (r) {
       e1 =0.0;
       e2=0.04;
       e3 = -1.49;
       camera_flag=1;
    }
    //follow the camera view from a little height
    if(y){
        e1=0.04;
        e2=1.47;
        e3=-1.49;
        camera_flag=1;
    }
    //top view
    if(t){
        e1=0.0001;
        e2 = 10;
        e3=0;
        camera_flag = 2;
    }
    //tower view
    if(u){
         e1=3.32;
        e2=-1.47;
        e3=4.777;
        camera_flag = 3;
    }
    //first person view
    if(f){
        e1=0;
        e2=0;
        e3=4*airforce.radius;
        tz = e3 + 0.01;
        camera_flag = 4;
    }
    if(h){
        bomb.push_back(Bomb(airforce.position.x,airforce.position.y-1.2*airforce.radius,airforce.position.z));
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
    e1 =0.0;
       e2=0.04;
       e3 = -1.49;
       tx=ty=tz=0;
       u1=u3=0;
    u2=1;
    speed = glm::vec4(0,0,0.05,1);

    airforce = Airplane(0,0.5594,0.2999);
    airplane_box.depth = airforce.radius*6;
    airplane_box.height = 2*airforce.radius;
    airplane_box.width = 2*airforce.radius;
    forest = Screen(0,-5,0);
    mt = Mountain(0,-5,7,2,0.5);

    smoke.push_back(Rings(0,5,3,10,0.05));
    
    dash_fuel = Dashboard(-3,-3,1,2);
    dash_stick_fuel = Dashsticks(-3,-3,dash_fuel.radius_rx,100,2);
    dash_altitude =  Dashboard(3,-3,1,1);
    dash_stick_altitude = Dashsticks(3,-3,dash_altitude.radius_rx,20,1);
    
    //fuel.push_back(Fuel(3,3,3));
    para.push_back(Parachute(3,3,3));
    shoot = Shooter(mt.position.x,mt.position.y+2*mt.height,mt.position.z,mt.radius,mt.height);
    // for(int i=0;i<5;i++){
    //     mount.push_back(Mountain(2*i,0,4));
    // }
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
           (abs(a.y - b.y) * 2 < (a.height + b.height)&& 
           abs(a.z - b.z)*2 < (a.depth+b.depth));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    float angle = M_PI/2;
    // angle is field of view, aspect ratio, near and far
    Matrices.projection = glm::perspective(angle, 1.0f, 1.0f, 500.0f);
    MatricesDashboard.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

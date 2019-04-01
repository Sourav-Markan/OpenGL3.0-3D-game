#include "main.h"
#include "timer.h"
#include "ball.h"
#include "sea.h"
#include "block.h"
#include "goli.h"
#include "enemy.h"
#include "life.h"
#include "boss.h"
#include "coins.h"
#include "man.h"
#include "flag.h"
#include "island.h"
#include <string.h>

#define no 100
#define nc 15
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
double x;
double y;
char str[400];
int level=1,k,dir;
int lives=3;
int wind=0,up;
int health=100,lif=0;
int score=0,kill=0,emerge=0;


/**************************
* Customizable functions *
**************************/
int view =0,jump=0;
int zoom=10,mm=0;
int goli_i=-1;
float helx,hely,helz;
float hx,hy,hz;
Man man;
Boss boss;
Ball ball1;
Sea  sea1;
Block blo;
Flag fla; 
Island isl;
Enemy enemy[30];
Life life[30];
Life L,L2;
Coin coins[nc];
Coin coins1[nc];
Coin coins2[nc];
Block  blocks[no];
Goli goli[1000];;
float eye_x;
float eye_y;
float eye_z;
float tar_x;
float tar_y;
float tar_z;

float RandomFloat(float min, float max)
{
    float r = (float)rand() / (float)RAND_MAX;
    return min + r * (max - min);
}

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float store_camera_angle;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);
    ///   VIEWS   ///
    /*
    1ST View is Follow Cam view.
    2ND View is Boat View.
    3RD View is Top View.
    4TH View is Tower View.
    5TH View is Helicopter view.
    */
    // Eye - Location of camera. Don't change unless you are sure!!
    

    if(view%5==0)
    {
        if(!(man.position.z<100 || man.position.x>100 || man.position.x<-100 || man.position.z>200))
        {
            eye_x=man.position.x+5*cos(camera_rotation_angle*M_PI/180.0f);
            eye_y=3;
            eye_z=man.position.z+5*sin(camera_rotation_angle*M_PI/180.0f);
            tar_x=man.position.x;
            tar_y=man.position.y;
            tar_z=man.position.z;
        }
        else
        {
            eye_x=ball1.position.x+5*cos(camera_rotation_angle*M_PI/180.0f);
            eye_y=3;
            eye_z=ball1.position.z+5*sin(camera_rotation_angle*M_PI/180.0f);
            tar_x=ball1.position.x;
            tar_y=ball1.position.y;
            tar_z=ball1.position.z;
        }
    }
    if(view%5==1)
    {
        eye_x=ball1.position.x;
        eye_y=ball1.position.y+2.1;
        eye_z=ball1.position.z;
        tar_x=ball1.position.x-5*cos(camera_rotation_angle*M_PI/180.0f);
        tar_y=1;
        tar_z=ball1.position.z-5*sin(camera_rotation_angle*M_PI/180.0f);
    }
    if(view%5==2)
    {
        tar_x=ball1.position.x;
        tar_y=ball1.position.y;
        tar_z=ball1.position.z;
        eye_x=ball1.position.x+0.6*cos(camera_rotation_angle*M_PI/180.0f);
        eye_y=10;
        eye_z=ball1.position.z+0.6*sin(camera_rotation_angle*M_PI/180.0f);        
    }
    if(view%5==3)
    {
        tar_x=ball1.position.x;
        tar_y=ball1.position.y;
        tar_z=ball1.position.z;
        eye_x=1;
        eye_y=5;
        eye_z=1;
    }
    if(view%5==4)  //To be done Helicopter view.
    {
        tar_x=hx-x;
        tar_y=hy+2;
        tar_z=hz+y;
        printf("tar %f %f\n",tar_x,tar_z);
        eye_x=helx;
        eye_y=hely;
        eye_z=helz;
    }



    glm::vec3 eye (eye_x, eye_y, eye_z);
    glm::vec3 target (tar_x, tar_y, tar_z);
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model
    sea1.draw(VP);
    // Scene render
    ball1.draw(VP);
    isl.draw(VP);
    fla.draw(VP);
    man.draw(VP);
    // blo.draw(VP);
    for(int i=0;i<no;i++)
    {
        blocks[i].draw(VP);
    }
    L.draw(VP);
    L2.draw(VP);
    for(int i=0;i<30;i++)
        enemy[i].draw(VP);
    for(int i=0;i<30;i++)
        life[i].draw(VP);
    for(int i=0;i<nc;i++)
    {
        coins[i].draw(VP);
        coins1[i].draw(VP);
        coins2[i].draw(VP);
    }
    for (int i=0;i<1000;i++)
    {
        goli[i].draw(VP);
    }
    blo.draw(VP);
    boss.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int goli = glfwGetKey(window, GLFW_KEY_X);
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    up = glfwGetKey(window, GLFW_KEY_UP);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    // int view = glfwGetKey(window, GLFW_KEY_V);
    if (left) {
        camera_rotation_angle-=2;
        ball1.rotation+=2;
    }
    if (right) {
        camera_rotation_angle+=2;
        ball1.rotation-=2;
    }
    if (up) {
        if(ball1.position.x>=-100 && ball1.position.x<=100 && ball1.position.z>=100 && ball1.position.z<=200)
        {   
            if(!mm)
            {
                man.position.x=ball1.position.x+0.4*cos((M_PI/180)*camera_rotation_angle);
                man.position.z=ball1.position.z+0.4*sin((M_PI/180)*camera_rotation_angle);
            }
            mm=1;
            if(mm)
            {
                man.position.x-=0.25*cos((M_PI/180)*camera_rotation_angle);
                man.position.z-=0.25*sin((M_PI/180)*camera_rotation_angle);
            }
        }
        else if(man.position.z<=100 || man.position.x>=100 || man.position.x<=-100 || man.position.z>=200)
        {

            if(mm)
            {
                ball1.position.x=man.position.x-0.4*cos((M_PI/180)*camera_rotation_angle);
                ball1.position.z=man.position.z-0.4*sin((M_PI/180)*camera_rotation_angle);
            }
            mm=0;
            ball1.position.z-=0.25*sin((M_PI/180)*camera_rotation_angle);
            ball1.position.x-=0.25*cos((M_PI/180)*camera_rotation_angle);
            // man.position.x=ball1.position.x+0.4*cos((M_PI/180)*camera_rotation_angle);
            // man.position.z=ball1.position.z+0.4*sin((M_PI/180)*camera_rotation_angle);
        }
        else
        {
            mm=0;
            ball1.position.z-=0.25*sin((M_PI/180)*camera_rotation_angle);
            ball1.position.x-=0.25*cos((M_PI/180)*camera_rotation_angle);
            // man.position.x=ball1.position.x+0.4*cos((M_PI/180)*camera_rotation_angle);
            // man.position.z=ball1.position.z+0.4*sin((M_PI/180)*camera_rotation_angle);;;
        }
    }
    if(space)
    {
        jump=1;
        ball1.speed_y=0.4;
    }
}

void tick_elements() {
    // if(wind%300==0) {
    //     k=rand()%360;
    //     printf("k %d\n",k);
    // }
    // wind++;
    // if(wind%300 < 0)
    // {
    //     fla.rotation=k;
    //     printf("hi\n");
    //     if(up)
    //     {
    //         ball1.position.z-=0.25*sin((M_PI/180)*fla.rotation);
    //         ball1.position.x-=0.25*cos((M_PI/180)*fla.rotation);
    //     }
    // }
    // else
    //     fla.rotation=0;
    // if(abs(fla.rotation- ball1.rotation)>180)
    // {
    //     fla.position.x=1000;
    // }
    // else
    // {
    //     fla.position.x=ball1.position.x;
    //     fla.position.z=ball1.position.z;
    // }

    if(abs(fla.rotation- ball1.rotation)>180)
                {
                    fla.position.x=1000;
                }
                else
                {
                    fla.position.x=ball1.position.x;
                    fla.position.z=ball1.position.z;
                }
    // L.tick();
    if(health<=0)
    {
        lives--;
        health=100;
        if(lives==0)
        {
            quit(window);
        }
    }
    glfwGetCursorPos(window, &x, &y);
    // printf("kill /%d \n",kill);
    if(jump==0)
    {
        if(ball1.position.y >= 0.2)
        {
            ball1.speed_y = -ball1.speed_y;
        }
        if(ball1.position.y <= -0.2)
        {
            ball1.speed_y = -ball1.speed_y;
        }
    }
    if(jump==1)
    {
        if(ball1.position.y >= 4.8)
        {
            ball1.speed_y = -ball1.speed_y;
        }
        if(ball1.position.y <= 0.0)
        {
            ball1.speed_y=0.03;
            jump=0;
        }
    }
    if(kill %4 == 0 && kill!=0){
        emerge=1;
        boss.emerge_boss();

    }
    if(emerge)
    {
        boss.shots=level+2;
        boss.tick(ball1.position.x - boss.position.x,ball1.position.z - boss.position.z,ball1.rotation);
    }
        ball1.tick();
    goli[goli_i].tick();
    if(abs(ball1.position.x-L.position.x)<=0.1 && abs(ball1.position.z-L.position.z)<=0.1)
    {
        health+=40;
        L.position.x=1000;
    }
    if(abs(man.position.x-50)<=20 && abs(man.position.z-120)<=10)
    {
        score+=1000;
        quit(window);
    }
    if(abs(ball1.position.x-L2.position.x)<=0.1 && abs(ball1.position.z- L2.position.z)<=0.1)
    {
        lives+=1;
        L2.position.x=1000;
    }
    for(int i=0;i<30;i++)
    {
        if(detect_collision(ball1.bounding_box(),enemy[i].bounding_box()))
        {
            health-=25;
            score+=10;
            enemy[i].position.x = RandomFloat(-200,200);
            enemy[i].position.z = RandomFloat(-200,200);
        }
        if(detect_collision(goli[goli_i].bounding_box(),enemy[i].bounding_box()))
        {
            kill++;
            score+=15;
            // printf("enemy %f %f\n",enemy[i].position.x,enemy[i].position.z);
            // printf("Life %f %f\n",L.position.x,L.position.z);
            L.position.x=enemy[i].position.x;
            L.position.z=enemy[i].position.z;
            enemy[i].position.x = 1000;
            enemy[i].position.z = 1000;
        }
        if(detect_collision(goli[goli_i].bounding_box(),boss.bounding_box()))
        {
            boss.shots--;
            health-=50;
            score+=7;
            if(boss.shots==0)
            {
               L2.position.x=ball1.position.x-=10*cos((M_PI/180)*camera_rotation_angle);
            L2.position.z=ball1.position.z-=10*sin((M_PI/180)*camera_rotation_angle);
               emerge=0;
               boss.position.x=1000;
               health-=50;
               score+=30;
               level+=1;
            }
        }

        enemy[i].tick();
        if((abs(enemy[i].position.x > 100))|| abs(enemy[i].position.z > 100)){
        enemy[i].speed_x = -enemy[i].speed_x;
        enemy[i].speed_z = -enemy[i].speed_z;
        }
    }
    fla.position.x=ball1.position.x;
    fla.position.z=ball1.position.z;
    if(detect_collision(ball1.bounding_box(),boss.bounding_box()))
        {   
            boss.shots--;
            health-=50;
            score+=7;
            if(boss.shots==0)
            {
               emerge=0;
               boss.position.x=1000;
               health-=50;
               score+=30;
               level+=1;
            }
        };
    for(int i=0;i<nc;i++)
    {
        coins[i].tick();
        if(coins[i].position.y >= 2)
        {
            coins[i].speed_y = -coins[i].speed_y;
        }
        if(coins[i].position.y <= -0.3)
        {
            coins[i].speed_y = -coins[i].speed_y;
        }
        coins1[i].tick();
        if(coins1[i].position.y >= 2)
        {
            coins1[i].speed_y = -coins1[i].speed_y;
        }
        if(coins1[i].position.y <= -0.3)
        {
            coins1[i].speed_y = -coins1[i].speed_y;
        }
        coins2[i].tick();
        if(coins2[i].position.y >= 2)
        {
            coins2[i].speed_y = -coins2[i].speed_y;
        }
        if(coins2[i].position.y <= -0.3)
        {
            coins2[i].speed_y = -coins2[i].speed_y;
        }
        if(detect_collision(ball1.bounding_box(),coins[i].bounding_box()))
        {
            score+=10;
            coins[i].position.x=RandomFloat(-100,100);
            coins[i].position.z=RandomFloat(-100,100);
        }
        if(detect_collision(ball1.bounding_box(),coins1[i].bounding_box()))
        {
            score+=15;
            coins1[i].position.x=RandomFloat(-200,200);
            coins1[i].position.z=RandomFloat(-200,200);
        }
        if(detect_collision(ball1.bounding_box(),coins2[i].bounding_box()))
        {
            score+=20;
            coins2[i].position.x=RandomFloat(-300,300);
            coins2[i].position.z=RandomFloat(-300,300);
        }
    }
    for (int i=0;i<100;i++)
    {
        if(detect_collision(ball1.bounding_box(),blocks[i].bounding_box()))
        {
            //printf("YES ");
            ball1.position.z +=0.25*sin((M_PI/180)*camera_rotation_angle);
            ball1.position.x +=0.25*cos((M_PI/180)*camera_rotation_angle);
        }
        if(detect_collision(blocks[i].bounding_box(),goli[goli_i].bounding_box()))
        {
            score+=5;
            blocks[i].position.x = RandomFloat(-200,200);
            blocks[i].position.z = RandomFloat(-200,200);
        }
        if(detect_collision(blo.bounding_box(),goli[goli_i].bounding_box()))
        {
            score+=3;;
            blo.position.x = 1000;
            blo.position.z = 1000;
        }
    }

    // printf("cursor %f  %f\n",x,y);
    glfwGetCursorPos(window, &x, &y);
    // printf("cursor %f  %f\n",x,y);
            // previous_x_position = x;
//    if(goli[goli_i].position.y <= 0)
//    {
//        goli[goli_i].position.y=0;
//    }


    // printf("ball->%f %f %f\n",ball1.position.x,ball1.position.y,ball1.position.z);
    // printf("camera    ball   angles->%d %d \n",camera_rotation_angle,ball1.rotation);
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    man=Man(1000,0,COLOR_RED);
    ball1       = Ball(0, 0, COLOR_RED);
    sea1       = Sea(0, 0, COLOR_aqua);
    isl  = Island(0,0,COLOR_RED);
    // blo        = Block(-4,0,COLOR_BLACK);
    for (int i = 0; i < no; ++i)
    {
        blocks[i] = Block(RandomFloat(-200,200),RandomFloat(-200,200),COLOR_BLACK);
    }
    fla=Flag(0,0,COLOR_RED);
    blo=Block(-12,0,COLOR_BLACK);
    boss = Boss(0, -9, -20);
    L=Life(1000,1000,COLOR_RED);
    L2=Life(1000,1000,COLOR_purple);
    for(int i=0; i<1000;i++)
    {
        goli[i] =   Goli(1000,1000,COLOR_RED);
    }
    for(int i=0; i<30;i++)
    {
        life[i] =   Life(1000,1000,COLOR_BLACK);
    }
    for(int i=0;i<30;i++)
        enemy[i]=   Enemy(RandomFloat(-100,100),RandomFloat(-100,100),COLOR_RED);

    for(int i=0;i<nc;i++)
        coins[i]=   Coin(RandomFloat(-100,100),RandomFloat(-100,100),COLOR_RED);
    for(int i=0;i<nc;i++)
        coins1[i]=   Coin(RandomFloat(-100,100),RandomFloat(-100,100),COLOR_white);
    for(int i=0;i<nc;i++)
        coins2[i]=   Coin(RandomFloat(-100,100),RandomFloat(-100,100),COLOR_GREEN);

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
        
        char temp[20];
    sprintf(temp,"%d",score);
    char temp2[20];
    sprintf(temp2,"%d",lives);
    char temp3[20];
    sprintf(temp3,"%d",health);
    char temp4[20];
    sprintf(temp4,"%d",level);
    char str[200]="Score-> ";
    strcat(str,temp);
    strcat(str,"Lives ->");
    strcat(str,temp2);
    strcat(str,"Health-");
    strcat(str,temp3);
    strcat(str,"Level-");
    strcat(str,temp4);
    glfwSetWindowTitle(window,str);
        if (t60.processTick()) {
            // wind++;
            // int ch=0;
            // int sec=(wind/60)%10;
            // if(sec<2)
            // {
            //     if(ch==0)
            //     {
            //         fla.rotation=rand()%360;
            //         ch=1;
            //     }
            //     if(abs(fla.rotation- ball1.rotation)>180)
            //     {
            //         fla.position.x=1000;
            //     }
            //     else
            //     {
            //         fla.position.x=ball1.position.x;
            //         fla.position.z=ball1.position.z;
            //     }
            // }
            // else ch=0;
            // printf("%d\n",wind);
        
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
    return (abs(a.x - b.x) * 3 <= (-0.1+a.width + b.width)) &&
           (abs(a.y - b.y) * 3 <= (-0.1+a.height + b.height)) &&
           (abs(a.z - b.z) * 3 <= (-0.1+a.length + b.length));
}
void changeview(){
    if(view==3)
    {
        helx=ball1.position.x+zoom*cos(camera_rotation_angle*M_PI/180.0f);
        hely=4;
        helz=ball1.position.z+zoom*sin(camera_rotation_angle*M_PI/180.0f);
        hx=ball1.position.x;
        hy=ball1.position.y;
        hz=ball1.position.z;
    }
    view++;
    // printf("%d",view);
}
void attack(){
//    if(goli[goli_i].position.y==0)
//    {
        goli_i++;
        goli[goli_i].position.x = ball1.position.x-1.7*cos((M_PI/180)*camera_rotation_angle);;
        goli[goli_i].position.z = ball1.position.z-1.7*sin((M_PI/180)*camera_rotation_angle);;
        goli[goli_i].position.y = .01;
        store_camera_angle = camera_rotation_angle;
        // printf("%f ",store_camera_angle);
        goli[goli_i].speed_y=0.6;
        goli[goli_i].acc_y = -0.04;
        goli[goli_i].speed_z = 0.35*sin((M_PI/180)*store_camera_angle);
        goli[goli_i].speed_x = 0.35*cos((M_PI/180)*store_camera_angle);
        // printf("%d",goli_i);
//    }
}
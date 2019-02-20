#include "main.h"
#include "timer.h"
#include "wall.h"
#include "platform.h"
#include "player.h"
#include "dragon.h"
#include "coin.h"
#include "seg_a.h"
#include "fireline.h"
#include "firebeam.h"
#include "arrow.h"
#include "diamond.h"
#include "magnet.h"
#include "balloon.h"
#include "fox.h"
#include "math.h"
#include "ring.h"

using namespace std;
int boost_flag=0;
GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
int level=1;

/**************************
* Customizable functions *
**************************/
Wall wall[70];
A0 a0, b0, c0, e0, f0, g0, d0, 
a2, b2, c2, d2, e2, f2, g2,
a1, b1, c1, d1, e1, f1, g1;
// A0 score
Platform platform;
Player player;
Dragon dragon;
Coin coin1[70], coin2[70];
Arrow arrow[3], sword;
Diamond diamond[2];
Magnet magnet;
Fox fox[4];
Ring ring;
// Balloon iceball[45];
Fireline fireline[30];
Firebeam firebeam[30];

int magnet_flag=0;
int sword_flag=0;
int dia_flag =0;
double  boost=0.5;
// int ice_ball=0;


int sword_flag2=0;
// int balloon_counter=0;
// int balloon_flag=0;
// int balloon_number=0;
double g = -1;
double dt = 1.0 / 60;
double prev_speed = 0.0;
double prev_speed_fox = 0.0;
long long score = 10;
double t;
double firebeam_active[30];
double fireline_active[30];
double dragon_active =1;
int prev_ballon;
double fox_active[3];
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
//up motion detect
int up_flag = 0;

Timer t60(1.0 / 60);
// Timer times;

//to generate random numbers
float RandomNumber(float Min, float Max)
{
    return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
}

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
     // level system

    if(score<30) level=1;
    if(score>=30 && score<50) level=2;
    if(score>=50 && score<75) level=3;

    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    // ball1.draw(VP);
    for(int i=0; i<22; i++){
        wall[i].draw(VP); //draw 15 walls
    }

    for(int i=0; i<28; i++){
        // if(fireline_active[i]>0 || fireline_active[i]<-150 )
            fireline[i].draw(VP); //draw 13 firelines
    }

    for(int i=0; i<15; i++){
        // if(firebeam_active[i]>0 || firebeam_active[i]<-150)
            firebeam[i].draw(VP); //draw 8 walls
    }

    for(int i=0; i<30; i++){
        coin1[i].draw(VP); //draw 30 coins 
    }
    for(int i=0; i<30; i++){
        coin2[i].draw(VP); //draw 30 coins 
    }

    for(int i=0; i<2; i++){
        // if(fox_active[i]>0 || fox_active[i]<-120)
            fox[i].draw(VP); //drw 1 fox
    }

    for(int i=0; i<1; i++){
        diamond[i].draw(VP); //drw 1 diamond
    }

    for(int i=0; i<1; i++){
        arrow[i].draw(VP);
    }

    platform.draw(VP);
    ring.draw(VP);
    player.draw(VP);
     if (level >=3) {
        //  ice_ball+=100;
         dragon.draw(VP);
        //  cout<<ice_ball<<'\n';
    //     //condition
        /// for(int i=0;i<15;i++){
            //  if(ice_ball%1000000 == 0)
                //   iceball[(ice_ball/1000000)].draw(VP);
         
     }

    // if(balloon_flag == 1 && balloon_number<40){

    //     balloon[balloon_number].draw(VP);
    //     balloon_number++;
    //     balloon_flag=0;
    //     balloon_counter=0;
    // }

    if(sword_flag >= 1 && sword_flag < 450) sword_flag2 = 4;
    else if(sword_flag >= 6)sword_flag2 =-1;

    if(sword_flag2 > 0)sword.draw(VP);
    magnet_flag=0;
    
    //if(score>=65) level=4;
    if(level>=2) t+=0.01;
    if((t > 0.00 && t <= 5.00))
        magnet_flag=1;
    if(t > 15.0 && t < 20.0)
        magnet_flag=1;
    if(magnet_flag)
        magnet.draw(VP);

    //seven segment - score
    long long int tmp_score=score;
    int dig0=tmp_score%10;
    tmp_score/=10;
    int dig1=tmp_score%10;
    bool binary0[5];
    bool binary1[5];
    int bin0[5];
    int bin1[5];
    for(int i=0;i<=4;i++){
           binary0[i]=false;
           binary1[i]=false;
           bin0[i]=0;
           bin1[i]=0;
    }
    int idx0=0;
    while(dig0>0){
        bin0[idx0]=dig0%2;
        dig0/=2;
        idx0++;
    }
    int idx1=0;
    while(dig1>0){
        bin1[idx1]=dig1%2;
        dig1/=2;
        idx1++;
    }
    for(int i=0;i<4;i++)
    {
        if(bin0[3-i])
            binary0[i]=true;
        else binary0[i]=false;
        if(bin1[3-i])
            binary1[i]=true;
        else binary1[i]=false;
    }

    if(level==1){
        b2.draw(VP);
        c2.draw(VP);
    }
    else if(level==2){
        a2.draw(VP);
        b2.draw(VP);
        g2.draw(VP);
        e2.draw(VP);
        d2.draw(VP);
    }
    else if(level==3){
        a2.draw(VP);
        b2.draw(VP);
        g2.draw(VP);
        c2.draw(VP);
        d2.draw(VP);
    }

    if(score >=0){
        //bool aa0=(binary0[0] | binary0[2] | (binary0[1]&binary0[3]) | ((~(binary0[1]))&(~(binary0[3]))) );
        if((binary0[0] || binary0[2] || (binary0[1]&&binary0[3]) || ((!(binary0[1]))&&(!(binary0[3]))) ))
            a0.draw(VP);
        // bool bb0=((~binary0[1]) | (binary0[2]&binary0[3]) | ((~binary0[2])&(~binary0[3])) );
        if(((!binary0[1]) || (binary0[2]&&binary0[3]) || ((!binary0[2])&&(!binary0[3])) ))
                b0.draw(VP);
        if((binary0[1] || (!binary0[2]) || binary0[3] ))
                c0.draw(VP);
        if(((((!binary0[3])&&binary0[2]) || ((!(binary0[1]))&&(!(binary0[3])))) || (((!binary0[2])&&binary0[1]&&binary0[3]) || ((!(binary0[1]))&&((binary0[2]))) || binary0[0] )))
                d0.draw(VP);
        if((((!binary0[3])&&binary0[2]) || ((!(binary0[1]))&&(!(binary0[3]))) ))
                e0.draw(VP);
        if((binary0[0] || (((!binary0[2]))&&(!(binary0[3]))) || (((binary0[1]))&&(!(binary0[2]))) ||(((binary0[1]))&&(!(binary0[3]))) ))
                f0.draw(VP);
        if((binary0[0] || (((binary0[1]))&&(!(binary0[2]))) || ((!(binary0[1]))&&((binary0[2]))) ||(((binary0[2]))&&(!(binary0[3]))) ))
                g0.draw(VP);
            
        if((binary1[0] || binary1[2] || (binary1[1]&&binary1[3]) || ((!(binary1[1]))&&(!(binary1[3]))) ))
            a1.draw(VP);
        // bool bb0=((~binary1[1]) | (binary1[2]&binary1[3]) | ((~binary1[2])&(~binary1[3])) );
        if(((!binary1[1]) || (binary1[2]&&binary1[3]) || ((!binary1[2])&&(!binary1[3])) ))
                b1.draw(VP);
        if((binary1[1] || (!binary1[2]) || binary1[3] ))
                c1.draw(VP);
        if(((((!binary1[3])&&binary1[2]) || ((!(binary1[1]))&&(!(binary1[3])))) || (((!binary1[2])&&binary1[1]&&binary1[3]) || ((!(binary1[1]))&&((binary1[2]))) || binary1[0] )))
                d1.draw(VP);
        if((((!binary1[3])&&binary1[2]) || ((!(binary1[1]))&&(!(binary1[3]))) ))
                e1.draw(VP);
        if((binary1[0] || (((!binary1[2]))&&(!(binary1[3]))) || (((binary1[1]))&&(!(binary1[2]))) ||(((binary1[1]))&&(!(binary1[3]))) ))
                f1.draw(VP);
        if((binary1[0] || (((binary1[1]))&&(!(binary1[2]))) || ((!(binary1[1]))&&((binary1[2]))) ||(((binary1[2]))&&(!(binary1[3]))) ))
                g1.draw(VP); 
    }
    
    else
    {
        g0.draw(VP);
        g1.draw(VP);
        quit(window);
        // exit();
    }

}


void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_SPACE);
    int b = glfwGetKey(window, GLFW_KEY_B);
    double X_limit=3.7;
    double UP_Y_limit=3.9;
    double LOW_Y_limit=1.56;
    if(dia_flag>0)
        boost_flag=1;
    if(!magnet_flag){
        if(player.position.x<-X_limit || player.position.x>X_limit) 
        player.xspeed=0.0;
    // else if(player.position.y>=2.5) 
        //   player.yspeed=0.0;
        if (left && player.position.y <= -LOW_Y_limit && up && player.position.x >= -X_limit){
            player.xspeed = -0.04;
            player.yspeed = 0.1;
            if(dia_flag>0) player.xspeed-=boost;
            if(dia_flag<0 && boost_flag==1){
                 player.xspeed+=boost;
                 boost_flag=0;
            }

        }
        else if (right && player.position.y <= -LOW_Y_limit && up && player.position.x <= X_limit){
            player.xspeed = 0.04;
            if(dia_flag>0) player.xspeed+=boost;
             if(dia_flag<0 && boost_flag==1){
                 player.xspeed-=boost;
                 boost_flag=0;
            }

            player.yspeed = 0.1;
        }
        else if(player.position.y > -LOW_Y_limit ){
            if (left  && up && player.position.x >= -X_limit){
                player.xspeed = -0.04;
                if(dia_flag>0) player.xspeed-=boost;
                 if(dia_flag<0 && boost_flag==1){
                 player.xspeed+=boost;
                 boost_flag=0;
            }
                if(player.position.y>=UP_Y_limit){
                    player.yspeed = 0.0;
                }
                //player.xspeed = -0.04;
                else  player.yspeed = 0.1;
            }
            else if (right && up && player.position.x <= X_limit){
                player.xspeed = +0.04;
                            if(dia_flag>0) player.xspeed+=boost;
            if(dia_flag<0 && boost_flag==1){
                 player.xspeed-=boost;
                 boost_flag=0;
            }


                if(player.position.y>=UP_Y_limit){
                    player.yspeed = 0.0;
                }
                //player.xspeed = -0.04;
                else  player.yspeed = 0.1;
            }
            else if (right && !up && player.position.x <= X_limit){
                player.xspeed = 0.04;
                            if(dia_flag>0) player.xspeed+=boost;
            if(dia_flag<0 && boost_flag==1){
                 player.xspeed-=boost;
                 boost_flag=0;
            }


                player.yspeed += g*dt;
            }
            else if (left && !up && player.position.x >= -X_limit){
                player.xspeed = -0.04;
            if(dia_flag>0) player.xspeed-=boost;
            if(dia_flag<0 && boost_flag==1){
                 player.xspeed+=boost;
                 boost_flag=0;
            }


                player.yspeed += g*dt;
            }
            // else if(up && player.position.y<=UP_Y_limit  && !right && !left){
            //     player.xspeed=+0.00;
            //    player.yspeed=+0.04;
            // }
            else if(up && player.position.y>=UP_Y_limit){
                player.yspeed=0.00;
            }
            else if(!left && !right && !up ){  
                player.yspeed += g*dt;
                
            }
        // player.yspeed += g*dt;
        //  cout << "hello" << endl;
        }
        else if(player.position.y<=-LOW_Y_limit){
                player.yspeed=0.0;
                if(left && player.position.x>=-X_limit){
                        player.xspeed=-0.04;
                                    if(dia_flag>0) player.xspeed-=boost;
                                     if(dia_flag<0 && boost_flag==1){
                 player.xspeed+=boost;
                 boost_flag=0;
            }


                }
                else if(right && player.position.x<=X_limit){
                        player.xspeed=+0.04;
                                    if(dia_flag>0) player.xspeed+=boost;
                                     if(dia_flag<0 && boost_flag==1){
                 player.xspeed-=boost;
                 boost_flag=0;
            }


                }
                else if(up && player.position.y<=UP_Y_limit){
                        player.yspeed=+0.1;
                }
                else 
                    player.xspeed=0.0;
        }
    }
    else{
        double XP = player.position.x, YP = player.position.y;
        double XM = magnet.position.x, YM = magnet.position.y;
        double acc = -g+.05;
        double dis=sqrt(pow(YP-YM,2)+pow(XP-XM,2));
        double sinx=abs((YM-YP))/(dis);
        double cosx=abs((XM-XP))/(dis);
        
       // cout<<"thettaa radian  ->" << theta<< '\n';
        //cout<<"thettaa degree  ->" << theta_degree<< '\n';
        //cout<<"slope = tan(theta)  ->"<< (YM-YP)/(XM-XP) << '\n';
         if(player.position.x<-X_limit || player.position.x>X_limit) 
            player.xspeed=0.0;

       // if(player.position.y>=YM-0.5){
         //     player.yspeed=0.0;
       // }
              //player.position.y
        // else if(player.position.y<-LOW_Y_limit || player.position.y>UP_Y_limit) 
        //   player.yspeed=0.0;
        if (left && player.position.y <= -LOW_Y_limit && up && player.position.x >= -X_limit){
            player.xspeed = -0.04 ;
            player.yspeed = 0.1;
            if(dia_flag>0) player.xspeed-=boost;
            if(dia_flag<0 && boost_flag==1){
                 player.xspeed+=boost;
                 boost_flag=0;
            }
        }
        else if (right && player.position.y <= -LOW_Y_limit && up && player.position.x <= X_limit){
            player.xspeed = 0.04;
            player.yspeed = 0.1;
            if(dia_flag>0) player.xspeed+=boost;
            if(dia_flag<0 && boost_flag==1){
                 player.xspeed-=boost;
                 boost_flag=0;
            }
        }
        else if(player.position.y > -LOW_Y_limit ){
            if (left  && up && player.position.x >= -X_limit){
                player.xspeed = -0.04;
                if(dia_flag>0) player.xspeed-=boost;
            if(dia_flag<0 && boost_flag==1){
                 player.xspeed+=boost;
                 boost_flag=0;
            }
                if(player.position.y>=UP_Y_limit){
                    player.yspeed = 0.0;
                }
                //player.xspeed = -0.04;
                else  player.yspeed = 0.1;
            }
            else if (right && up && player.position.x <= X_limit){
                player.xspeed = +0.04;
                if(dia_flag>0) player.xspeed+=boost;
             if(dia_flag<0 && boost_flag==1){
                 player.xspeed-=boost;
                 boost_flag=0;
            }
                if(player.position.y>=UP_Y_limit){
                    player.yspeed = 0.0;
                }
                //player.xspeed = -0.04;
                else  player.yspeed = 0.1;
            }
            else if (right && !up && player.position.x <= X_limit){
                player.xspeed = 0.04;
                if(dia_flag>0) player.xspeed+=boost;
            if(dia_flag<0 && boost_flag==1){
                 player.xspeed-=boost;
                 boost_flag=0;
            }
                player.yspeed += g*dt;
            }
            else if (left && !up && player.position.x >= -X_limit){
                player.xspeed = -0.04;
                if(dia_flag>0) player.xspeed-=boost;
            if(dia_flag<0 && boost_flag==1){
                 player.xspeed+=boost;
                 boost_flag=0;
            }
                player.yspeed += g*dt;
            }
            // else if(up && player.position.y<=UP_Y_limit  && !right && !left){
            //     player.xspeed=+0.00;
            //    player.yspeed=+0.04;
            // }
            else if(up && player.position.y>=UP_Y_limit){
                player.yspeed=0.00;
            }
            else if(!left && !right && !up ){  
                player.yspeed += g*dt;
            }
        // player.yspeed += g*dt;
        //  cout << "hello" << endl;
        }
        else if(player.position.y<=-LOW_Y_limit){
                player.yspeed=0.0;
                if(left && player.position.x>=-X_limit){
                        player.xspeed=-0.04;
                        if(dia_flag>0) player.xspeed-=boost;
            if(dia_flag<0 && boost_flag==1){
                 player.xspeed+=boost;
                 boost_flag=0;
            }
                }
                else if(right && player.position.x<=X_limit){
                        player.xspeed=+0.04;
                        if(dia_flag>0) player.xspeed+=boost;
            if(dia_flag<0 && boost_flag==1){
                 player.xspeed-=boost;
                 boost_flag=0;
            }
                }
                else if(up && player.position.y<=UP_Y_limit){
                        player.yspeed=+0.1;
                }
                else 
                    player.xspeed=0.0;
        }
       if(XP<=XM){
            if(player.position.y<=YM-0.1){
                player.xspeed+=acc*cosx*dt/10.0;
                player.yspeed+=acc*sinx*dt;
            }
        }
        else{
                if(player.position.y<=YM-0.1)
            {
                    player.xspeed-=acc*cosx*dt/10.0;
                    player.yspeed+=acc*sinx*dt;
            }
        }

    }
      //      player.yspeed=0.0;
  //  }
    // else if(right && !up && player.position.x <= 3.6){
    //     player.xspeed = 0.04; //when left or right key is released
    //     player.yspeed = 0.0; //when left or right key is released
    // }
    // else if(left && !up && player.position.x >= -3.6){
    //     player.xspeed = -0.04; //when left or right key is released
    //     player.yspeed = 0.0; //when left or right key is released
    // }
    
    
    //  else if(up && !right && !left && player.position.y <= 4){
    //      player.yspeed = 0.1;
    //      player.xspeed = 0.0;
    //  }
    //  else{
    //      player.xspeed =0.0;
    //      player.yspeed =0.0;
    //  }

    // //jump
    // if (up == GLFW_PRESS && player.position.y <= 4) { 
    //     player.yspeed = 0.10;
    // }
    // if (up == GLFW_PRESS && player.position.y >= 4) { 
    //     player.yspeed = 0.0;
    // }
    // if (up == GLFW_RELEASE && player.position.y >= -LOW_Y_limit){
    //     player.yspeed += g*dt;
    //     player.xspeed = 0.02;
    // }
    // if (up == GLFW_RELEASE && player.position.y <= -LOW_Y_limit){
    //     player.yspeed = 0.0;
    //     player.xspeed = 0.0;
    // }
    
    // //balloon
    // if(b && balloon_flag==0){
    //     balloon_flag=1;
    // } 
    // else balloon_flag=0;

    // // if(b){
    // //      balloon_counter++;
    // // }
    // // if(balloon_counter%10==0){
    // //     balloon_flag=1;
    // // }

}

void tick_elements() {
// //balloon generate
//     for(int i=0; i<40; i++){
//     balloon[i] = Balloon(player.position.x, player.position.y, COLOR_MAGNET2);
//     }
    // cout << dt << endl;
    if(score >=0){
        a0.tick();
        b0.tick();
        c0.tick();
        d0.tick();
        e0.tick();
        f0.tick();
        g0.tick();
        a1.tick();
        b1.tick();
        c1.tick();
        d1.tick();
        e1.tick();
        f1.tick();
        g1.tick();
        a2.tick();
        b2.tick();
        c2.tick();
        d2.tick();
        e2.tick();
        f2.tick();
        g2.tick();
    }
    
    //wall
    for(int i=0; i<22; i++){
        wall[i].tick();
        wall[i].speed = 0.02;
    }

    //fireline
    for(int i=0; i<28; i++){
        fireline[i].tick();
        if(detect_collision(player.bounding_box(), fireline[i].bounding_box())){
            if(sword_flag2 <= 0){
                score-=1;
                fireline_active[i] = -1;
            }
        }

        if(fireline_active[i] <= -1){
            fireline_active[i] -=1;
        }
        double old;
        if(fireline_active[i]<0 && fireline_active[i]>-150 ){
            old = fireline[i].position.x;
            fireline[i].position.x = -12;
        }
        else if(fireline_active[i] == -150.0)
        {
            fireline[i].position.x = old - 100*0.02;
        }
        fireline[i].speed = 0.02;        
        
    }

    //firebeam
    for(int i=0; i<15; i++){
        firebeam[i].xspeed = 0.02;
        if(prev_speed == 0.0){
            firebeam[i].yspeed = 0.02;
            prev_speed = 0.02;
        }
        else if(firebeam[i].position.y < -1.0){
            firebeam[i].yspeed = 0.02;
            prev_speed = 0.02;
        } 
        else if(firebeam[i].position.y > 3.5){
            prev_speed = -0.02;
            firebeam[i].yspeed = -0.02;
        }
        else if(firebeam[i].position.y <= 3.5 && firebeam[i].position.y >= -1.0){
            firebeam[i].yspeed = prev_speed;
        }
        firebeam[i].tick();
        if(detect_collision(player.bounding_box(), firebeam[i].bounding_box())){
            if(sword_flag2 <= 0){
                score-=2;
                firebeam_active[i] = -1;
            }
        }
        if(firebeam_active[i] <= -1){
            firebeam_active[i] -=1;
        }
        double old2;
        if(firebeam_active[i]<0 && firebeam_active[i]>-150 ){
            old2 = firebeam[i].position.x;
            firebeam[i].position.x = -12;
        }
        else if(firebeam_active[i] == -150.0)
        {
            firebeam[i].position.x = old2 - 100*0.02;
        }
    }

    // arrow.tick();
    for(int i=0; i<1; i++){
        arrow[i].tick();
        // arrow[i].rotation += 1;
        arrow[i].xspeed = -0.03;
        if(arrow[i].position.y >= 3.0){
            arrow[i].yspeed -= 0.001;
        }
        else if(arrow[i].position.y <= -1.0){
            arrow[i].yspeed += 0.001;
        }
        if(detect_collision(player.bounding_box(), arrow[i].bounding_box())){
            sword_flag =1;
        }

    }
    //sword
    if(sword_flag >= 1) sword_flag+= 1;
    sword.tick();
    // cout << sword_flag << " " << sword_flag2 << endl;
    sword.position.x=player.position.x+0.1;
    sword.position.y=player.position.y - 0.5;

    // diamond.tick();
    for(int i=0; i<1; i++){
        diamond[i].tick();
        diamond[i].rotation += 2;
        diamond[i].xspeed = -0.03;
        if(diamond[i].position.y >= 3.0){
            diamond[i].yspeed -= 0.001;
        }
        else if(diamond[i].position.y <= -1.0){
            diamond[i].yspeed += 0.001;
        }
        if(detect_collision(player.bounding_box(), diamond[i].bounding_box())){
            dia_flag =1;
        }
    }
    if(dia_flag >= 1 && dia_flag < 480) dia_flag +=1;
    else if(dia_flag >= 6)dia_flag =-1;
   // if(dia_flag > 0) player.xspeed +=0.01; //!!ERROR!!
    
    //t+=0.01;

//    cout << t1 << " " << t2 << endl;
    magnet.tick();
    // magnet.speed = -0.01;

    for(int i=0; i<2; i++){
        if(prev_speed_fox == 0){
            fox[i].xspeed = -0.02;
            fox[i].yspeed = 0.0;
            prev_speed_fox = -1;
        }
        if(fox[i].position.x >= 3.7){
            fox[i].xspeed = -0.02;
            fox[i].yspeed = 0.0;
            prev_speed_fox = -1;
        }
        else if(fox[i].position.x < 1){
            fox[i].xspeed += 0.007;
            prev_speed_fox = 1;
            fox[i].yspeed = -0.09;
        }
        else if(fox[i].position.x >= 1 && fox[i].position.x <= 3.7){
            if(prev_speed_fox == -1){
                fox[i].xspeed -= 0.004;
                fox[i].yspeed = -0.04;
            }
            else if(prev_speed_fox == 1){
                fox[i].xspeed += 0.007;
                fox[i].yspeed = -0.09;
            }
        }
        fox[i].tick();
        if(detect_collision(player.bounding_box(), fox[i].bounding_box())){
            if(sword_flag2 <= 0){
                score-=4;
                fox_active[i] = -1;
            }
        }
        if(fox_active[i] <= -1){
            fox_active[i] -=1;
        }
        double old3;
        if(fox_active[i]<0 && fox_active[i]>-120 ){
            old3 = fox[i].position.x;
            fox[i].position.x = -12;
        }
        else if(fox_active[i] == -120.0)
        {
            fox[i].position.x = old3 - 80*0.02;
        }
    }
        // cout << "fox.x ->" << fox[0].position.x << endl;
        // cout << "fox222222.x ->" << fox[1].position.x << endl;
        // cout << "fox.y ->" << fox[1].position.x << endl;
        // cout << "fox.xspeed ->" << fox[1].xspeed << endl;
        // cout << "fox.yspeed ->" << fox[1].yspeed << endl;
    //dragon
    dragon.tick();
    if(detect_collision(player.bounding_box(), dragon.bounding_box())){
            if(sword_flag2 <= 0){
                score-=20;
                dragon_active = -1;
            }
        }
        if(dragon_active <= -1){
            dragon_active-=1;
        }
        double old3;
        if(dragon_active<0 && dragon_active>-120 ){
            old3 = dragon.position.x;
            dragon.position.x = -12;
        }
        else if(dragon_active == -120.0)
        {
            dragon.position.x = old3 - 80*0.02;
        }

    dragon.xspeed = -0.02;

   // iceball
    // for(int i =0; i<40; i++){
    //     iceball[i].tick();
    //     if(i%3==0){
    //         iceball[i].xspeed=-0.04;
    //         iceball[i].yspeed=0.00;
    //     }
    //     if(i%3==1){
    //         iceball[i].xspeed=0.0;
    //         iceball[i].xspeed=-0.04;
    //     }
    //     if(i%3==2){
    //         iceball[i].xspeed=-0.04;
    //         iceball[i].xspeed=-0.04;
    //     }
    // }

    if(prev_speed == 0.0){
        dragon.yspeed = 0.02;
        prev_speed = 0.02;
    }
    else if(dragon.position.y <= -1.0){
        dragon.yspeed = -0.02;
        prev_speed = -0.02;
    }
    else if(dragon.position.y >= 3.5){
        prev_speed = 0.02;
        dragon.yspeed = 0.02;
    }
    else if(dragon.position.y < 3.5 && dragon.position.y > -1.0){
        dragon.yspeed = prev_speed;
    }
    
    //coin
    for(int i=0; i<30; i++){
        coin1[i].tick();
        coin1[i].speed = 0.02;
        if(detect_collision(player.bounding_box(), coin1[i].bounding_box())){
            score += 5;
            coin1[i].position.x = -6.0;
        }
        // cout << "score " << score <<endl;

    }

    for(int i=0; i<30; i++){
        coin2[i].tick();
        coin2[i].speed = 0.02;
        if(detect_collision(player.bounding_box(), coin2[i].bounding_box())){
            score += 3;
            coin2[i].position.x = -6.0;
        }
        // cout << "score " << score <<endl;

    }
    //platform
    platform.tick();
    ring.tick();
    ring.speed = -0.02;
    //player
    player.tick();
    // cout << "player " << player.position.x <<endl;
    // for(int i=0; i<balloon_number+1; i++){
    //     balloon[i].tick();
    //     balloon[i].speed = 0.005;
    //      cout << "balloon" << i << " " << balloon[i].position.x << " " << balloon[i].position.y << endl;
    //      cout << "player" << i << " " << player.position.x << " " << player.position.y << endl;
    //     cout << "flag " << balloon_flag << " number " << balloon_number << endl;
    //     cout << "counter " << balloon_counter << endl;
    // }
    camera_rotation_angle += 1;

}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    for(int i=0; i<30; i++){
        firebeam_active[i]=1;
        fireline_active[i]=1;
        if(i<3)
            fox_active[i]=1;
    }

    //wall
    double x = -0.7, y = 0;
    for(int i=0; i<22; i++){
        wall[i] = Wall(x, y, COLOR_WALL);
        x += 5;
    }
    //coin
    for(int i=0; i<30; i++){
        double x = RandomNumber(-1, 100.0);
        double y = RandomNumber(-1, 3.5);
        coin1[i] = Coin(x, y, COLOR_COIN);
    }

    for(int i=0; i<30; i++){
        double x = RandomNumber(-1, 100.0);
        double y = RandomNumber(-1, 3.5);
        coin2[i] = Coin(x, y, COLOR_BLUSH);
    }
    //fireline
    for(int i=0; i<28; i++){
        double x = RandomNumber(-1, 100.0);
        double y = RandomNumber(-0.1, 3.5);
        fireline[i] = Fireline(x, y, COLOR_FIRE1);
        fireline[i].rotation = RandomNumber(0, 180);
    }

    //firebeam
    for(int i=0; i<15; i++){
        double x = RandomNumber(-1, 100.0);
        double y = RandomNumber(-1.0, 3.5);
        // cout << y << endl;
        firebeam[i] = Firebeam(x, y, COLOR_FIRE2);
    }

    //arrow - special flying objects - power up
    for(int i=0; i<1; i++){
        double y =0.0;
        double x = RandomNumber(4.0, 20.0);
        if(int(x)%2 == 0)
            y = RandomNumber(-3.0, -2.0);
        else
            y = RandomNumber(4.0, 5.0);        
        arrow[i]=Arrow(x, y, COLOR_GREEN);
    }
    //sword
    sword = Arrow(player.position.x, player.position.y, COLOR_WHITE);
    sword.rotation = 180;
    //diamond - special flying objects - power up
    for(int i=0; i<1; i++){
        double y =0.0;
        double x = RandomNumber(50.0, 80.5);
        // double x = RandomNumber(5.0, 8.5);
        if(int(x)%2 == 0)
            y = RandomNumber(-3.0, -2.0);
        else
            y = RandomNumber(4.0, 5.0);
        diamond[i]=Diamond(x, y, COLOR_PINK);
        // cout<< diamond[i].position.y <<endl;
        // cout<< x <<endl;
        // cout<< y <<endl;
        // cout<< int(x)%2 <<endl;
    }

    //fox - boomerang
    for(int i=0; i<1; i++){
        double x = RandomNumber(10.0, 70.0);
        double y = 3.5;
        fox[0] = Fox(x, y, COLOR_DARK_ORANGE);
        fox[1] = Fox(x+30, y, COLOR_DARK_ORANGE);
    } 

    //magnet
    double magnet_x = RandomNumber(-1.0, 2.0);
    double magnet_y = RandomNumber(2.5,3.0);
    magnet = Magnet(magnet_x, magnet_y, COLOR_MAGNET1);
    magnet.rotation = RandomNumber(0, 180);

    //seven seg
    double dx=0.75;
    double dy=-5.5;
    a0 = A0(3.0+dx ,3.0+dy, COLOR_MAGNET1);
    b0 = A0(2.48+dx, 2.45+dy, COLOR_MAGNET1);
    c0 = A0(2.48 +dx,2.19+dy, COLOR_MAGNET1);
    d0 = A0(3.0 +dx,2.48+dy, COLOR_MAGNET1);
    e0 = A0(2.27 +dx,2.19+dy, COLOR_MAGNET1);
    f0 = A0(2.27 +dx,2.45+dy, COLOR_MAGNET1);
    g0 = A0(3.0 +dx,2.74+dy, COLOR_MAGNET1);
    b0.rotation =90;
    c0.rotation =90;
    e0.rotation =90;
    f0.rotation =90;
    double DX=0.30;
    a1 = A0(3.0+dx-DX ,3.0+dy, COLOR_MAGNET1);
    b1 = A0(2.48+dx-DX, 2.45+dy, COLOR_MAGNET1);
    c1 = A0(2.48 +dx-DX,2.19+dy, COLOR_MAGNET1);
    d1 = A0(3.0 +dx-DX,2.48+dy, COLOR_MAGNET1);
    e1 = A0(2.27 +dx-DX,2.19+dy, COLOR_MAGNET1);
    f1 = A0(2.27 +dx-DX,2.45+dy, COLOR_MAGNET1);
    g1 = A0(3.0 +dx-DX,2.74+dy, COLOR_MAGNET1);
    b1.rotation =90;
    c1.rotation =90;
    e1.rotation =90;
    f1.rotation =90;

    //level
    double lx=7.2;
    a2 = A0(3.0+dx-lx ,3.0+dy, COLOR_MAGNET1);
    b2 = A0(2.48+dx-lx, 2.45+dy, COLOR_MAGNET1);
    c2 = A0(2.48 +dx-lx,2.19+dy, COLOR_MAGNET1);
    d2 = A0(3.0 +dx-lx,2.48+dy, COLOR_MAGNET1);
    e2 = A0(2.27 +dx-lx,2.19+dy, COLOR_MAGNET1);
    f2 = A0(2.27 +dx-lx,2.45+dy, COLOR_MAGNET1);
    g2 = A0(3.0 +dx-lx,2.74+dy, COLOR_MAGNET1);
    b2.rotation =90;
    c2.rotation =90;
    e2.rotation =90;
    f2.rotation =90;

    //platform
    platform = Platform(-2, -3,COLOR_PLATFORM);

    //player
    player = Player(-3.5, -1.0, COLOR_BACKGROUND);

    //ring
    double ring_x = RandomNumber(2.0, 6.0);
    ring = Ring(ring_x, -2, COLOR_WHITE);

    //balloon
    

    //dragon
    double dragon_x = RandomNumber(80, 90);
    double dragon_y = 1.0;
    dragon = Dragon(dragon_x, dragon_y, COLOR_DRAGON1);

    //balloon generate
    for(int i=0; i<40; i++){
    // iceball[i] = Balloon(dragon.position.x, dragon.position.y, COLOR_DRAGON1);
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
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

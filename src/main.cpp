#include "main.h"
#include "timer.h"
#include "ball.h"
#include "ground.h"
#include "balls.h"
#include "spikes.h"
#include "rectangle.h"
#include "semi.h"
#include "magnet.h"
#include "slide.h"
#include "star.h"
#include "arrow.h"
#include "exit.h"
#include "digit.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include <cstring>
#include <string>
#include <sstream>

//to include glut
//#include <GL/glut.h>
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball player,coin;
// exit rectangles
Exit rec3,brick;

Ground ground,ground2;
int number_balls = 200;
int number_spikes = 3;
int frame_ref;
Balls balls[200]; //balls which are to be destroyed
Spikes spike[5]; // spikes which should appear after some level
Rectangle rec1,rec2; // two rectangles for the trampoline
Slide slab[100]; // rectangles for the slab on the balls
int count = 0; // count for the number of rectangles used as the slab
Magnet magnet,magnet2; // magnets
Arrow arrow; //used to show direction
color_t color_array[7]; // color array
float speeds_balls[4]; //speeds the balls can have
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
Semi half_circle,water; // used for the trampoline and pond
Timer t60(1.0 / 60);
Timer timer(14.0),timex(5.0),arrow_timer1(2.0/60) , arrow_timer2(3.0/60); //timers for the stars and the magnets and arrow
Star star; // star which will be used to end the game
float frame = 0; // this will be used to shift the frames
int level1 = 2,level2 = 2,level3 = 4; //minimum score required to cross that particular level
Digit d1,d2,d3; //digits for the score
//GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24; //for displaying the text



/*void drawBitmapText(char *string,float x,float y,float z)
{
	char *c;
	glRasterPos3f(x, y,z);

	for (c=string; (*c) != 0; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
	}
}
void render(void)
{
	//glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	drawBitmapText("Osama Hosam's OpenGL Tutorials",3,0,0);
	//glutSwapBuffers();
}*/

// try function for drawing the text on the screen
/*void draw_text(const char *text , int length , int x , int  y)
{
        glMatrixMode(GL_PROJECTION);
        double *matrix = new double[16];
        glGetDoublev(GL_PROJECTION_MATRIX , matrix);
        glLoadIdentity();
        glOrtho(0,800,0,600,-5,5);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();
        glLoadIdentity();
        glRasterPos2i(x,y);

        for(int i=0;i<length;i++)
        {
          glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int)text[i]);
        }
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixd(matrix);
        glMatrixMode(GL_MODELVIEW);


}*/

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(frame, 0, 3), glm::vec3(frame, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model


    // Scene render

    //write the code here
    ground.draw(VP); // for drawing the floor
    ground2.draw(VP);


    //draw the exit rec3
    if(frame_ref == 2)
    {
    rec3.draw(VP);
    brick.draw(VP);
    }

    //for all the balls
    for(int i=0;i<number_balls;i++)
    {
        if(balls[i].is_alive == 1)
        {
            balls[i].draw(VP);
        }

    }

    //for all the slabs used
    for(int i=0;i<count;i++)
    {
        slab[i].draw(VP);
    }

    //for all the spikes if player level is not one
    if(player.level != 1)
    {
    for(int i=0;i<number_spikes;i++)
    {
      if(spike[i].is_active == 1)
        spike[i].draw(VP);
    }
    }

    //draw the trampoline
    rec1.draw(VP);
    rec2.draw(VP);
    half_circle.draw(VP);

    //draw the pond
    water.draw(VP);

    //draw the magnets if wanted player level is not one
    if(player.level != 1)
    {
      if(magnet.is_active == 1)
      {
        magnet.draw(VP);
      }
      if(magnet2.is_active == 1)
      {
        magnet2.draw(VP);
      }
    }
    //drawing the star if the player level is 3
    if(player.level == 3)
  {
    if(star.is_active == 1)
    {
      star.draw(VP);
    }
  }
    //draw if not killed by spikes
    if(player.is_killed == 0)
    {
      player.draw(VP); // for drawing the player
    }
    else
    {
      exit(1);
    }
    //draw the coin if frame is 2 and when it is not is_killed
    if(coin.is_killed == 0 && frame_ref == 2)
    {
      coin.draw(VP);
    }

    //draw the direction array
    if(player.level != 3)
    {
    if(frame_ref != 2){
    if(arrow.is_active == 1)
    arrow.draw(VP);
    }
    }

    int score_of_player = player.score;
    //inti for the digits
    d1 = Digit(-3.7+frame,4,player.level);

    d2 = Digit(3+frame,4,(score_of_player/10) % 100);
    d3 = Digit(3.7+frame,4,score_of_player % 10);



    //draw the score
    //render();
    d1.draw(VP);
    d2.draw(VP);
    d3.draw(VP);
    /*std::string text;
    text = "Hey how are you";
    glColor3f(0,1,0);
    draw_text(text.data(),text.size(),0,0);*/

    /*printf( "char: %c, decimal: %d, float: %f, string: %s", 'X', 1618, 1.618, "text");
    printw(0, 3, 0, "char: %c, decimal: %d, float: %f, string: %s", 'X', 1618, 1.618, "text");
    renderBitmapString(-1.2f, -0.2f , -5.0f, GLUT_BITMAP_HELVETICA_18, "'Y pos'");
    */

}

void tick_input(GLFWwindow *window) {
    glm::vec3 player_pos = player.position; // position of the ball 2
    //glm::vec3 pos1 = ball1.position; // position of the ball 1
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int space = glfwGetKey(window , GLFW_KEY_SPACE);
    int up = glfwGetKey(window,GLFW_KEY_UP);
    if (left) {
        // Do something

        bounding_box_t temp;
        temp.x = player_pos[0] - 0.05;
        temp.y = player_pos[1];
        temp.width = 0.5;
        temp.height = 0.5;
        bool move = true;

        //for checking if the player can move or not if not level 1
        if(player.level != 1)
        {
        for(int i=0;i<number_spikes;i++)
        {   if(spike[i].is_active == 1)
          {
            if(detect_collision(temp,spike[i].bounding_box()))
            {
                move = false;
            }
          }
        }
        }
        //check for the rectangles
        if(detect_collision(temp,rec1.bounding_box()) || detect_collision(temp,rec2.bounding_box()))
        {
                //printf("entered \n");
                move = false;
        }


        if(move)
        {
        player.set_position(player_pos[0]-0.05,player_pos[1]);
        player.rotation += 10;
        }
        //ball1.rotation = ball1.rotation - 1; for rotation

        //check for the pond surface
        if(player.ball_water == 1)
        {
          int flag = 0;

          if(player.position.x >= 0)
          {
          player.position.x = 0;
          }
          if(player.position.x <= -1.6)
          {
            player.position.x = -1.65;
            player.position.y = -1.22;
            flag = 1;
          }
          if((player.position.x <= -0.1 && player.position.x >= -1.2))
          {
            flag = 1;
          }

          if(flag == 0)
          {
          float y_pond = -(float)sqrt((0.8*0.8)-(player.position.x + 0.8)*(player.position.x + 0.8)) - 1.5;
          if(y_pond < -2.25)
          y_pond = -2.22;
          player.set_position(player.position.x,y_pond);
          }
        }

    }
    if(right){


        bounding_box_t temp;
        temp.x = player_pos[0] + 0.05;
        temp.y = player_pos[1];
        temp.width = 0.5;
        temp.height = 0.5;

        //for checking if it can move or not
        bool move = true;

        //check for the spikes if exist and level is not 1
        if(player.level != 1)
        {
        for(int i=0;i<number_spikes;i++)
        {
            if(detect_collision(temp,spike[i].bounding_box()))
            {
                move = false;
            }
        }
      }

        //check for the rectangles
        if(detect_collision(temp,rec1.bounding_box()) || detect_collision(temp,rec2.bounding_box()))
        {
                //printf("entered deefds\n");
                //printf("%f %f\n",temp.x , temp.y);
                //printf("%f %f dcd \n",rec1.position.x , rec1.position.y);
                move = false;

        }

        if(move)
        {
        player.set_position(player_pos[0]+0.05,player_pos[1]);
        player.rotation -= 10;
        }
        //ball1.rotation = ball1.rotation + 1; for rotation

        if(player.ball_water == 1)
        {
          int flag = 0;
          if(player.position.x >= 0)
          {
          player.position.x = 0.25; /// 0 is original value
          player.position.y = -1.22;
          flag = 1;
          }
          if(player.position.x <= -1.6)
          {
            player.position.x = -1.58;
          }
          if((player.position.x <= -0.1 && player.position.x >= -1.2))
          {
            flag = 1;
          }
          if(flag == 0)
          {
          float y_pond = -(float)sqrt((0.8*0.8)-(player.position.x + 0.8)*(player.position.x + 0.8)) - 1.5;
          if(y_pond < -2.25)
          {
          y_pond = -2.22;
          //player.position.x = -0.8;
          }

          player.set_position(player.position.x,y_pond);
          }
          //printf("player at main.cpp %f %f",player.position.x , player.position.y);
        }

    }

    if(player.ball_air != 1)
    {
    if(up)
    {

        if(player.ball_water == 1)
        {
          player.speedy = 0.15;
        }
        else{
        player.speedy = 0.25;
            }
        player.ball_air = 1;

    }
    }

}

void tick_elements() {

    frame_ref = (int)round(player.position.x/7.4);
    frame = 7.4 * frame_ref;

    //set the positions accotding to frames
    star.set_position(star.start_x+frame , star.start_y);
    magnet.set_position(magnet.start_x + frame , magnet.start_y);
    magnet2.set_position(magnet2.start_x + frame,magnet2.start_y);
    ground.set_position(ground.start_x + frame , ground.start_y);
    ground2.set_position(ground2.start_x + frame , ground2.start_y);
    rec1.set_position(rec1.start_x + frame,rec1.start_y);
    rec2.set_position(rec2.start_x + frame , rec2.start_y);
    half_circle.set_position(half_circle.start_x + frame , half_circle.start_y);
    arrow.set_position(arrow.start_x + frame,arrow.start_y);
    rec3.set_position(rec3.start_x + frame,rec3.start_y);
    brick.set_position(brick.start_x + frame , brick.start_y);
    player.tick(); //player tick
    coin.tick();


    //check if player had reached level 1 score
    if(player.score >= level1 && player.level == 1)
    {
      rec3.colour = COLOR_DEEPBLUE;
    }
    //check if player had reached level 2 score
    if(player.score >= level2 && player.level == 2)
    {
      rec3.colour = COLOR_DEEPBLUE;
    }
    else if(player.score <= level2 && player.level == 2)
    {
      rec3.colour = COLOR_DEEPRED;
    }

    //check score and object touch for level up
    if(player.score >= level1 && player.level == 1 && frame_ref == 2 && detect_collision(player.bounding_box(),rec3.bounding_box()))
    {
      player.level = 2; //level up
      coin.set_position(coin.start_x,coin.start_y);
      coin.is_killed = 1; //killed when level up
      coin.ball_air = 0; //should not fall
      coin.done = 0;
      rec3.colour = COLOR_DEEPRED;
      brick.colour = COLOR_BROWN;
      player.score = 0; //make score as zero
      player.set_position(player.start_x,player.start_y);
    }

    //check score and object touch for the level up
    if(player.score >= level2 && player.level == 2 && frame_ref == 2 && detect_collision(player.bounding_box(),rec3.bounding_box()))
    {
      player.level = 3;
      player.score = 0;
      coin.set_position(coin.start_x,coin.start_y);
      coin.is_killed = 1; //killed when level up
      coin.ball_air = 0; //should not fall
      coin.done = 0;
      brick.colour = COLOR_BROWN;
      player.set_position(player.start_x,player.start_y);
    }

    //check collision with the brick in the 2 nd frame
    if(coin.done == 0)
    {
    if(frame_ref == 2 && detect_collision(player.bounding_box(),brick.bounding_box()))
    {
      brick.colour = COLOR_BLACK;

      coin.is_killed = 0; //make it appear
      coin.ball_air = 1; //make it fall
    }
  }

    //check collision with the coin in 2 nd frame if not already killed
    if(coin.is_killed == 0)
    {
      if(frame_ref == 2 && detect_collision(player.bounding_box(),coin.bounding_box()))
      {
        player.score += 10;
        coin.is_killed = 1;
        coin.done = 1; //done adding the score
        //printf("coin got by the player \n");
      }
    }
    //check for the landing of the ball on the brick;
    if(frame_ref == 2)
    {
    if((player.speedy <=0 && detect_collision(player.bounding_box(),brick.bounding_box()) && player.position.y
        >= brick.position.y))
        {

          if(player.on_brick == 0)
          {
            player.position.y = brick.position.y + brick.length/2 + 0.25;
            player.speedy = 0;
            player.on_brick = 1;
          }
          player.gravity = 0;
          //player.ball_air = 0;
          //printf("enter the brick \n");
        }
        else
        {
          player.gravity = 0.02;
          player.on_brick = 0;
        }
      }

    //ground.set_position(ground)
    //check for the star
    if(player.level == 3)
    {
    if(star.is_active == 1)
    {
      //if it touches the star
      if(detect_collision(player.bounding_box(),star.bounding_box()) && player.score >= level3) //chek for level 3 or game over
      {
        star.is_active = 0;
        player.is_killed = 1; //game over
        printf("game over \n");
      }
    }
    }

    //check if the ball is in pond

    if((player.position.x <= 0.07 && player.position.x>=-1.6) && (player.position.y < -1.22)) {

      player.ball_water = 1; // ball is still in water
      /*if(player.position.y > -1.5 && player.speedy == 0 && ((player.position.x >= -0.04) || (player.position.x <= -1.6)))
      {
      player.position.y = -1.5;
      player.position.x = -0.05;
    }*/
      //printf("ball is in water %d \n",player.ball_water);
    }
    else
    {
      player.ball_water = 0; // ball is not in water
    }

    if(player.position.y > -1.2)
    {
      player.ball_air = 1;
    }

    for(int i=0;i<number_balls;i++)
    {
        if(balls[i].is_alive == 1)
        {
            balls[i].tick();
        }
    }

    //for the slabs tick
    for(int i=0;i<count;i++)
    {
        slab[i].tick();
    }
    //checking for the collision of the player with the slabs
    int flag = 0;
    for(int i=0;i<count;i++)
    {
        if(player.speedy <= 0 && (player.position.y >= slab[i].position.y))
        {
          if(detect_collision(player.bounding_box(),slab[i].bounding_box()))
          {
            //printf("collision with slab detected  %d \n",slab[i].dirc);
            flag = 1;
            if(slab[i].dirc == 1)
            {
              //printf("left \n");
              player.speed = -0.06;
              player.speedy = 0.1;
              //printf("left collision %f %f",player.speed , player.speedy);
            }
            else if(slab[i].dirc == 2)
            {
              //printf("right \n");
              player.speed = 0.06;
              player.speedy = 0.1;
              //printf("Right collision %f %f",player.speed , player.speedy);
            }
            break;
          }

        }


    }


    //checking for the collision of player with each ball
    if(flag == 0)
    {
    for(int i=0;i<number_balls;i++)
    {
        if(balls[i].is_alive == 1)
        {
        if(player.speedy <= 0 && (player.position.y >= balls[i].position.y))
        {
        if(detect_collision(player.bounding_box(),balls[i].bounding_box()))
        {

            balls[i].is_alive = 1;
            //balls[i].position.x = balls[i].start_x;
            if(balls[i].index_of_slide >= 0)
            {
              // do something
              if(balls[i].dir == 1){
                slab[balls[i].index_of_slide].position.x = slab[balls[i].index_of_slide].start_x
                - balls[i].radius/2  - balls[i].radius/4;
              }
              else if(balls[i].dir == 2)
              {
  slab[balls[i].index_of_slide].position.x = slab[balls[i].index_of_slide].start_x + balls[i].radius/2 + balls[i].radius/4;
              }

            }
            balls[i].position.x = balls[i].start_x;
            // we have to boost the player up here
            player.speedy = 0.25;
            player.score += balls[i].score;
            printf("%d\n",player.score);
            continue;
        }

        }
        }

    }
}
    //checking for the collision of the player with spikes
    if(player.level != 1)
    {
    for(int i=0;i<number_spikes;i++)
    {
      spike[i].set_position(spike[i].start_x + frame,spike[i].position.y);
      if(spike[i].is_active == 1)
      {
        if(detect_collision(player.bounding_box(),spike[i].bounding_box()))
        {
            if(player.score >= 5)
            {
            player.score -= 5; // decreasing the score if the collision occurs
            }
            player.set_position(player.start_x,player.start_y); // set the ball to its original position
        }
      }
    }
    }

    //checking for the catapult
    if(detect_collision(player.bounding_box(),half_circle.bounding_box()))
    {
        player.speedy = 0.3;
    }

    //checking for the timers to introduce magnet for every 14 second
    if(player.level != 1)
    {
    if(timer.processTick())
    {
      int magnet_rand = rand()%2;
      if(magnet_rand == 0)
      {
      magnet.is_active = 1;
      }
      else if(magnet_rand == 1)
      {
        magnet2.is_active =1;
      }
      if(player.level == 3)
      star.is_active = 1; //activating the star for every 14 secs
    }

    //deadline timer  for every 5 secs
    if(timex.processTick())
    {
      magnet.is_active = 0;
      magnet2.is_active = 0;
      if(player.level == 3)
      {
      star.is_active = 0;
      //change the position of the star
      float star_x = rand()%4;
      float star_y = 3.0;
      int rand_nums = rand()%2;
      if(rand_nums == 0)
      star_x = star_x;
      else
      star_x = -star_x;

      star.set_position(star_x,star_y);
      }
    }

    //deadline for star
    /*if(time_star.processTick())
    {
      star.is_active = 0;
    }*/

    //checking for the magnet is present
    if(magnet.is_active == 1)
    {

      player.speed += magnet.horizantal_acceleration; //aply const acceleration towards it
      //printf("%f spedd %f\n",player.speed , magnet.horizantal_acceleration);
    }
    else if(magnet2.is_active == 1)
    {
      player.speed += magnet2.horizantal_acceleration;
    }
    else
    {
      //player.speed = 0;
    }

  }
    //check for the star here
    //checking for the direction arrow
    if(frame_ref != 2)
    {
    if(arrow_timer1.processTick())
    {
      arrow.is_active = 1;
    }
    if(arrow_timer2.processTick())
    {
      arrow.is_active = 0;
    }
    }

}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models


    //player
    player       = Ball(1,-1.22, COLOR_RED);
    player.speed = 0;
    player.is_killed = 0;

    //direction Arrow
    arrow = Arrow(0,3.4,0.3,0.1);

    //ground 1
    ground = Ground(0,4.5,COLOR_GREEN);

    //ground 2
    ground2 = Ground(0,3.5,COLOR_SOIL);

    //init for the balls and slabs on the balls

    for(int i=0;i<number_balls;i++)
    {
        int rand_xx = rand() % number_balls;
        float x_cord = (float)i/4;
        x_cord = -x_cord - rand_xx - 6;

        int random_number = rand()%6;
        int color_rand = rand()%7;
        //printf("%d cadc %d  ",i , random_number);

        if(i%4 == 0)
        {
            balls[i] = Balls(x_cord,0,0.2,1,color_array[color_rand]);
            int random_index = rand()%(4);
            balls[i].speed = speeds_balls[random_index];
            balls[i].start_x = (float)x_cord; //starting co-ordinate of the ball
            balls[i].start_y = 0; // starting y co-ordinate of the ball
            //for the slabs
            if(random_number >=1 && random_number <=5)
            {
                if(i % random_number == 0)
                {
                    //create a slab for this slab with same velocity as the ball
                    float slide_y = balls[i].start_y + balls[i].radius;
                    float slide_x = x_cord - balls[i].radius;
                    slab[count] = Slide(slide_x,slide_y,0.5,0.1,x_cord,slide_y,COLOR_BROWN);
                    slab[count].speed = balls[i].speed;
                    slab[count].rotation = 45;
                    balls[i].index_of_slide = count;
                    balls[i].dir = 1; //left side
                    slab[count].dirc = 1;
                    count++;
                }
            }
            continue;
        }
        else if(i%4 == 1)
        {
            balls[i] = Balls(x_cord,1.5,0.24,2,color_array[color_rand]);
            int random_index = rand()%(4);
            balls[i].speed = speeds_balls[random_index];
            balls[i].start_x = (float)x_cord; //starting co-ordinate of the ball
            balls[i].start_y = 1.5;
            //for the slabs
            if(random_number >=1 && random_number <=5)
            {
                if(i % random_number == 0)
                {
                    //create a slab for this slab with same velocity as the ball
                    float slide_y = balls[i].start_y + balls[i].radius;
                    float slide_x = x_cord + balls[i].radius;
                    slab[count] = Slide(slide_x,slide_y,0.5,0.1,x_cord,slide_y,COLOR_BROWN);
                    slab[count].rotation = -45;
                    slab[count].speed = balls[i].speed;
                    balls[i].index_of_slide = count;
                    balls[i].dir = 2; //right side
                    slab[count].dirc = 2;
                    count++;
                }
            }
            continue;
        }
        else if(i%4 == 2)
        {

            balls[i] = Balls(x_cord,2,0.16,3,color_array[color_rand]);
            int random_index = rand()%(4);
            balls[i].speed = speeds_balls[random_index];
            balls[i].start_x = (float)x_cord; //starting co-ordinate of the ball
            balls[i].start_y = 2;
            //for the slabs
            if(random_number >=1 && random_number <=5)
            {
                if(i % random_number == 0)
                {
                    //create a slab for this slab with same velocity as the ball
                    float slide_y = balls[i].start_y + balls[i].radius;
                    float slide_x = x_cord - balls[i].radius;
                    slab[count] = Slide(slide_x,slide_y,0.5,0.1,x_cord,slide_y,COLOR_BROWN);
                    slab[count].rotation = 45;
                    slab[count].speed = balls[i].speed;
                    balls[i].index_of_slide = count;
                    balls[i].dir = 1; //left side
                    slab[count].dirc = 1;
                    count++;
                }
            }

            continue;
        }
        else
        {
            balls[i] = Balls(x_cord,3,0.19,4,color_array[color_rand]);
            int random_index = rand()%(4);
            balls[i].speed = speeds_balls[random_index];
            balls[i].start_x = (float)x_cord; //starting co-ordinate of the ball
            balls[i].start_y = 3;
            //for the slabs
            if(random_number >=1 && random_number <=5)
            {
                if(i % random_number == 0)
                {
                    //create a slab for this slab with same velocity as the ball
                    float slide_y = balls[i].start_y + balls[i].radius;
                    float slide_x = x_cord + balls[i].radius;
                    slab[count] = Slide(slide_x,slide_y,0.5,0.1,x_cord,slide_y,COLOR_BROWN);
                    slab[count].rotation = -45;
                    slab[count].speed = balls[i].speed;
                    balls[i].index_of_slide = count;
                    balls[i].dir = 2; //right side
                    slab[count].dirc = 2;
                    count++;
                }
            }
            continue;
        }
    }

     // for init of the spikes
    float spike_x = -2.3;
    for(int i=0;i<number_spikes;i++)
    {
        spike[i] = Spikes(spike_x,-1.25,COLOR_INT);
        spike_x -= 0.3;
    }

     //init for the trampoline
    rec1 = Rectangle(2,-1.22,0.2,0.5,COLOR_DEEPRED);
    rec2 = Rectangle(3,-1.22,0.2,0.5,COLOR_DEEPRED);
    half_circle = Semi(2.5,-0.97,0.42,COLOR_DEEPRED);

    //init for the pond
    water = Semi(-0.8,-1.5,1,COLOR_BLUE);

    //init for the Magnet
    magnet = Magnet(-3.5,3,-0.0004);
    magnet2 = Magnet(3.5,3,0.0004);
    magnet2.rotation = 180;
    //init for the exit rectangles
    rec3 = Exit(3.9,3,0.8,0.2,COLOR_DEEPRED); //
    rec3.rotation = 90;
    // init for the brick
    brick = Exit(0,1,0.8,0.8,COLOR_BROWN);
    //init for the COin
    coin = Ball(brick.start_x + 7.4*2,brick.start_y ,COLOR_BV);
    coin.is_killed = 1; // initially there will be no ball
    coin.ball_air = 0; //initially it is in air
    coin.gravity = 0.005;
    //init for the star
    star = Star(2,3,0.2);



    //initial
    /*glShadeModel (GL_FLAT);

    makeRasterFont();*/

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
    int width  = 900;
    int height = 900;
    //allowed speeds of the balls
    speeds_balls[0] = 0.01;
    speeds_balls[1] = 0.03;
    speeds_balls[2] = 0.05;
    speeds_balls[3] = 0.015;

    //allowed colors of the Balls
    color_array[0] = COLOR_BV;
    color_array[1] = COLOR_YELLOW;
    color_array[2] = COLOR_INT;
    color_array[3] = COLOR_VOILET;
    color_array[4] = COLOR_INTMAX;
    color_array[5] = COLOR_DEEPBLUE;
    color_array[6] = COLOR_GREENPALE;

    //glutInit( & argc, argv );
     //glut init
    window = initGLFW(width, height);

    initGL (window, width, height);


    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            //used for displaying the score on the title bar
            string player_score,player_level;
            stringstream Score,Levels;

            Score << player.score;
            player_score = Score.str();

            const char *score_string = "Score ";
            const char *score_value = player_score.c_str();
            const char *Level = "   Level ";
            Levels << player.level;

            player_level = Levels.str();
            const char *level_value = player_level.c_str();
            string total( string(score_string) + score_value + string(Level) + level_value);
            glfwSetWindowTitle(window, total.c_str());

            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            //glutSwapBuffers();
            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    //printf("%f %f\n",a.width , a.height);
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

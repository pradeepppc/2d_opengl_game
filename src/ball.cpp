#include "ball.h"
#include "main.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//static  GLfloat vertex_buffer_data[360*9];
Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    start_x = x;
    start_y = y;
    speed = 0;
    colour = color;
    gravity = 0.02; // initial gravity
    speedy = 0; // at start there is no speed along the y direction
    ball_air = 0; // initially ball is not in air
    ball_water = 0; // initially ball is not in water
    is_killed = 0; //initially player is not killed
    on_brick = 0; // not on the brick
    level = 1; // initial level of the player
    score = 0; // initial score of the player
    done = 0;
    static  GLfloat vertex_buffer_data[60*9];
    static  GLfloat vertex_buffer_data1[60*9];
    static  GLfloat vertex_buffer_data2[60*9];
    static  GLfloat vertex_buffer_data3[60*9];
    static  GLfloat vertex_buffer_data4[60*9];
    static  GLfloat vertex_buffer_data5[60*9];
    static  GLfloat vertex_buffer_data6[60*9];

    float pi = 3.14159,x_cord=0.2,y_cord=0.2;

    for(int i=0;i<60*9;i=i+9)
     {
         float tempx = x_cord*cos(pi/180) - y_cord*sin(pi/180);
         float tempy = x_cord*sin(pi/180) + y_cord*cos(pi/180);
         //for first vertex
         vertex_buffer_data[i] = x_cord;
         vertex_buffer_data[i+1] = y_cord;
         vertex_buffer_data[i+2] = 0.0f;
         //for second vertex
         vertex_buffer_data[i+3] = tempx;
         vertex_buffer_data[i+4] = tempy;
         vertex_buffer_data[i+5] = 0.0f;
         //for third vertex
         vertex_buffer_data[i+6] = 0.0f;
         vertex_buffer_data[i+7] = 0.0f;
         vertex_buffer_data[i+8] = 0.0f;
         x_cord =tempx;
         y_cord= tempy;
     }

     for(int i=0;i<60*9;i=i+9)
      {
          float tempx = x_cord*cos(pi/180) - y_cord*sin(pi/180);
          float tempy = x_cord*sin(pi/180) + y_cord*cos(pi/180);
          //for first vertex
          vertex_buffer_data1[i] = x_cord;
          vertex_buffer_data1[i+1] = y_cord;
          vertex_buffer_data1[i+2] = 0.0f;
          //for second vertex
          vertex_buffer_data1[i+3] = tempx;
          vertex_buffer_data1[i+4] = tempy;
          vertex_buffer_data1[i+5] = 0.0f;
          //for third vertex
          vertex_buffer_data1[i+6] = 0.0f;
          vertex_buffer_data1[i+7] = 0.0f;
          vertex_buffer_data1[i+8] = 0.0f;
          x_cord =tempx;
          y_cord= tempy;
      }

      for(int i=0;i<60*9;i=i+9)
       {
           float tempx = x_cord*cos(pi/180) - y_cord*sin(pi/180);
           float tempy = x_cord*sin(pi/180) + y_cord*cos(pi/180);
           //for first vertex
           vertex_buffer_data2[i] = x_cord;
           vertex_buffer_data2[i+1] = y_cord;
           vertex_buffer_data2[i+2] = 0.0f;
           //for second vertex
           vertex_buffer_data2[i+3] = tempx;
           vertex_buffer_data2[i+4] = tempy;
           vertex_buffer_data2[i+5] = 0.0f;
           //for third vertex
           vertex_buffer_data2[i+6] = 0.0f;
           vertex_buffer_data2[i+7] = 0.0f;
           vertex_buffer_data2[i+8] = 0.0f;
           x_cord =tempx;
           y_cord= tempy;
       }

       for(int i=0;i<60*9;i=i+9)
        {
            float tempx = x_cord*cos(pi/180) - y_cord*sin(pi/180);
            float tempy = x_cord*sin(pi/180) + y_cord*cos(pi/180);
            //for first vertex
            vertex_buffer_data3[i] = x_cord;
            vertex_buffer_data3[i+1] = y_cord;
            vertex_buffer_data3[i+2] = 0.0f;
            //for second vertex
            vertex_buffer_data3[i+3] = tempx;
            vertex_buffer_data3[i+4] = tempy;
            vertex_buffer_data3[i+5] = 0.0f;
            //for third vertex
            vertex_buffer_data3[i+6] = 0.0f;
            vertex_buffer_data3[i+7] = 0.0f;
            vertex_buffer_data3[i+8] = 0.0f;
            x_cord =tempx;
            y_cord= tempy;
        }

        for(int i=0;i<60*9;i=i+9)
         {
             float tempx = x_cord*cos(pi/180) - y_cord*sin(pi/180);
             float tempy = x_cord*sin(pi/180) + y_cord*cos(pi/180);
             //for first vertex
             vertex_buffer_data4[i] = x_cord;
             vertex_buffer_data4[i+1] = y_cord;
             vertex_buffer_data4[i+2] = 0.0f;
             //for second vertex
             vertex_buffer_data4[i+3] = tempx;
             vertex_buffer_data4[i+4] = tempy;
             vertex_buffer_data4[i+5] = 0.0f;
             //for third vertex
             vertex_buffer_data4[i+6] = 0.0f;
             vertex_buffer_data4[i+7] = 0.0f;
             vertex_buffer_data4[i+8] = 0.0f;
             x_cord =tempx;
             y_cord= tempy;
         }

         for(int i=0;i<60*9;i=i+9)
          {
              float tempx = x_cord*cos(pi/180) - y_cord*sin(pi/180);
              float tempy = x_cord*sin(pi/180) + y_cord*cos(pi/180);
              //for first vertex
              vertex_buffer_data5[i] = x_cord;
              vertex_buffer_data5[i+1] = y_cord;
              vertex_buffer_data5[i+2] = 0.0f;
              //for second vertex
              vertex_buffer_data5[i+3] = tempx;
              vertex_buffer_data5[i+4] = tempy;
              vertex_buffer_data5[i+5] = 0.0f;
              //for third vertex
              vertex_buffer_data5[i+6] = 0.0f;
              vertex_buffer_data5[i+7] = 0.0f;
              vertex_buffer_data5[i+8] = 0.0f;
              x_cord =tempx;
              y_cord= tempy;
          }


    this->object[0] = create3DObject(GL_TRIANGLES, 60*3, vertex_buffer_data, COLOR_VOILET, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 60*3, vertex_buffer_data1, COLOR_BLUE, GL_FILL);
    this->object[2] = create3DObject(GL_TRIANGLES, 60*3, vertex_buffer_data2, COLOR_GREEN, GL_FILL);
    this->object[3] = create3DObject(GL_TRIANGLES, 60*3, vertex_buffer_data3, COLOR_YELLOW, GL_FILL);
    this->object[4] = create3DObject(GL_TRIANGLES, 60*3, vertex_buffer_data4, COLOR_BROWN, GL_FILL);
    this->object[5] = create3DObject(GL_TRIANGLES, 60*3, vertex_buffer_data5, COLOR_RED, GL_FILL);


}



void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //this->object = create3DObject(GL_TRIANGLES, 360*3, vertex_buffer_data, this->colour, GL_FILL);
    for(int i=0;i<6;i++)
    {
      draw3DObject(this->object[i]);
    }

}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    //printf("%f speedy ",this->speedy);
    this->position.x += this->speed;
    this->position.y += this->speedy;


    //if the ball is in air
    if(this->ball_air == 1)
    {
    this->speedy -= this->gravity;
    }

    //checking the player for the ground or not in air
    if(this->position.y < -1.22)
    {
        //printf("%d %d \n",this->ball_air , this->ball_water);

        if(this->ball_water == 0 && this->ball_air == 1)
        {
        this->position.y = -1.22;
        }
        if(this->ball_water == 0 && this->ball_air == 1)
        {
        this->speedy = 0;
        }
        /*if(this->ball_water == 1 && this->ball_air == 1)
        {
          this->speedy = this->speedy / 15;
        }*/
        this->ball_air = 0;

        this->speed = 0;
    }
    //checking the player if he was in glPolygonMode
    if(this->ball_water == 1)
    {

      this->speedy -= 0.0007;
      float pond_y = this->position.y;
      //added
      if(pond_y >= -0.7)
      pond_y = -0.7;

      if(pond_y <= -2.25)
      pond_y = -2.22;
      //extra added
      float temp = (float)sqrt((0.8)*(0.8)-(pond_y + 1.5)*(pond_y + 1.5));
      float pond_x;
      if(this->position.x > -0.8)
      {
      pond_x = temp - 0.8;
      if(this->position.y > -2.22)
      this->rotation += 10;
      }
      else{
        pond_x = -temp - 0.8;
        if(this->position.y > -2.22)
        this->rotation -= 10;
      }

      if(pond_y < -2.25)
      {
        //this->set_position(-0.8,-2.22); //added
        //this->speedy = 0;
      }
      else if(this->speedy >= 0 || (this->position.x <= -0.4 && this->position.x >= -1.2))
      {
        //ball while going up wards

      }
      else
      {
      this->set_position(pond_x , pond_y);
          }
    }
    //if it went below pond
    //printf("%f %f position\n",this->position.x , this->position.y);
    if(this->position.y <= -2.25)
    {
      this->position.y = -2.22;
    }


    //checking the player for the boundaries
    if(this->position.x <= -3.63)
    {
      this->position.x = -3.63; //dont allow it to go towards the left side.
    }
    if(this->position.x >=18.38)
    {
      this->position.x = 18.38;
    }
    //printf("in ball.cpp %f %f\n",this->position.x ,this->position.y);


  }


bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.5, 0.5};
    return bbox;
}

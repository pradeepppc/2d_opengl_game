#include "magnet.h"
#include "main.h"
#include <stdio.h>
Magnet::Magnet(float x, float y,float acceleration) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0;
    start_x = x;
    start_y = y;
    timer = 0; // number of ticks
    is_active = 0; // initially not there on the screen
    horizantal_acceleration = acceleration; //this should be modified accordingly
    static  GLfloat vertex_buffer_data[180*9],vertex_buffer_data2[180*9]; //for two semi circles
    float pi = 3.14159,x_cord=0,y_cord=0.2; //smaller semi circle
    float x_co = 0,y_co = 0.4; // bigger semi circle

    //data for the first rectangle
    static GLfloat const vertex_buffer_data3[]={

      0.0f , y_co , 0.0f ,
      0.5f , y_co, 0.0f,
      0.0f , y_cord, 0.0f,
      0.5f , y_co, 0.0f,
      0.0f , y_cord, 0.0f,
      0.5f , y_cord,0.0f
    };
    //data for the second rectangle

    static GLfloat const vertex_buffer_data4[]={

      0.0f , -(y_co-0.0) , 0.0f ,
      0.5f , -(y_co-0.0) , 0.0f,
      0.0f , -(y_cord-0.0), 0.0f,
      0.5f , -(y_co-0.0) , 0.0f,
      0.0f , -(y_cord-0.0), 0.0f,
      0.5f , -(y_cord-0.0),0.0f
    };

    //for smaller semi circle
    for(int i=0;i<180*9;i=i+9)
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
     //data for bigger semi circles

     for(int i=0;i<180*9;i=i+9)
      {
          float tempx = x_co*cos(pi/180) - y_co*sin(pi/180);
          float tempy = x_co*sin(pi/180) + y_co*cos(pi/180);
          //for first vertex
          vertex_buffer_data2[i] = x_co;
          vertex_buffer_data2[i+1] = y_co;
          vertex_buffer_data2[i+2] = 0.0f;
          //for second vertex
          vertex_buffer_data2[i+3] = tempx;
          vertex_buffer_data2[i+4] = tempy;
          vertex_buffer_data2[i+5] = 0.0f;
          //for third vertex
          vertex_buffer_data2[i+6] = 0.0f;
          vertex_buffer_data2[i+7] = 0.0f;
          vertex_buffer_data2[i+8] = 0.0f;
          x_co = tempx;
          y_co = tempy;
      }




    this->object = create3DObject(GL_TRIANGLES, 180*3, vertex_buffer_data, COLOR_BACKGROUND, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES ,180*3 , vertex_buffer_data2,COLOR_DEEPRED,GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES , 6 , vertex_buffer_data3,COLOR_DEEPRED,GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES , 6 , vertex_buffer_data4,COLOR_DEEPRED,GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object2);
    draw3DObject(this->object);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Magnet::tick() {


}

bounding_box_t Magnet::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.45, 0.45};
    return bbox;
}

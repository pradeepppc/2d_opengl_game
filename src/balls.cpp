#include "balls.h"
#include "main.h"
#include <stdio.h>
Balls::Balls(float x, float y,float r,int sco,color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.02;
    start_x = 0.0;
    start_y = 0.0;
    score = sco;
    dir = 0; //if no slide
    index_of_slide = -1; // -1 if the ball doesnt have a index
    is_alive = 1; // 1 if not destroyed
    radius = r; // radius of the ball
    static  GLfloat vertex_buffer_data[360*9];
    float pi = 3.14159,x_cord=r,y_cord=r;

    for(int i=0;i<360*9;i=i+9)
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



    this->object = create3DObject(GL_TRIANGLES, 360*3, vertex_buffer_data, color, GL_FILL);
}

void Balls::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Balls::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Balls::tick() {
    //the speed of the balls
    this->position.x += this->speed;

    //get back to the starting point if they move out of boundary
    if(this->position.x >= 20)
    {
        this->position.x = this->start_x;
        //printf("%f kkkk ",this->start_x);
    }

}

bounding_box_t Balls::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float r = this->radius;
    bounding_box_t bbox = { x, y, 2*r , 2*r };
    return bbox;
}

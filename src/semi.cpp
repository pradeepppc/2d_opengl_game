#include "semi.h"
#include "main.h"
#include <stdio.h>
Semi::Semi(float x, float y,float r,color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    gravity = 0.02; // initial gravity
    radius = r;
    start_x = x;
    start_y = y;
    static  GLfloat vertex_buffer_data[180*9];
    float pi = 3.14159,x_cord=-r,y_cord=0;

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



    this->object = create3DObject(GL_TRIANGLES, 180*3, vertex_buffer_data, color, GL_FILL);
}

void Semi::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Semi::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Semi::tick() {


}

bounding_box_t Semi::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 2*this->radius - 0.3, this->radius-0.2};
    return bbox;
}

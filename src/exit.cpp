#include "exit.h"
#include "main.h"
#include <stdio.h>
static GLfloat vertex_buffer_data[18];
Exit::Exit(float x, float y,float l,float b,color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0;
    start_x = x;
    start_y = y;
    this->length = l;
    colour = color;
    this->breadth = b;
     // number of ticks
    is_active = 1; // initially not there on the screen
    //data for the first rectangle

    float ll = l/2,bb = b/2;
    vertex_buffer_data[0]= -ll;
    vertex_buffer_data[1] = bb;
    vertex_buffer_data[2] = 0.0f ;vertex_buffer_data[3] = ll;vertex_buffer_data[4] = bb;vertex_buffer_data[5] = 0.0f;
    vertex_buffer_data[6]=-ll ;vertex_buffer_data[7] = -bb;vertex_buffer_data[8] = 0.0f;vertex_buffer_data[9] = ll;
    vertex_buffer_data[10] = bb;
    vertex_buffer_data[11] = 0.0f; vertex_buffer_data[12] = -ll; vertex_buffer_data[13] = -bb; vertex_buffer_data[14] = 0.0f;
     vertex_buffer_data[15] = ll;
    vertex_buffer_data[16]  = -bb; vertex_buffer_data[17] = 0.0f;




    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Exit::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, this->colour, GL_FILL);
    draw3DObject(this->object);
    }

void Exit::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Exit::tick() {


}

bounding_box_t Exit::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, this->breadth, this->length};
    return bbox;
}

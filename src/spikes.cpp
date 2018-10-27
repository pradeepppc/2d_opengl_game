#include "spikes.h"
#include "main.h"
#include <stdio.h>
Spikes::Spikes(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    is_active = 1; // initially it is active
    start_x = x;
    start_y = y;
    static  GLfloat const vertex_buffer_data[]={


        //vertices should be here
        0.0f , 0.25f , 0.0f,
        -0.15f , -0.25f , 0.0f,
        0.15f , -0.25f, 0.0f

    };

    this->object = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, color, GL_FILL);
}

void Spikes::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Spikes::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Spikes::tick() {
    //write code if required

}

bounding_box_t Spikes::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.2, 0.4 };
    return bbox;
}

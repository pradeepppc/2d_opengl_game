#include "slide.h"
#include "main.h"
#include <stdio.h>
Slide::Slide(float x, float y,float wid,float len,float stx,float sty,color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0; // initially speed will be zero
    widt = wid; // width and length of the rectangle
    lengt = len;
    dirc = 0; //no incline
    start_x = stx; // starting co -ordinate of the slide
    start_y = sty;  // starting y co - ordinate of the slide
    float x1 = -widt/2,x2 = widt/2;
    float y1 = -lengt/2,y2 = lengt/2;

    static  GLfloat  const vertex_buffer_data[]{

            //1st triangle
            x1, y2, 0.0f,
            x2 , y2 , 0.0f,
            x1 , y1 ,0.0f,

            //2nd triangle
                    x2 , y2 , 0.0f,
                    x1 , y1 ,0.0f,
                    x2 , y1 , 0.0f


        };



    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Slide::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Slide::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Slide::tick() {
    this->position.x += this->speed; //rectangle attached to the ball has to move

    if(this->position.x >= 20)
    {
        this->position.x = this->start_x;
        //printf("%f kkkk ",this->start_x);
    }
}

bounding_box_t Slide::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y,this->widt,this->lengt};
    return bbox;
}

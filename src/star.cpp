#include "star.h"
#include "main.h"
#include <stdio.h>
Star::Star(float x, float y,float len) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0; // initially speed will be zero
    length = len;
    is_active = 0; // initially active
    start_x = x;
    start_y = y;
    float x_len = len/2;
    float y_len = len + len/2;

    static  GLfloat const vertex_buffer_data[]{

            //1st triangle
            -x_len, x_len, 0.0f,
            x_len , x_len , 0.0f,
            -x_len , -x_len ,0.0f,

            //2nd triangle
            x_len , x_len , 0.0f,
            -x_len , -x_len ,0.0f,
            x_len , -x_len , 0.0f,


        };
        static  GLfloat const vertex_buffer_data1[]{

          0.0f,-y_len , 0.0f,
          -x_len,-x_len,0.0f,
          x_len , -x_len , 0.0f

        };
        static  GLfloat const vertex_buffer_data2[]{
          -x_len , x_len , 0.0f,
          -x_len , -x_len , 0.0f,
          -y_len , 0.0f , 0.0f
        };
        static  GLfloat const vertex_buffer_data3[]{
          -x_len , x_len , 0.0f,
          x_len , x_len , 0.0f,
          0.0f , y_len , 0.0f
        };
        static  GLfloat const vertex_buffer_data4[]{

          x_len , x_len , 0.0f,
          x_len , -x_len , 0.0f,
          y_len , 0.0f, 0.0f
        };


    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_DEEPRED, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data1, COLOR_DEEPBLUE, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data2, COLOR_DEEPBLUE, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data3, COLOR_DEEPBLUE, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data4, COLOR_DEEPBLUE, GL_FILL);

}

void Star::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
}

void Star::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Star::tick() {
    this->position.x += this->speed; //rectangle attached to the ball has to move

}

bounding_box_t Star::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y,((float)3/2)*this->length,((float)3/2)*this->length};
    return bbox;
}

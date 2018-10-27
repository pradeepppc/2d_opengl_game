#include "arrow.h"
#include "main.h"
#include <stdio.h>
Arrow::Arrow(float x, float y, float l,float b) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    length = l;
    breadth = b;
    start_x = x;
    start_y = y;
    is_active = 1; //active initially
    float dx = 0.1;

    static GLfloat const vertex_buffer_data[]={

        -l/2 , b/2 , 0.0f,
        l/2 , b/2 , 0.0f ,
        -l/2 , -b/2 , 0.0f,

        l/2 , b/2 , 0.0f ,
        -l/2 , -b/2 , 0.0f,
        l/2 , -b/2 , 0.0f

      };

      static GLfloat const vertex_buffer_data1[]={
          l/2 , b/2 + dx ,0.0f,
          l/2 , -b/2 - dx , 0.0f,
          l , 0.0f , 0.0f
      };


      this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_DEEPBLUE, GL_FILL);
      this->object1 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data1, COLOR_DEEPBLUE, GL_FILL);


}

void Arrow::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
}

void Arrow::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
  }


    void Arrow::tick(){

}


bounding_box_t Arrow::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}

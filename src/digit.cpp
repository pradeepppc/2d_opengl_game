#include "digit.h"

Digit::Digit(float x, float y,int num) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->number=num;
    this->start_x = x;
    this->start_y = y;
    color_t color;
    static const GLfloat vertex_buffer_data1[] = {
        -0.2, 0, 0, // vertex 1
        0.2,  0, 0, // vertex 2
    };
    static const GLfloat vertex_buffer_data2[] = {
        0.2,  0, 0,
        0.2,-0.2,0,
    };
    static const GLfloat vertex_buffer_data3[] = {
        0.2,-0.2,0,
        -0.2,-0.2,0,
    };
    static const GLfloat vertex_buffer_data4[] = {
        -0.2,-0.2,0,
        -0.2, 0, 0,
    };
    static const GLfloat vertex_buffer_data5[] = {
        0.2,  0, 0,
        0.2,0.2,0,
    };
    static const GLfloat vertex_buffer_data6[] = {
        0.2,0.2,0,
        -0.2,0.2,0,
    };
    static const GLfloat vertex_buffer_data7[] = {
        -0.2,0.2,0,
        -0.2, 0, 0,
    };


    if(this->number==9 || this->number==8 || this->number==6 || this->number==5 || this->number==4 || this->number==0)
    {
    color=COLOR_BLACK;
    }
    else
    {
    color=COLOR_BACKGROUND;
    }
    this->object[0] = create3DObject(GL_LINES, 2, vertex_buffer_data7, color, GL_FILL);


    if(this->number==8 ||  this->number==6 || this->number==5 || this->number==3 || this->number==2 || this->number==0)
    {
    color=COLOR_BLACK;
    }
    else
    {
    color=COLOR_BACKGROUND;
    }
    this->object[1] = create3DObject(GL_LINES, 2, vertex_buffer_data3, color, GL_FILL);


    if(this->number!=2)
      {
        color=COLOR_BLACK;
      }
    else
      {
        color=COLOR_BACKGROUND;
      }
    this->object[2] = create3DObject(GL_LINES, 2, vertex_buffer_data2, color, GL_FILL);




    if(this->number==8 || this->number==6 || this->number==2 || this->number==0)
    {
        color=COLOR_BLACK;
      }
    else
    {
        color=COLOR_BACKGROUND;
      }
    this->object[3] = create3DObject(GL_LINES, 2, vertex_buffer_data4, color, GL_FILL);




    if(this->number!=5 && this->number!=6)
    {
        color=COLOR_BLACK;
      }
    else
    {
        color=COLOR_BACKGROUND;
      }
    this->object[4] = create3DObject(GL_LINES, 2, vertex_buffer_data5, color, GL_FILL);





    if(this->number!=1 && this->number!=4)
    {
        color=COLOR_BLACK;
      }
      else
      {
        color=COLOR_BACKGROUND;
      }
    this->object[5] = create3DObject(GL_LINES, 2, vertex_buffer_data6, color, GL_FILL);




    if(this->number!=7 && this->number!=1 && this->number!=0)
    {
      color=COLOR_BLACK;
    }
    else
    {
      color=COLOR_BACKGROUND;
    }
    this->object[6] = create3DObject(GL_LINES, 2, vertex_buffer_data1, color, GL_FILL);

}

void Digit::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    for(int i=0;i<7;i++)
        draw3DObject(this->object[i]);
}


void Digit::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Digit::tick() {



}

bounding_box_t Digit::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}

#include "main.h"

#ifndef ARROW_H
#define ARROW_H


class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y,float l,float b);
    glm::vec3 position;
    float rotation;
    float length;
    float breadth;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float start_x; //starting position of the ball
    float start_y;
    int is_active; 
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *object1;
};

#endif // BALL_H

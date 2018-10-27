#include "main.h"

#ifndef BRICK_H
#define BRICK_H


class Brick {
public:
    Brick() {}
    Brick(float x, float y,float l,float b,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    float start_x;
    float start_y;
    float length;
    float breadth;
    void set_position(float x, float y);
    void tick();
    double speed;
    color_t colour;
    int is_active; // to know wether it is on the screen or not
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H

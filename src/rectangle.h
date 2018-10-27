#include "main.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H


class Rectangle {
public:
    Rectangle() {}
    Rectangle(float x, float y,float wid,float len ,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    float start_x;
    float start_y;
    float widt; // width of the rectangle
    float lengt; // length of the rectangle
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H

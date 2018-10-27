#include "main.h"

#ifndef SLIDE_H
#define SLIDE_H


class Slide {
public:
    Slide() {}
    Slide(float x, float y,float wid,float len ,float stx,float sty ,color_t color);
    glm::vec3 position;
    float rotation;
    float start_x; // for storing the starting x co-ordinate
    float start_y; //for storing the starting y co-ordinate
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed; //speed of the slide
    float widt; // width of the rectangle
    float lengt; // length of the rectangle
    int dirc; // direction of incline
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H

#include "main.h"

#ifndef DIGIT_H
#define DIGIT_H


class Digit {
public:
    Digit() {}
    float rotation;
    Digit(float x, float y,int no);
    glm::vec3 position;
    float start_x;
    float start_y;
    int number;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
private:
    VAO *object[7];
};

#endif // Digit_H

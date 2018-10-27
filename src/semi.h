#include "main.h"

#ifndef SEMI_H
#define SEMI_H


class Semi {
public:
    Semi() {}
    Semi(float x, float y,float r, color_t color);
    glm::vec3 position;
    double gravity; // used as deaceleration
    void draw(glm::mat4 VP);
    float rotation;
    void set_position(float x, float y);
    void tick();
    float radius;
    float start_x;
    float start_y;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H

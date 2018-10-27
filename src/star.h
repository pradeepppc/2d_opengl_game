#include "main.h"

#ifndef STAR_H
#define STAR_H


class Star {
public:
    Star() {}
    Star(float x, float y,float len);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    int timer; // time after which it should appear
    int is_active; // to know wether it is on the screen or not
    float length;
    float start_x;
    float start_y;
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
};

#endif // BALL_H

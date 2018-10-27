#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H


class Magnet {
public:
    Magnet() {}
    Magnet(float x, float y,float accelaration);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    float start_x;
    float start_y;
    double speed;
    int timer; // time after which it should appear
    float horizantal_acceleration;
    int is_active; // to know wether it is on the screen or not
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *object2;
    VAO *object3;
    VAO *object4;
};

#endif // BALL_H

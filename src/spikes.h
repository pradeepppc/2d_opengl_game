#include "main.h"

#ifndef SPIKES_H
#define SPIKES_H


class Spikes {
public:
    Spikes() {}
    Spikes(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float rotation;
    float start_x;
    float start_y;
    bounding_box_t bounding_box();
    int is_active; // to know wether it should be there or not
private:
    VAO *object;
};

#endif // BALL_H

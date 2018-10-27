#include "main.h"


#ifndef GROUND_H
#define GROUND_H


class Ground {
public:
    Ground() {}
        Ground(float x, float y, color_t color);
        glm::vec3 position;
        float rotation;
        float start_x;
        float start_y;
        void draw(glm::mat4 VP);
        void set_position(float x, float y);
        void tick();
        bounding_box_t bounding_box();
    private:
        VAO *object;
    };

#endif

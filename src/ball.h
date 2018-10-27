#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    double gravity; // used as deaceleration
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    color_t colour;
    float start_x; //starting position of the ball
    float start_y;
    int ball_air;
    int ball_water; // to know if the ball is in pond or not
    int is_killed; // to know if it is alive or not
    double speedy; // speed along the y direction
    bounding_box_t bounding_box();
    int score; //score of the player
    int level; // level of the player
    int on_brick; //
    int done; //
private:
    VAO *object[6];
};

#endif // BALL_H

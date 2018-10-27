#include "main.h"

#ifndef BALLS_H
#define BALLS_H


class Balls {
public:
  glm::vec3 position;
    Balls() {}
    Balls(float x, float y, float r,int sco,color_t color);
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    int is_alive;
    float radius; //radius of the ball
    float start_x; //starting x co-ordinate of the ball
    float start_y; //starting y co-ordinate of the ball
    int score; // score attained by killing this particular ball
    int index_of_slide; //index of the slide it got attached
    int dir; //for storing the side the slab was placed
    
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H

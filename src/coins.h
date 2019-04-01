#include "main.h"

#ifndef COIN_H
#define COIN_H


class Coin {
public:
    Coin() {}
    Coin(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void change_speed();
    double speed_x,speed_y,speed_z,acc_y;
    bounding_box_t bounding_box();
private:
    VAO *object[2];
};

#endif // BALL_H

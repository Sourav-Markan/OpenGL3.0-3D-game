#include "main.h"

#ifndef GOLI_H
#define GOLI_H


class Goli {
public:
    Goli() {}
    Goli(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    double speed_y,acc_y,speed_x,speed_z;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void change_speed();
    double speed;
    bounding_box_t bounding_box();
private:
    VAO *object[2];
};

#endif // BALL_H

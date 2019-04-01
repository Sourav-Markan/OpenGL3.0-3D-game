#include "main.h"

#ifndef FLAG_H
#define FLAG_H


class Flag {
public:
    Flag() {}
    Flag(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void change_speed();
    double speed_x,speed_y,speed_z,acc_y;
    bounding_box_t bounding_box();
private:
    VAO *object[6];
};

#endif // BAFLAG
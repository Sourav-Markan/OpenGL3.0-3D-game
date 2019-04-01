#include "main.h"

#ifndef MAN_H
#define MAN_H


class Man{
public:
    Man() {}
    Man(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object[3];
};

#endif // BALL_H

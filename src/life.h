#include "main.h"

#ifndef LIFE_H
#define LIFE_H


class Life {
public:
    Life() {}
    Life(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object[2];
};

#endif // BALL_H

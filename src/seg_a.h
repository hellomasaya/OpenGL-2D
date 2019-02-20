#include "main.h"

#ifndef A0_H
#define A0_H

class A0 {
public:
    A0() {}
    A0(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    bounding_box_t bounding_box();

private:
    VAO *object;
};

#endif // A0_H

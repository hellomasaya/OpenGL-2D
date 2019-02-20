#include "main.h"

#ifndef FIRELINE_H
#define FIRELINE_H

class Fireline {
public:
    Fireline() {}
    Fireline(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    bounding_box_t bounding_box();

private:
    VAO *object;
    VAO *fire1;
    VAO *fire2;
};

#endif // FIRELINE_H

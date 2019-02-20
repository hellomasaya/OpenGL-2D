#include "main.h"

#ifndef ARROW_H
#define ARROW_H

class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double xspeed;
    double yspeed;
    bounding_box_t bounding_box();

private:
    VAO *arrow1;
    VAO *arrow2;
    VAO *arrow3;
};

#endif // ARROW_H

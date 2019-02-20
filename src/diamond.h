#include "main.h"

#ifndef DIAMOND_H
#define DIAMOND_H

class Diamond {
public:
    Diamond() {}
    Diamond(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double xspeed;
    double yspeed;
    bounding_box_t bounding_box();

private:
    VAO *triangle1;
    VAO *triangle2;
    VAO *triangle3;
};

#endif // DIAMOND_H

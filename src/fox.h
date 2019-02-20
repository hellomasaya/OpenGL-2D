#include "main.h"

#ifndef FOX_H
#define FOX_H

class Fox {
public:
    Fox() {}
    Fox(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double xspeed;
    double yspeed;
    bounding_box_t bounding_box();

private:
    VAO *eyes;
    VAO *nose;
    VAO *jaw;
    VAO *middle;
    VAO *side;
};

#endif // FOX_H

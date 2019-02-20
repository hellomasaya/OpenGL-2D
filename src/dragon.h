#include "main.h"

#ifndef DRAGON_H
#define DRAGON_H

class Dragon {
public:
    Dragon() {}
    Dragon(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double xspeed;
    double yspeed;
    bounding_box_t bounding_box();

    private:
    // VAO *object;
    VAO *blush;
    VAO *eyes;
    VAO *body1;
    VAO *body2;
};

#endif // DRAGON_H

#include "main.h"

#ifndef PLAYERBODY_H
#define PLAYERBODY_H

class Playerbody {
public:
    Playerbody() {}
    Playerbody(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double xspeed;
    double yspeed;
    // bounding_box_t bounding_box();

    private:
    VAO *object;
};

#endif // PLAYERBODY_H

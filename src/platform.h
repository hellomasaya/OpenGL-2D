#include "main.h"

#ifndef PLATFORM_H
#define PLATFORM_H

class Platform {
public:
    Platform() {}
    Platform(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    bounding_box_t bounding_box();

private:
    VAO *object;
    // VAO *brick;
};

#endif // PLATFORM_H

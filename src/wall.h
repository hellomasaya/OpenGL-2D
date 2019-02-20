#include "main.h"

#ifndef WALL_H
#define WALL_H


class Wall {
public:
    Wall() {}
    Wall(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
    double speed;
private:
    VAO *object;
};

#endif // WALL_H

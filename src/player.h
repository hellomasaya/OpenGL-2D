#include "main.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    Player() {}
    Player(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double xspeed;
    double yspeed;
    double gravity;
    bounding_box_t bounding_box();

    private:
    // VAO *object;
    VAO *face;
    VAO *hair;
    VAO *jetpack;
    VAO *body;
};

#endif // PLAYER_H

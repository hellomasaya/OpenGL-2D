#include "main.h"

#ifndef FIREBEAM_H
#define FIREBEAM_H

class Firebeam {
public:
    Firebeam() {}
    Firebeam(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double xspeed;
    double yspeed;
    bounding_box_t bounding_box();
    
private:
    VAO *object;
    VAO *glow1;
    VAO *glow2;
};

#endif // FIREBEAM_H

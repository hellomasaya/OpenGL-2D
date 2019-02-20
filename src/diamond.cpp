#include "diamond.h"
#include "main.h"

Diamond::Diamond(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    xspeed = 0.0;
    yspeed = 0.0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices  
    static const GLfloat vertex_buffer_data_1[] = {
        -0.02f, 0.2f, 0.0f,
        0.03f, 0.2f, 0.0f,
        0.1f, 0.45f, 0.0f,

        0.17f, 0.2f, 0.0f,
        0.22f, 0.2f, 0.0f,
        0.1f, 0.45f, 0.0f,

        0.03f, 0.2f, 0.0f, 
        0.17f, 0.2f, 0.0f,
        0.1f, -0.05f, 0.0f,
        };

    this->triangle1 = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data_1, COLOR_PINK, GL_FILL);

    static const GLfloat vertex_buffer_data_2[] = {
        -0.02f, 0.2f, 0.0f,
        0.03f, 0.2f, 0.0f,
        0.1f, -0.05f, 0.0f,

        0.17f, 0.2f, 0.0f, 
        0.22f, 0.2f, 0.0f,
        0.1f, -0.05f, 0.0f,
        };

    this->triangle2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_2, COLOR_PINK_DARK, GL_FILL);

    static const GLfloat vertex_buffer_data_box2[] = {    
        0.03f, 0.2f, 0.0f,
        0.1f, 0.45f, 0.0f,
        0.17f, 0.2f, 0.0f,           
        };

    this->triangle3 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data_box2, COLOR_PINK_LIGHT, GL_FILL);

}

void Diamond::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    rotate = rotate * glm::translate(glm::vec3(0, -0.001, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->triangle1);
    draw3DObject(this->triangle2);
    draw3DObject(this->triangle3);
}

void Diamond::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Diamond::tick() {
    // this->rotation += speed;
    this->position.x += xspeed;
    this->position.y += yspeed;
}

bounding_box_t Diamond::bounding_box() {
    float x = this->position.x, y = this->position.y;
    double h = 0.5*2*sin(this->rotation);
    double w = abs(0.24*2*cos(this->rotation));
    bounding_box_t bbox = { x, y, w, h };
    return bbox;
}
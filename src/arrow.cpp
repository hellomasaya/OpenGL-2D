#include "arrow.h"
#include "main.h"

Arrow::Arrow(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    xspeed = 0.0;
    yspeed = 0.0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices  
    static const GLfloat vertex_buffer_data_1[] = {
        -0.02f, 0.2f, 0.0f,
        0.17f, 0.3f, 0.0f,
        0.17f, 0.4f, 0.0f,

        0.17f, 0.3f, 0.0f, 
        0.17f, 0.2f, 0.0f,
        0.4f, 0.3f, 0.0f,

        0.17f, 0.2f, 0.0f, 
        0.4f, 0.2f, 0.0f,
        0.4f, 0.3f, 0.0f,
        };

    this->arrow1 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data_1, COLOR_GREEN, GL_FILL);

    static const GLfloat vertex_buffer_data_2[] = {
        0.17f, 0.1f, 0.0f, 
        0.17f, 0.2f, 0.0f,
        0.4f, 0.1f, 0.0f,

        0.17f, 0.2f, 0.0f, 
        0.4f, 0.2f, 0.0f,
        0.4f, 0.1f, 0.0f,

        0.17f, 0.0f, 0.0f,
        0.17f, 0.1f, 0.0f,
        -0.02f, 0.2f, 0.0f,
        };

    this->arrow2 = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data_2, COLOR_DARK_GREEN, GL_FILL);

    static const GLfloat vertex_buffer_data_box2[] = {    
        -0.02f, 0.2f, 0.0f,
        0.17f, 0.3f, 0.0f,
        0.17f, 0.1f, 0.0f,           
        };

    this->arrow3 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data_box2, COLOR_LIGHT_GREEN, GL_FILL);

}

void Arrow::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    rotate = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->arrow1);
    draw3DObject(this->arrow2);
    draw3DObject(this->arrow3);
}

void Arrow::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Arrow::tick() {
    // this->rotation += speed;
    this->position.x += xspeed;
    this->position.y += yspeed;
}

bounding_box_t Arrow::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.42, 0.4 };
    return bbox;
}
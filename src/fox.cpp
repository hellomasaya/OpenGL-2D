#include "fox.h"
#include "main.h"

Fox::Fox(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    xspeed = 0.0;
    yspeed = 0.0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices  
    static const GLfloat vertex_buffer_data_1[] = {
        0.4f, 0.5f, 0.0f,
        0.6f, 0.5f, 0.0f,
        0.6f, 0.4f, 0.0f,

        0.8f, 0.5f, 0.0f, 
        1.0f, 0.5f, 0.0f,
        0.8f, 0.4f, 0.0f,
        };

    this->eyes = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_1, COLOR_WHITE, GL_FILL);

    static const GLfloat vertex_buffer_data_2[] = {
        0.3f, 0.5f, 0.0f,
        0.65f, 0.5f, 0.0f,
        0.5f, 0.7f, 0.0f,

        0.75f, 0.5f, 0.0f, 
        1.1f, 0.5f, 0.0f,
        0.9f, 0.7f, 0.0f,
        };

    this->side = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_2, COLOR_YELLOW_ORANGE, GL_FILL);

    static const GLfloat vertex_buffer_data_box2[] = {    
        0.61f, 0.1f, 0.0f,
        0.70f, 0.0f, 0.0f,
        0.79f, 0.1f, 0.0f,           
        };

    this->nose = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data_box2, COLOR_HAIR, GL_FILL);

    static const GLfloat vertex_buffer_data_box3[] = {

        //jaws
        0.3f, 0.5f, 0.0f,
        0.7f, 0.0f, 0.0f,
        0.65f, 0.5f, 0.0f,

        0.75f, 0.5f, 0.0f,
        0.7f, 0.0f, 0.0f,
        1.1f, 0.5f, 0.0f,

        //ears
        0.5, 0.7f, 0.0f,
        0.25f, 0.85f, 0.0f,
        0.3f, 0.5f, 0.0f,

        0.9f, 0.7f, 0.0f,
        1.15f, 0.85f, 0.0f,
        1.1f, 0.5f, 0.0f,

        };

    this->jaw = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data_box3, COLOR_DARK_ORANGE, GL_FILL);

    static const GLfloat vertex_buffer_data_box4[] = {    
        0.9f, 0.7f, 0.0f,
        0.7f, 0.0f, 0.0f,
        0.5f, 0.7f, 0.0f,           
        };

    this->middle = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data_box4, COLOR_LIGHT_ORANGE, GL_FILL);

}

void Fox::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    rotate = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->jaw);
    draw3DObject(this->side);
    draw3DObject(this->eyes);
    draw3DObject(this->middle);
    draw3DObject(this->nose);
}

void Fox::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Fox::tick() {
    // this->rotation += speed;
    this->position.x += xspeed;
    this->position.y += yspeed;
}

bounding_box_t Fox::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.9, 0.85 };
    return bbox;
}
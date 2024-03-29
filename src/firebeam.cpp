#include "firebeam.h"
#include "main.h"

Firebeam::Firebeam(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    xspeed = 0;
    yspeed = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -0.5f, 0.3f, 0.0f, // triangle 1 : begin
        0.5f, 0.3f, 0.0f,
        -0.5f, 0.2f, 0.0f, // triangle 1 : end
        0.5f, 0.3f, 0.0f, // triangle 2 : begin
        -0.5f, 0.2f, 0.0f,
        0.5f, 0.2f, 0.0f, // triangle 2 : end
        //rect1 end
        -0.5f, -0.2f, 0.0f, // triangle 1 : begin
        0.5f, -0.2f, 0.0f,
        -0.5f, -0.3f, 0.0f, // triangle 1 : end
        0.5f, -0.2f, 0.0f, // triangle 2 : begin
        -0.5f, -0.3f, 0.0f,
        0.5f, -0.3f, 0.0f
        //rect2 end
    };

    this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, COLOR_FIRE2, GL_FILL);

    static const GLfloat vertex_buffer_data_glow1[] = {
        -0.5f, -0.2f, 0.0f,
        -0.3f, -0.2f, 0.0f,
        -0.4f, 0.0f, 0.0f, //1
        -0.1f, -0.2f, 0.0f,
        0.1f, -0.2f, 0.0f,
        0.0f, 0.0f, 0.0f, //2
        0.5f, -0.2f, 0.0f,
        0.3f, -0.2f, 0.0f,
        0.4f, 0.0f, 0.0f, //3
        -0.1f, 0.2f, 0.0f,
        -0.3f, 0.2f, 0.0f,
        -0.2f, 0.0f, 0.0f,//4
        0.1f, 0.2f, 0.0f,
        0.2f, 0.0f, 0.0f,
        0.3f, 0.2f, 0.0f,//5
    };

    this->glow1 = create3DObject(GL_TRIANGLES, 5*3, vertex_buffer_data_glow1, COLOR_FIRE4, GL_FILL);

    static const GLfloat vertex_buffer_data_glow2[] = {
        -0.5f, -0.2f, 0.0f,
        -0.3f, -0.2f, 0.0f,
        -0.4f, -0.1f, 0.0f, //1
        -0.1f, -0.2f, 0.0f,
        0.1f, -0.2f, 0.0f,
        0.0f, -0.1f, 0.0f, //2
        0.5f, -0.2f, 0.0f,
        0.3f, -0.2f, 0.0f,
        0.4f, -0.1f, 0.0f, //3
        -0.1f, 0.2f, 0.0f,
        -0.3f, 0.2f, 0.0f,
        -0.2f, 0.1f, 0.0f,//4
        0.1f, 0.2f, 0.0f,
        0.2f, 0.1f, 0.0f,
        0.3f, 0.2f, 0.0f,//5
    };

    this->glow2 = create3DObject(GL_TRIANGLES, 5*3, vertex_buffer_data_glow2, COLOR_FIRE1, GL_FILL);
}

void Firebeam::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    rotate = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // Matrices.model *= (translate);
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->glow1);
    draw3DObject(this->glow2);
}

void Firebeam::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Firebeam::tick() {
    // this->rotation += speed;
    this->position.x -= xspeed;
    this->position.y += yspeed;
}

bounding_box_t Firebeam::bounding_box() {
    float x = this->position.x, y = this->position.y; 
    bounding_box_t bbox = { x, y, 1.0, 0.6 };
    return bbox;
}
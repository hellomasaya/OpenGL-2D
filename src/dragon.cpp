#include "dragon.h"
#include "main.h"

Dragon::Dragon(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    xspeed = 0;
    yspeed = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data_body1[] = {
        0.0f, 0.1f, 0.0f, // triangle 1 : begin
        1.0f, 0.1f, 0.0f,
        0.5f, 1.0f, 0.0f,// triangle 1 : end      
    };

    this->body1 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data_body1, COLOR_DRAGON1, GL_FILL);

    static const GLfloat vertex_buffer_data_eyes[] = {
        //eye1
        0.35f, 0.575f, 0.0f, // triangle 1 : begin
        0.35f, 0.525f, 0.0f,
        0.45f, 0.575f, 0.0f,// triangle 1 : end
        0.35f, 0.525f, 0.0f,
        0.45f, 0.525f, 0.0f,
        0.45f, 0.575f, 0.0f,
        //eye2
        0.55f, 0.575f, 0.0f, // triangle 1 : begin
        0.55f, 0.525f, 0.0f,
        0.65f, 0.575f, 0.0f,// triangle 1 : end
        0.55f, 0.525f, 0.0f,
        0.65f, 0.525f, 0.0f,
        0.65f, 0.575f, 0.0f,
        //mouth
        0.45f, 0.390f, 0.0f, // triangle 1 : begin
        0.45f, 0.300f, 0.0f,
        0.55f, 0.390f, 0.0f,// triangle 1 : end
        0.45f, 0.300f, 0.0f,
        0.55f, 0.300f, 0.0f,
        0.55f, 0.395f, 0.0f,
    };

    this->eyes = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data_eyes, COLOR_HAIR, GL_FILL);

    static const GLfloat vertex_buffer_data_body2[] = {
        0.5f, -0.1f, 0.0f, // triangle 1 : begin
        0.0f, 0.8f, 0.0f,
        1.0f, 0.8f, 0.0f,// triangle 1 : end
        
    };

    this->body2 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data_body2, COLOR_DRAGON2, GL_FILL);

    static const GLfloat vertex_buffer_data_blush[] = {
        //left cheek
        0.35f, 0.395f, 0.0f, // triangle 1 : begin
        0.35f, 0.315f, 0.0f,
        0.45f, 0.395f, 0.0f,// triangle 1 : end
        0.35f, 0.315f, 0.0f,
        0.45f, 0.315f, 0.0f,
        0.45f, 0.395f, 0.0f,
        //right
        0.55f, 0.395f, 0.0f, // triangle 1 : begin
        0.55f, 0.315f, 0.0f,
        0.65f, 0.395f, 0.0f,// triangle 1 : end
        0.55f, 0.315f, 0.0f,
        0.65f, 0.315f, 0.0f,
        0.65f, 0.395f, 0.0f,
    };
    this->blush = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data_blush, COLOR_BLUSH, GL_FILL);
}

void Dragon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    rotate = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // Matrices.model *= (translate);
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->body2);
    draw3DObject(this->body1);
    draw3DObject(this->blush);
    draw3DObject(this->eyes);
}

void Dragon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Dragon::tick() {
    // this->rotation += speed;
    this->position.x += xspeed;
    this->position.y += yspeed;
}

bounding_box_t Dragon::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.65, 0.9 };
    return bbox;
}
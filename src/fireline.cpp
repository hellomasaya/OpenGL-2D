#include "fireline.h"
#include "main.h"

Fireline::Fireline(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices  
    static const GLfloat vertex_buffer_data_box[] = {    
        -0.15f, 0.3f, 0.0f, // triangle 1 : begin
        0.0f, 0.3f, 0.0f,
        -0.15f, 0.1f, 0.0f,// triangle 1 : end
        0.0f, 0.3f, 0.0f,
        -0.15f, 0.1f, 0.0f, 
        0.0f, 0.1f, 0.0f,
        //block1
        0.375f, 0.3f, 0.0f, // triangle 3 : begin
        0.525f, 0.3f, 0.0f,
        0.375f, 0.1f, 0.0f,// triangle 3: end
        0.525f, 0.3f, 0.0f,
        0.375f, 0.1f, 0.0f, 
        0.525f, 0.1f, 0.0f,
        //block2
        };

    this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data_box, COLOR_BLOCK, GL_FILL);

    static const GLfloat vertex_buffer_data_fire1[] = {    
        0.075f, 0.2f, 0.0f, // triangle 1 : begin
        0.0f, 0.2f, 0.0f,
        0.0375f, 0.3f, 0.0f,// triangle 1 : end
        0.075f, 0.2f, 0.0f,
        0.15f, 0.2f, 0.0f, 
        0.1125f, 0.3f, 0.0f,
        0.15f, 0.2f, 0.0f, // triangle 3 : begin
        0.225f, 0.2f, 0.0f,
        0.1875f, 0.3f, 0.0f,// triangle 3: end
        0.2625f, 0.3f, 0.0f,
        0.3f, 0.2f, 0.0f, 
        0.225f, 0.2f, 0.0f,
        0.3375f, 0.3f, 0.0f,
        0.3f, 0.2f, 0.0f, 
        0.375f, 0.2f, 0.0f,
        };

    this->fire1 = create3DObject(GL_TRIANGLES, 5*3, vertex_buffer_data_fire1, COLOR_FIRE4, GL_FILL);

    static const GLfloat vertex_buffer_data_fire2[] = {    
        0.075f, 0.2f, 0.0f, // triangle 1 : begin
        0.0f, 0.2f, 0.0f,
        0.0375f, 0.1f, 0.0f,// triangle 1 : end
        0.075f, 0.2f, 0.0f,
        0.15f, 0.2f, 0.0f, 
        0.1125f, 0.1f, 0.0f,
        0.15f, 0.2f, 0.0f, // triangle 3 : begin
        0.225f, 0.2f, 0.0f,
        0.1875f, 0.1f, 0.0f,// triangle 3: end
        0.2625f, 0.1f, 0.0f,
        0.3f, 0.2f, 0.0f, 
        0.225f, 0.2f, 0.0f,
        0.3375f, 0.1f, 0.0f,
        0.3f, 0.2f, 0.0f, 
        0.375f, 0.2f, 0.0f,
        };

    this->fire2 = create3DObject(GL_TRIANGLES, 5*3, vertex_buffer_data_fire2, COLOR_FIRE1, GL_FILL);
}

void Fireline::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    rotate = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->fire1);
    draw3DObject(this->fire2);
}

void Fireline::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Fireline::tick() {
    // this->rotation += speed;
    this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Fireline::bounding_box() {
    float x = this->position.x, y = this->position.y;
    double h = 0.1*2*sin(this->rotation);
    double w = abs(0.3375*2*cos(this->rotation));
    bounding_box_t bbox = { x, y, w, h };
    return bbox;
}


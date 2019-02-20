#include "magnet.h"
#include "main.h"

Magnet::Magnet(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices  
    static const GLfloat vertex_buffer_data_mag1[] = {    
        0.3f, 0.3f, 0.0f,
        0.0f, 0.3f, 0.0f,
        0.3f, 0.1f, 0.0f,

        0.0f, 0.3f, 0.0f,
        0.3f, 0.1f, 0.0f, 
        0.0f, 0.1f, 0.0f,
        };

    this->magnet1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_mag1, COLOR_MAGNET1, GL_FILL);

    static const GLfloat vertex_buffer_data_box2[] = {    
        0.3f, 0.3f, 0.0f,
        0.6f, 0.3f, 0.0f,
        0.3f, 0.1f, 0.0f,
        
        0.6f, 0.3f, 0.0f,
        0.3f, 0.1f, 0.0f, 
        0.6f, 0.1f, 0.0f,
        };

    this->magnet2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_box2, COLOR_MAGNET2, GL_FILL);

}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    rotate = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->magnet1);
    draw3DObject(this->magnet2);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Magnet::tick() {
    // this->rotation += speed;
    this->position.x += speed;
    // this->position.y -= speed;
}


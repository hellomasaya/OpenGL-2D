#include "coin.h"
#include "main.h"

Coin::Coin(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[100000];
    int j=0;
    int angle = 0;
    double radius =0.08;
    for (int i=0; i<1080; i++) {
        if(i%3==0){
            vertex_buffer_data[j++] = 0.0f;
            vertex_buffer_data[j++] = 0.0f;
            vertex_buffer_data[j++] = 0.0f;
        } else if(i%3==1) {
            vertex_buffer_data[j++] = radius*cos((angle*3.1428)/180);
            vertex_buffer_data[j++] = radius*sin((angle*3.1428)/180);
            vertex_buffer_data[j++] = 0.0f;
            angle+=1;
        } else {
            vertex_buffer_data[j++] = radius*cos((angle*3.1428)/180);
            vertex_buffer_data[j++] = radius*sin((angle*3.1428)/180);
            vertex_buffer_data[j++] = 0.0f;
        }
    }

    this->object = create3DObject(GL_TRIANGLES, 10000, vertex_buffer_data, color, GL_FILL);
}

void Coin::draw(glm::mat4 VP) {
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
}

void Coin::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Coin::tick() {
    // this->rotation += speed;
    this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Coin::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.16, 0.16 };
    return bbox;
}


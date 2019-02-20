#include "player.h"
#include "main.h"

Player::Player(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    xspeed = 0;
    yspeed = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data_face[] = {
        -0.15f, 0.3f, 0.0f, // triangle 1 : begin
        0.0f, 0.3f, 0.0f,
        -0.15f, 0.1f, 0.0f,// triangle 1 : end
        0.0f, 0.3f, 0.0f,
        -0.15f, 0.1f, 0.0f, 
        0.0f, 0.1f, 0.0f, // triangle 2 : end
        -0.15f, 0.1f, 0.0f, 
        0.0f, 0.1f, 0.0f, 
        -0.1f, 0.0f, 0.0f, // triangle 3 : end
        -0.1f, 0.0f, 0.0f, // triangle 4 : begin
        -0.05f, 0.0f, 0.0f, 
        0.0f, 0.1f, 0.0f,         
    };

    this->face = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data_face, COLOR_FACE, GL_FILL);

    static const GLfloat vertex_buffer_data_hair[] = {
        -0.15f, 0.3f, 0.0f, // triangle 1 : begin
        0.07f, 0.3f, 0.0f,
        -0.15f, 0.15f, 0.0f,// triangle 1 : end
        
    };

    this->hair = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data_hair, COLOR_HAIR, GL_FILL);

    static const GLfloat vertex_buffer_data_jet[] = {
        -0.15f, -0.3f, 0.0f, // triangle 1 : begin
        -0.15f, -0.07f, 0.0f,
        -0.2f, -0.07f, 0.0f,// triangle 1 : end
        -0.2f, -0.07f, 0.0f,// triangle 2 : begin
        -0.2f, -0.3f, 0.0f,
        -0.15f, -0.3f, 0.0f, // triangle 2 : end
        
    };

    this->jetpack = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_jet, COLOR_JETPACK, GL_FILL);

    static const GLfloat vertex_buffer_data_body[] = {
        -0.1f, 0.0f, 0.0f, // triangle 1 : begin
        -0.05f, 0.0f, 0.0f,
        -0.15f, -0.1f, 0.0f,// triangle 1 : end
        -0.05f, 0.0f, 0.0f,
        -0.15f, -0.1f, 0.0f,
        0.0f, -0.1f, 0.0f, //neck ends
        -0.15f, -0.1f, 0.0f,//torso starts
        0.0f, -0.1f, 0.0f,
        -0.15f, -0.3f, 0.0f,
        0.0f, -0.1f, 0.0f,
        -0.15f, -0.3f, 0.0f,
        0.0f, -0.3f, 0.0f,// torso ends
        0.0f, -0.3f, 0.0f,//legs start
        -0.15f, -0.4f, 0.0f,
        -0.15f, -0.3f, 0.0f,
        0.0f, -0.4f, 0.0f,//tri 2
        0.0f, -0.3f, 0.0f,
        -0.15f, -0.3f, 0.0f,
    };
    this->body = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data_body, COLOR_BODY, GL_FILL);
}

void Player::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    rotate = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // Matrices.model *= (translate);
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->face);
    draw3DObject(this->hair);
    draw3DObject(this->body);
    draw3DObject(this->jetpack);
}

void Player::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Player::tick() {
    // this->rotation += speed;
    this->position.x += xspeed;
    this->position.y += yspeed;
}

bounding_box_t Player::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.22, 0.7 };
    return bbox;
}
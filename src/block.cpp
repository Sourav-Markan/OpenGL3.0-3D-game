    #include "block.h"
#include "main.h"
Block::Block(float x, float y, color_t color) {
    this->position = glm::vec3(x, 0, y);
    this->rotation = 0;
    speed = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        
        // Block
          0.0f, 1.9f, 0.0f,
        -0.8f, 0.0f, -0.8f,
        0.8f, 0.0f, -0.8f,//
        0.0f, 1.9f, 0.0f,
        0.8f, 0.0f, -0.8f,
        0.8f, 0.0f, 0.8f,//
        0.0f, 1.9f, 0.0f,
        0.8f, 0.0f, 0.8f,
        -0.8f, 0.0f, 0.8f,//
        0.0f, 1.9f, 0.0f,
        -0.8f, 0.0f, 0.8f,
        -0.8f, 0.0f, -0.8f,//
    };

   

    this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, color, GL_FILL);
}

void Block::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Block::set_position(float x, float y) {
    this->position = glm::vec3(x, 0, y);
}

void Block::tick() {
    // this->rotation += speed;
}
bounding_box_t Block::bounding_box() {
    float x = this->position.x, y = this->position.y,z= this->position.z;
    bounding_box_t bbox = { x, y, z, 1, 1, 1 };
    return bbox;
}

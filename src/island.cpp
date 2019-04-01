#include "island.h"
#include "main.h"
Island::Island(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    color_t color_island = { 240,230,140 };
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        
        // Sea
        100.0f,0.5f,200.0f,
        -100.0f,0.5f,100.0f,
        100.0f,0.5f,100.0f,//
        100.0f,0.5f,200.0f,
        -100.0f,0.5f,100.0f,
        -100.0f,0.5f,200.0f,//
    };
static const GLfloat vertex_buffer_data2[] = {
        50.0f, 4.0f, 120.0f,
        30.0f, 0.0f, 130.0f,
        70.0f, 0.0f, 130.0f,//
        50.0f, 4.0f, 120.0f,
        70.0f, 0.0f, 130.0f,
        70.0f, 0.0f, 110.0f,//
        50.0f, 4.0f, 120.0f,
        70.0f, 0.0f, 110.0f,
        30.0f, 0.0f, 110.0f,//
        50.0f, 4.0f, 120.0f,
        30.0f, 0.0f, 110.0f,
        30.0f, 0.0f, 130.0f,//


    };
   

    this->object[0] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color_island, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data2, COLOR_purple, GL_FILL);

}

void Island::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
}

void Island::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Island::tick() {
    this->rotation += speed;
}


#include "flag.h"
#include "main.h"

Flag::Flag(float x, float y, color_t color) {
    this->position = glm::vec3(x,1, y);
    this->rotation = 0;
    speed_y = 0.03;
    color_t COLOR_flag ={255,20,148};
//    acc_y   =  0.01;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data1[] = {
        
        // Base of the boat.
        0.0f, 3.3f, 0.0f,
        1.5f, 1.2f, 0.0f,
        -1.5f, 1.2f, 0.0f,
        
    };

    static const GLfloat vertex_buffer_data2[] = {
        //Hexagon of boat
        0.0f, 0.0f, 1.7f,
        -0.4f,0.0f, 3.5f,
        0.4f, 0.0f,3.5f,

        // 0.0f, 1.6f, 2.5f,
        // 0.0f, 1.3f, 1.7f,
        // 0.4f, 1.0f, 1.7f,

        // 0.0f, 1.3f, 1.7f,
        // -0.4f, 1.0f, 1.7f,
        // -0.4f, 1.0f, 1.7f,

        // -0.4f, 1.0f,1.7f,
        // 0.4f, 1.0f, 1.7f,
        // 0.0f, 1.6f, 2.5f,
    };


    // static const GLfloat vertex_buffer_data3[] = {
        
        
    // };


    this->object[0] = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data1, COLOR_flag, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data2, COLOR_white, GL_FILL);
    // this->object[2] = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data3, COLOR_BLACK, GL_FILL);
}

void Flag::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
    // draw3DObject(this->object[2]);
}

void Flag::set_position(float x, float y) {
    this->position = glm::vec3(x, 0.0, y);
}

void Flag::change_speed(){
//    if(this->position.y == 0.1)
//        speed_y = -speed_y;
}

void Flag::tick() {
    change_speed();
    // this->rotation += speed;
    // this->position.x-= speed;
     this->position.y += speed_y;
}

bounding_box_t Flag::bounding_box() {
    float x = this->position.x, y = this->position.y,z= this->position.z;
    bounding_box_t bbox = { x, y, z, 2, 2, 2 };
    return bbox;
}


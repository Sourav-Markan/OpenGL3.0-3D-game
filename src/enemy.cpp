#include "enemy.h"
#include "main.h"

Enemy::Enemy(float x, float y, color_t color) {
    this->position = glm::vec3(x, -0.1, y);
    this->rotation = 90;
    speed_x = RandomFloat(-0.1,0.1);
    // speed_x =0;
    // speed_z =0;
    speed_z = RandomFloat(-0.1,0.1);
//    acc_y   =  0.01;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        
        // Cube
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
    };

    static const GLfloat vertex_buffer_data2[] = {
        
        // Eyes
        -0.6f,1.0f,0.7f,
        -0.9f,1.0f,0.3f,
        -0.3f,1.0f,0.3f,

        0.6f,1.0f,0.7f,
        0.9f,1.0f,0.3f,
        0.3f,1.0f,0.3f,

        -0.6f,-1.0f,0.7f,
        -0.9f,-1.0f,0.3f,
        -0.3f,-1.0f,0.3f,

        0.6f,-1.0f,0.7f,
        0.9f,-1.0f,0.3f,
        0.3f,-1.0f,0.3f, 
        
    };

    static const GLfloat vertex_buffer_data3[] = {
        
        // Eyes
        0.0f,2.5f,0.0f,
        -1.0f,1.0f,-1.0f,
        -1.0f,1.0f,1.0f,

        0.0f,2.5f,0.0f,
        -1.0f,1.0f,1.0f,
        1.0f,1.0f,1.0f,

        0.0f,2.5f,0.0f,
        1.0f,1.0f,1.0f,
        1.0f,1.0f,-1.0f,

        0.0f,2.5f,0.0f,
        1.0f,1.0f,-1.0f,
        -1.0f,1.0f,-1.0f,
        
    };
   

    this->object[0] = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_maroon, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data2, COLOR_white, GL_FILL);
    this->object[2] = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data3, COLOR_GREEN, GL_FILL);
}

void Enemy::draw(glm::mat4 VP) {
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
    draw3DObject(this->object[2]);
}

void Enemy::set_position(float x, float y) {
    this->position = glm::vec3(x, -0.01, y);
}

void Enemy::change_speed(){
//    if(this->position.y == 0.1)
//        speed_y = -speed_y;
}

void Enemy::tick() {
    change_speed();
    // this->rotation += speed;
     this->position.x += speed_x;
     this->position.z += speed_z;
}

bounding_box_t Enemy::bounding_box() {
    float x = this->position.x, y = this->position.y,z= this->position.z;
    bounding_box_t bbox = { x, y, z, 1, 1, 1 };
    return bbox;
}


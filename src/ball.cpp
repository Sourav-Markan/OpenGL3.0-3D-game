#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, -0.1, y);
    this->rotation = 90;
    speed_y = 0.03;
//    acc_y   =  0.01;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data1[] = {
        
        // Base of the boat.
        0.0f, 0.21f, -2.0f,
        1.0f, 0.21f, -1.0f,
        -1.0f, 0.21f, -1.0f,//
        1.0f, 0.21f, -1.0f,
        1.0f, 0.21f, 1.0f,
        -1.0f, 0.21f, -1.0f,//
        -1.0f, 0.21f, -1.0f,
        1.0f, 0.21f, 1.0f,
        -1.0f, 0.21f, 1.0f,//
        -1.0f, 0.21f, 1.0f,
        1.0f, 0.21f, 1.0f,
        0.0f, 0.21f, 2.0f,//
    };

    static const GLfloat vertex_buffer_data2[] = {
        //Hexagon of boat
        0.0f,1.0f, -2.0f,
        1.0f,1.0f,-1.0f,
        1.0f, 0.0f, -1.0f,
        0.0f,1.0f, -2.0f,
        0.0f,0.0f,-2.0f,
        1.0f, 0.0f, -1.0f,//
        
        0.0f,1.0f,2.0f,
        1.0f,1.0f, 1.0f,
        0.0f, 0.0f, 2.0f,
        1.0f,0.0f,1.0f,
        1.0f,1.0f, 1.0f,
        0.0f, 0.0f, 2.0f,//

        1.0f,1.0f,-1.0f,
        1.0f,1.0f, 1.0f,
        1.0f, 0.0f, -1.0f,
        1.0f,0.0f,1.0f,
        1.0f,1.0f, 1.0f,
        1.0f, 0.0f, -1.0f,//

        
        -1.0f,1.0f,-1.0f,
        -1.0f,1.0f, 1.0f,
        -1.0f, 0.0f, -1.0f,
        -1.0f,0.0f,1.0f,
        -1.0f,1.0f, 1.0f,
        -1.0f, 0.0f, -1.0f,//

        0.0f,1.0f,2.0f,
        -1.0f,1.0f, 1.0f,
        0.0f, 0.0f, 2.0f,
        -1.0f,0.0f,1.0f,
        -1.0f,1.0f, 1.0f,
        0.0f, 0.0f, 2.0f,//

        -1.0f,1.0f,-1.0f,
        0.0f,1.0f, -2.0f,
        -1.0f, 0.0f, -1.0f,
        0.0f,0.0f,-2.0f,
        0.0f,1.0f, -2.0f,
        -1.0f, 0.0f, -1.0f,//
    };


    static const GLfloat vertex_buffer_data3[] = {
        //Flag Stand
        0.0f, 5.0f, 0.0f,
        -0.3f, 0.0f, -0.3f,
        0.3f, 0.0f, -0.3f,//
        0.0f, 5.0f, 0.0f,
        0.3f, 0.0f, -0.3f,
        0.3f, 0.0f, 0.3f,//
        0.0f, 5.0f, 0.0f,
        0.3f, 0.0f, 0.3f,
        -0.3f, 0.0f, 0.3f,//
        0.0f, 5.0f, 0.0f,
        -0.3f, 0.0f, 0.3f,
        -0.3f, 0.0f, -0.3f,//
    };



    static const GLfloat vertex_buffer_data5[] = {
        //Flag 
        0.0f, 1.6f, -2.5f,
        0.0f, 1.3f, -1.7f,
        -0.4f, 1.0f,-1.7f,

        0.0f, 1.6f, -2.5f,
        0.0f, 1.3f, -1.7f,
        0.4f, 1.0f, -1.7f,

        0.0f, 1.3f, -1.7f,
        -0.4f, 1.0f, -1.7f,
        -0.4f, 1.0f, -1.7f,

        -0.4f, 1.0f,-1.7f,
        0.4f, 1.0f, -1.7f,
        0.0f, 1.6f, -2.5f,
    };

    static const GLfloat vertex_buffer_data6[] = {
    
    -0.2f,1.6f,-12.0f,
     0.2f,1.6f,-12.0f,
    -0.2f,0.7f,-12.0f,

     0.2f,1.6f,-12.0f,
     0.2f,0.6f,-12.0f,
    -0.2f,0.6f,-12.0f,

    0.3f,1.2f,-12.0f,
    -0.3f,1.2f,-12.0f,
    -0.3f,0.8f,-12.0f,

    0.3f,1.2f,-12.0f,
    0.3f,0.8f,-12.0f,
    -0.3f,0.8f,-12.0f,        
    };

    this->object[0] = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data1, COLOR_yellow, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data2, COLOR_RED, GL_FILL);
    this->object[2] = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data3, COLOR_BLACK, GL_FILL);
    // this->object[3] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data4, COLOR_purple, GL_FILL);
    // this->object[4] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data4+18, COLOR_maroon, GL_FILL);
    this->object[3] = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data5, COLOR_olive, GL_FILL);
    this->object[4] = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data6, COLOR_BLACK, GL_FILL);


}

void Ball::draw(glm::mat4 VP) {
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
    // draw3DObject(this->object[3]);
    // draw3DObject(this->object[4]);
    draw3DObject(this->object[3]);
    draw3DObject(this->object[4]);


}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, -0.01, y);
}

void Ball::change_speed(){
//    if(this->position.y == 0.1)
//        speed_y = -speed_y;
}

void Ball::tick() {
    change_speed();
    // this->rotation += speed;
    // this->position.x-= speed;
     this->position.y += speed_y;
}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y,z= this->position.z;
    bounding_box_t bbox = { x, y, z, 2, 2, 2 };
    return bbox;
}


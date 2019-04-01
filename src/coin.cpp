#include "coins.h"
#include "main.h"

Coin::Coin(float x, float y, color_t color) {
    this->position = glm::vec3(x, -0.1, y);
    this->rotation = 90;
    //speed_y = 0.01;
    int k=y;
    color_t color_coin = { (k+120)%255, (k*2+210)%255, (k*3) %255 };
    speed_y = RandomFloat(-0.11,0.152);
//    acc_y   =  0.01;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    float radius=1;
    int n=100,count=0;
        double anglechange=0;
        anglechange = 360/n;
        GLfloat g_vertex_buffer_data[9*50];

        for(int i=0;i<50;i++)
        {
            g_vertex_buffer_data[0+9*i] = 0.0f;
            g_vertex_buffer_data[1+9*i] = 1.0f;
            g_vertex_buffer_data[2+9*i] = 0.0f;

            g_vertex_buffer_data[3+9*i] = cos(i*2*M_PI/50)*1.0f;
            g_vertex_buffer_data[4+9*i] = 1+sin(i*2*M_PI/50)*1.0f;
            g_vertex_buffer_data[5+9*i] = 0.0f;

            g_vertex_buffer_data[6+9*i] = cos((i+1)*2*M_PI/50)*1.0f;
            g_vertex_buffer_data[7+9*i] = 1+sin((i+1)*2*M_PI/50)*1.0f;
            g_vertex_buffer_data[8+9*i] = 0.0f;
        };

        static const GLfloat vertex_buffer_data2[] = {
        0.0f, -2.0f, 0.0f,
        -1.5f, 0.0f, -1.5f,
        1.5f, 0.0f, -1.5f,//
        0.0f, -2.0f, 0.0f,
        1.5f, 0.0f, -1.5f,
        1.5f, 0.0f, 1.5f,//
        0.0f, -2.0f, 0.0f,
        1.5f, 0.0f, 1.5f,
        -1.5f, 0.0f, 1.5f,//
        0.0f, -2.0f, 0.0f,
        -1.5f, 0.0f, 1.5f,
        -1.5f, 0.0f, -1.5f,//


    };
    this->object[0] = create3DObject(GL_TRIANGLES, 50*3, g_vertex_buffer_data, color, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data2, color_coin, GL_FILL);

}

void Coin::draw(glm::mat4 VP) {
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
}

void Coin::set_position(float x, float y) {
    this->position = glm::vec3(x, -0.01, y);
}

void Coin::change_speed(){
//    if(this->position.y == 0.1)
//        speed_y = -speed_y;
}

void Coin::tick() {
    change_speed();
    this->position.y -=speed_y;
    this->rotation += 4;

}

bounding_box_t Coin::bounding_box() {
    float x = this->position.x, y = this->position.y,z= this->position.z;
    bounding_box_t bbox = { x, y, z, 1, 1, 1 };
    return bbox;
}


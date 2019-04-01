#include "man.h"
#include "main.h"
Man::Man(float x, float y, color_t color) {
    this->position = glm::vec3(x, 0, y);
    this->rotation = 90;
    speed = 1;
    color_t COLOR_man = { 255, 160, 122 };
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        
        // Block
          0.0f, 2.0f, 0.0f,
        -0.5f, 1.0f, -0.5f,
        0.5f, 1.0f, -0.5f,//
        0.0f, 2.0f, 0.0f,
        0.5f, 1.0f, -0.5f,
        0.5f, 1.0f, 0.5f,//
        0.0f, 2.0f, 0.0f,
        0.5f, 1.0f, 0.5f,
        -0.5f, 1.0f, 0.5f,//
        0.0f, 2.0f, 0.0f,
        -0.5f, 1.0f, 0.5f,
        -0.5f, 1.0f, -0.5f,//
    };
static const GLfloat vertex_buffer_data2[] = {
        0.0f, 0.0f, 0.0f,
        -0.5f, 1.0f, -0.5f,
        0.5f, 1.0f, -0.5f,//
        0.0f, 0.0f, 0.0f,
        0.5f, 1.0f, -0.5f,
        0.5f, 1.0f, 0.5f,//
        0.0f, 0.0f, 0.0f,
        0.5f, 1.0f, 0.5f,
        -0.5f, 1.0f, 0.5f,//
        0.0f, 0.0f, 0.0f,
        -0.5f, 1.0f, 0.5f,
        -0.5f, 1.0f, -0.5f,//


    };
GLfloat g_vertex_buffer_data[9*50];

        for(int i=0;i<50;i++)
        {
            g_vertex_buffer_data[0+9*i] = 0.0f;
            g_vertex_buffer_data[1+9*i] = 2.0f;
            g_vertex_buffer_data[2+9*i] = 0.0f;

            g_vertex_buffer_data[3+9*i] = cos(i*2*M_PI/50)*0.3f;
            g_vertex_buffer_data[4+9*i] = 2+sin(i*2*M_PI/50)*0.3f;
            g_vertex_buffer_data[5+9*i] = 0.0f;

            g_vertex_buffer_data[6+9*i] = cos((i+1)*2*M_PI/50)*0.3f;
            g_vertex_buffer_data[7+9*i] = 2+sin((i+1)*2*M_PI/50)*0.3f;
            g_vertex_buffer_data[8+9*i] = 0.0f;
        };

    this->object[0] = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, COLOR_yellow, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data2, COLOR_RED, GL_FILL);
    this->object[2] = create3DObject(GL_TRIANGLES, 50*3, g_vertex_buffer_data, COLOR_man, GL_FILL);


   

}

void Man::draw(glm::mat4 VP) {
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

void Man::set_position(float x, float y) {
    this->position = glm::vec3(x, 0, y);
}

void Man::tick() {
    this->rotation += speed;
}


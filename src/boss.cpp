#include "boss.h"
#include "main.h"

Boss::Boss(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;

    this->speed_x = 0.05;
    this->speed_z = 0.05;

    this->shots=level+2;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        
        1.0f,1.0f,1.0f,
        -1.0f,-1.0f,1.0f,
        1.0f,-1.0f,1.0f,       //red face end
-1.0f, 1.0f, 1.0f,  //red face start
        -1.0f,-1.0f,1.0f,
        1.0f,1.0f,1.0f,

        
        1.0f,-1.0f,1.0f,
        1.0f,1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,

        
        -1.0f,-1.0f,-1.0f,
        1.0f,1.0f,-1.0f,
        -1.0f,1.0f,-1.0f,
1.0f, -1.0f, 1.0f,
        1.0f,1.0f,-1.0f,
        1.0f,-1.0f,1.0f,
        -1.0f,1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,1.0f,1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,1.0f,1.0f,
        -1.0f,-1.0f,1.0f,
        1.0f,1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,

        
        -1.0f,1.0f,-1.0f,
        1.0f,1.0f,1.0f,
        1.0f,1.0f,-1.0f,

        -1.0f,-1.0f,1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,1.0f,
        -1.0f,1.0f,1.0f,
        -1.0f,1.0f,-1.0f,
        1.0f,1.0f,1.0f,
        

        0.0f, 2.5f, 0.0f,
        -1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,

        0.0f, 2.5f, 0.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,

        0.0f, 2.5f, 0.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,1.0f,
        1.0f,-1.0f,-1.0f,
        0.0f, 2.5f, 0.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,

        0.2f, 0.3f, 1.0f,
        0.6f, 0.5f, 1.0f,
        0.4f, 0.0f, 1.0f,

        -0.2f, 0.3f, 1.0f,
        -0.6f, 0.5f, 1.0f,
        -0.4f, 0.0f, 1.0f,

        0.4f, -0.15f, 1.0f,
        0.0f, -0.3f, 1.0f,
        0.0f, -0.55f, 1.0f,

        -0.4f, -0.15f, 1.0f,
        0.0f, -0.3f, 1.0f,
        0.0f, -0.55f, 1.0f
        //smile_end

    };

    this->object1 = create3DObject(GL_TRIANGLES, 48, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data + 144, COLOR_RED, GL_FILL);
}

void Boss::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Boss::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Boss::tick(float x, float z, float orientation) {
    this->position.x += speed_x  * (x/pow(pow(x,2)+pow(z,2),0.5));
    this->position.z += speed_z  * (z/pow(pow(x,2)+pow(z,2),0.5));
    this->rotation = orientation-M_PI/2;

}

bounding_box_t Boss::bounding_box() {
    float x = this->position.x, y = this->position.y,z= this->position.z;
    bounding_box_t bbox = { x, y, z, 1, 1, 1 };
    return bbox;
}

void Boss::emerge_boss(){
    if(this->position.y < 0.75)
        this->position.y += 0.03;
}


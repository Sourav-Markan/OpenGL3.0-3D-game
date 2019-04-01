#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "main.h"

bool   cannon_keyboard_input = true;
bool   drag_pan = false, old_cki;
double drag_oldx = -1, drag_oldy = -1;

using namespace std;

/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Function is called first on GLFW_PRESS.

    if (action == GLFW_RELEASE) {
        // if(key==glfwGetKey(window, GLFW_KEY_V))
        // {

        // }
    } else if (action == GLFW_PRESS) {
        switch (key) {
        case GLFW_KEY_ESCAPE:
            quit(window);
            break;
        default:
            break;
        }
    }
}

/* Executed for character input (like in text boxes) */
void keyboardChar(GLFWwindow *window, unsigned int key) {
    switch (key) {
    case 'Q':
    case 'q':
        quit(window);
        break;
    case 'V':
    case 'v':
        changeview();
        break;
    case 'X':
    case 'x':
        attack();
        break;
    default:
        break;
    }
}

/* Executed when a mouse button is pressed/released */
void mouseButton(GLFWwindow *window, int button, int action, int mods) {
    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
        if (action == GLFW_PRESS) {
            glfwGetCursorPos(window, &x, &y);
            hx=600-x;
            hz=600-y;
            return;
        } else if (action == GLFW_RELEASE) {
            // Do something
        }
        break;
    // case GLFW_MOUSE_BUTTON_RIGHT:
    // if (action == GLFW_RELEASE) {
    // rectangle_rot_dir *= -1;
    // }
    // break;
    default:
        break;
    }
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    // Do something
    if(yoffset==1)
    {
        zoom--;
        helx=helx+zoom*cos(camera_rotation_angle*M_PI/180.0f);
        hely=hely-0.1;
        helz=helz+zoom*sin(camera_rotation_angle*M_PI/180.0f);
    }
    if(yoffset==-1)
    {
        zoom++;
        helx=helx-zoom*cos(camera_rotation_angle*M_PI/180.0f);
        hely=hely+0.1;
        helz=helz-zoom*sin(camera_rotation_angle*M_PI/180.0f);
    }
    printf("y_off %f\n",yoffset);
}

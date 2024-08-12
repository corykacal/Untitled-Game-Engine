#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "debug/Debug.h"
#include <GLFW/glfw3.h>

#ifndef UNTITLED_CAMERA_H
#define UNTITLED_CAMERA_H


class Camera {
private:
    Camera(u_int width, u_int height);
    static Camera* instance;

    float x;
    float y;

    float pitch;
    float yaw;
    float lastX;
    float lastY;

    bool firstMouse;

    glm::vec3 cameraFront;
    glm::vec3 cameraPos;

    glm::mat4 proj;
    glm::mat4 view;

    u_int windowHeight;
    u_int windowWidth;

    void mouse_callback(GLFWwindow* window, float xpos, float ypos);

public:
    ~Camera();

    static Camera & init(u_int width, u_int height);
    static Camera & get();

    void SetWindowDimensions(u_int width, u_int height);
    void SetPosition(float x, float y);
    glm::mat4 GetMVP();
    glm::vec3 getCameraPosition();

    float getXPos() const;
    float getYPos() const;

    void moveFoward(float speedForward, float speedSideways);

    static void static_mouse_callback(GLFWwindow* window, float xpos, float ypos);
};


#endif //UNTITLED_CAMERA_H

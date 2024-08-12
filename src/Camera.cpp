#include "Camera.h"

Camera::~Camera() {
}

const glm::vec3 up = glm::vec3(0,1,0);

Camera* Camera::instance{nullptr};

Camera::Camera(u_int width, u_int height) {
    Camera::x = 0.0f;
    Camera::y = 0.0f;
    Camera::pitch = 0.0f;
    Camera::yaw = 0.0f;
    Camera::firstMouse = true;
    Camera::lastX = x;
    Camera::lastY = y;
    Camera::windowHeight = height;
    Camera::windowWidth = width;

    cameraPos = glm::vec3(0, 4, 0);
    cameraFront = glm::vec3(-1, 0, -1);

    Camera::proj = glm::perspective(
            glm::radians(90.0f),
            (float) windowWidth / (float) windowHeight,
            0.1f, 300.0f);
    Camera::view = glm::lookAt(cameraPos, cameraFront, up);
}

Camera & Camera::init(u_int width, u_int height) {
    if (!instance) {
        instance = new Camera(width, height);
    }

    instance->SetWindowDimensions(width, height);
    return *instance;
}

Camera &Camera::get() {
    ASSERT(instance);

    return *instance;
}

void Camera::SetPosition(float x, float y) {
    Camera::x = x;
    Camera::y = y;
}

glm::mat4 Camera::GetMVP() {
    return proj * view;
}

void Camera::SetWindowDimensions(u_int width, u_int height) {
    Camera::windowWidth = width;
    Camera::windowHeight = height;
}

void Camera::moveFoward(float speedForward, float speedSideways) {
    cameraPos += cameraFront * speedForward;
    cameraPos += glm::cross(cameraFront, up) * speedSideways;

    Camera::view = glm::lookAt(cameraPos, cameraPos + cameraFront, up);
}

float Camera::getXPos() const {
    return Camera::x;
}

float Camera::getYPos() const {
    return Camera::y;
}

void Camera::mouse_callback(GLFWwindow* window, float xpos, float ypos) {
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

void Camera::static_mouse_callback(GLFWwindow *window, float xpos, float ypos) {
    Camera::get().mouse_callback(window, xpos, ypos);
}

glm::vec3 Camera::getCameraPosition() {
    return cameraPos;
}

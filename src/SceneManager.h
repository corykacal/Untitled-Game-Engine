#include "list"
#include "models/Model.h"
#include "Renderer.h"
#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "../vendor/perlin/PerlinNoise.hpp"
#include "Camera.h"
#include "map/ChunkManager.h"
#include "util/OBJLoader.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "../vendor/glm/gtx/string_cast.hpp"

#ifndef UNTITLED_SCENEMANAGER_H
#define UNTITLED_SCENEMANAGER_H


class SceneManager {

private:
    SceneManager();
    static SceneManager* instance;

    std::list<Model*> shapes;

    Camera* camera;

public:
    ~SceneManager();

    static SceneManager & init();
    static SceneManager & get();

    void addToScene(Model* shape);
    std::list<Model*> getScene();

    // Delete copy assignment and move assignment constructors
    SceneManager(const SceneManager&) = delete;
    SceneManager(SceneManager&&) = delete;

    // Delete copy assignment and move assignment operators
    SceneManager& operator=(const SceneManager&) = delete;
    SceneManager& operator=(SceneManager&&) = delete;

    void Compile();

    Camera* getCamera();
    static void static_callback(GLFWwindow *window, float xpos, float ypos);
};


#endif //UNTITLED_SCENEMANAGER_H

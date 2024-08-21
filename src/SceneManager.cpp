#include "SceneManager.h"
#include "debug/PerformanceTest.h"
#include "models/Triangle.h"
#include "models/Square.h"

SceneManager::~SceneManager() {
    Renderer::Shutdown();
}

SceneManager* SceneManager::instance{nullptr};

SceneManager::SceneManager() {
    Renderer::Init();
    Renderer::SetUniform1i("u_FogDistance", 100);
    ChunkManager::Init();
    camera = &Camera::init(1440, 900);
    int chunkdistance = 4;
    for(int i=-chunkdistance; i<chunkdistance; i++) {
        for(int j=-chunkdistance; j<chunkdistance; j++) {
            ChunkManager::AddChunk({i,j});
        }
    }
    vector<Chunk> dirtyChunks = ChunkManager::GetDirtyChunks();
    for(const Chunk& dirtyChunk : dirtyChunks) {
        for(Quadrilateral* quad : dirtyChunk.quads) {
            Renderer::AddModel(quad);
        }
    }
    Renderer::AddModel(OBJLoader::LoadOBJ("../res/models/monkey.obj"));
    //THE SUN
    glm::vec4 sunColor = {1.0f, 0.9f, 0.9f, 1.0f};
    glm::vec3 sunPos = {40,100,0};
    Renderer::SetUniform3fv("u_LightColor", sunColor);
    Renderer::SetUniform3fv("u_LightPosition", sunPos);
    Renderer::AddModel(new Cube(7, sunPos, sunColor));
    Renderer::AddModel(new Cube(4, {70, 80, 30}, {1.0f, 1.0f, 1.0f, 1.0f}));
    Renderer::SetUniform3fv("u_AmbientLightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    Renderer::SetUniform1f("u_AmbientLightStrength", 0.3f);
}

SceneManager & SceneManager::init() {
    if (!instance)
        instance = new SceneManager();

    return *instance;
}

SceneManager &SceneManager::get() {
    ASSERT(instance);

    return *instance;
}

void SceneManager::addToScene(Model* shape) {
    shapes.push_back(shape);
}

std::list<Model*> SceneManager::getScene() {
    return shapes;
}

void SceneManager::Compile() {
    Renderer::SetUniformMat4f("u_MVP", camera->GetMVP());
    Renderer::SetUniform3fv("u_CameraPos", camera->getCameraPosition());
    Renderer::Clear();
    Renderer::Draw();
}

Camera *SceneManager::getCamera() {
    return camera;
}

void SceneManager::static_callback(GLFWwindow *window, float xpos, float ypos) {
    Camera::static_mouse_callback(window, xpos, ypos);
}

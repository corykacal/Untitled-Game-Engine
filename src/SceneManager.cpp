#include "SceneManager.h"

SceneManager::~SceneManager() {
    Renderer::Shutdown();
}

SceneManager* SceneManager::instance{nullptr};

SceneManager::SceneManager() {
    Renderer::Init();
    Renderer::SetFogDistance(100);
    ChunkManager::Init();
    camera = &Camera::init(1440, 900);
    int chunkdistance = 2;
    for(int i=-chunkdistance; i<chunkdistance; i++) {
        for(int j=-chunkdistance; j<chunkdistance; j++) {
            for(int k=-chunkdistance; k<chunkdistance; k++)
            ChunkManager::AddChunk({i,j,k});
        }
    }
    vector<Chunk> dirtyChunks = ChunkManager::GetDirtyChunks();
    for(const Chunk& dirtyChunk : dirtyChunks) {
        for(Triangle* quad : dirtyChunk.triangles) {
            Renderer::AddModel(quad);
        }
    }
    //THE SUN
    glm::vec4 sunColor = {1.0f, 0.9f, 0.9f, 1.0f};
    glm::vec3 sunPos = {0,120,0};
    Renderer::SetLightColor(sunColor);
    Renderer::SetLightPosition(sunPos);
    Renderer::AddModel(new Cube(7, sunPos, sunColor));
    Renderer::SetAmbientLightColor(glm::vec3(1.0f, 1.0f, 1.0f));
    Renderer::SetAmbientLightStrength(0.3f);
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
    Renderer::SetView(camera->GetView());
    Renderer::SetProjection(camera->GetProjection());
    Renderer::SetCameraPos(camera->getCameraPosition());
    Renderer::Draw();
}

Camera *SceneManager::getCamera() {
    return camera;
}

void SceneManager::static_callback(GLFWwindow *window, float xpos, float ypos) {
    Camera::static_mouse_callback(window, xpos, ypos);
}

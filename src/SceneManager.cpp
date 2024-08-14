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
    PerformanceTest::UseFPS(true);
    PerformanceTest::Start();
    vector<Chunk> dirtyChunks = ChunkManager::GetDirtyChunks();
    //each triangle has uuid.
    //keep track of uuid and memory address in renderer
    //when model changes
    //instead of checking when model changes, just set certain functions that will modify the model to be dirty.
    //if a model is drity, use its uuid to find its verticies in the buffer and update them in place.
    //if model goes away. delete from buffer. there will be fragmentaion there. have that open space.
    //polygon, sequences of 3, can be filled out of order. the triangle is very ipmortant.
    //fill triangles of data. should I make every Model out of Traingle objects?
    //
    //model changes: get all model classes on same page in constructors and class variables
    //make models instatiate triagnles? make triangle a struct?
    //GetVerticies in model compile all triangles in class?
    //flesh out the function variables too. like Coord.
    //create dirty function inside Model. wrap/override Setsize and shit with dirty.
    //dirty function will add uuid to renderer?
    if(!dirtyChunks.empty()) {
        for(const Chunk& dirtyChunk : dirtyChunks) {
            for(Quadrilateral* quad : dirtyChunk.quads) {
                Renderer::AddModel(quad);
            }
        }
        //Renderer::AddModel(new Cube(7, {0, 0, -10}, {0.3f, 0.2f, 1.0f, 1.0f}));
    }
    Renderer::SetUniformMat4f("u_MVP", camera->GetMVP());
    Renderer::SetUniform3fv("u_CameraPos", camera->getCameraPosition());
    Renderer::Clear();
    Renderer::Draw();
    PerformanceTest::End();
}

Camera *SceneManager::getCamera() {
    return camera;
}

void SceneManager::static_callback(GLFWwindow *window, float xpos, float ypos) {
    Camera::static_mouse_callback(window, xpos, ypos);
}

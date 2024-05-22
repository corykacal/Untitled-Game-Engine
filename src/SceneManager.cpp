//
// Created by Cory Kacal on 5/8/24.
//

#include "SceneManager.h"
#include "Debug.h"
#include "Texture.h"

SceneManager::SceneManager() = default;
SceneManager::~SceneManager() = default;

SceneManager* SceneManager::instance{nullptr};
Renderer* SceneManager::renderer{nullptr};
Shader* SceneManager::shader{nullptr};
VertexArray* SceneManager::va{nullptr};
IndexBuffer* SceneManager::ib{nullptr};


SceneManager & SceneManager::init() {
    if (!instance) // EDIT 1: Forgot to add this to the post.
        instance = new SceneManager();

    return *instance;
}

SceneManager &SceneManager::get() {
    ASSERT(instance);

    return *instance;
}

void SceneManager::addToScene(const Shape shape) {
    shapes.push_back(shape);
}

std::list<Shape> SceneManager::getScene() {
    return shapes;
}

void SceneManager::DrawScene() const {
    renderer->Clear();
    renderer->Draw(*va, *ib, *shader);
}

void SceneManager::CompileScene() const {
    //each shape has positions and indices

    float positions[] = {
            -0.5f, -0.5f, 0.0f, 0.0f, // 0
            0.5f, -0.5f, 1.0f, 0.0f, // 1
            0.5f,  0.5f, 1.0f, 1.0f, // 2
            -0.5f,  0.5f, 0.0f, 1.0f  // 3
    };
    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    //this changes based on shapes
    va = new VertexArray();
    VertexBuffer vb = VertexBuffer(positions, sizeof(positions));
    ib = new IndexBuffer(indices, 6);


    //this stays same
    VertexBufferLayout layout;
    layout.AddFloat(2);
    layout.AddFloat(2);

    //stays same
    va->AddBuffer(vb, layout);

    shader = new Shader("../res/shader/vertex.glsl", "../res/shader/fragment.glsl");
    //stays same
    shader->Bind();

    //might be apart of shape
    Texture texture("../res/texture/birb.jpg");
    texture.Bind();
    shader->SetUniform1i("u_Texture", 0);

    renderer = new Renderer();
}

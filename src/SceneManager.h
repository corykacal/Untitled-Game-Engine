#include "list"
#include "shapes/Shape.h"
#include "Renderer.h"

#ifndef UNTITLED_SCENEMANAGER_H
#define UNTITLED_SCENEMANAGER_H


class SceneManager {

private:
    SceneManager();
    static SceneManager* instance;

    std::list<Shape> shapes;

    static Renderer* renderer;
    static Shader* shader;

    static IndexBuffer* ib;
    static VertexArray* va;

public:
    ~SceneManager();

    static SceneManager & init();
    static SceneManager & get();

    void addToScene(const Shape shape);
    std::list<Shape> getScene();


    // Delete copy assignment and move assignment constructors
    SceneManager(const SceneManager&) = delete;
    SceneManager(SceneManager&&) = delete;

    // Delete copy assignment and move assignment operators
    SceneManager& operator=(const SceneManager&) = delete;
    SceneManager& operator=(SceneManager&&) = delete;

    void DrawScene() const;
    void CompileScene() const;


};


#endif //UNTITLED_SCENEMANAGER_H

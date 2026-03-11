#ifndef SCENE_HOLDER_H
#define SCENE_HOLDER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../include/MathLibrary/Shape.h"
#include <vector>
#include "Scene.h"

template <int n>
class SceneHolder : public Scene<n>
{
protected:
    std::vector<Scene<n> *> scenes;

public:
    void draw() override;
    void reloadVertices() override;
    Shape<n> *getShape() const override;
    void addScene(Scene<n> *scene) override;
    ~SceneHolder() override;
};

#include "SceneHolder.cpp"
#endif

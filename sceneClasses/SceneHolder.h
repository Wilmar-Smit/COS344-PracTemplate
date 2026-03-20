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
    Scene<n> *selectedScene = nullptr;

public:
    virtual void draw() override;
    virtual void reloadVertices() override;
    virtual Shape<n> *getShape() const override;
    virtual void addScene(Scene<n> *scene) override;
    virtual ~SceneHolder() override;
    virtual void Rotate(float degrees);
    virtual void Scale(float scale);
    virtual void Translation(Direction dir, float step);
    virtual void select();
    virtual void setWireframeMode();
    virtual void setNormalMode();
    virtual void deselect() override;
    virtual void transform(Matrix<n + 1, n + 1> &trans, bool toCenter)
    {
        return;
    }
    virtual Scene<n> *selectNext();
    virtual Scene<n> *getIndex(int i)
    {
        if (selectedScene)
        {
            this->deselect();
        }
        return scenes[i];
    };
};

#include "SceneHolder.cpp"
#endif

#include "SceneHolder.h"

template <int n>
void SceneHolder<n>::draw()
{
    for (std::size_t i = 0; i < scenes.size(); i++)
    {
        scenes[i]->draw();
    }
}

template <int n>
void SceneHolder<n>::reloadVertices()
{
    for (std::size_t i = 0; i < scenes.size(); i++)
    {
        scenes[i]->reloadVertices();
    }
}

template <int n>
Shape<n> *SceneHolder<n>::getShape() const
{
    // shouldnt be called
    return nullptr;
}

template <int n>
void SceneHolder<n>::addScene(Scene<n> *scene)
{
    scenes.push_back(scene);
}

template <int n>
SceneHolder<n>::~SceneHolder()
{

    for (int i = 0; i < scenes.size(); i++)
    {
        delete scenes[i];
    }
}

template <int n>
void SceneHolder<n>::Rotate(float degrees)
{
    for (int i = 0; i < scenes.size(); i++)
    {
        scenes[i]->Rotate(degrees);
    }
}
template <int n>
void SceneHolder<n>::Scale(float scale)
{
    for (int i = 0; i < scenes.size(); i++)
    {
        scenes[i]->Scale(scale);
    }
}
template <int n>
void SceneHolder<n>::Translation(Direction dir, float step)
{
    for (int i = 0; i < scenes.size(); i++)
    {
        scenes[i]->Translation(dir, step);
    }
}

template <int n>
void SceneHolder<n>::select()
{
    for (int i = 0; i < scenes.size(); i++)
    {
        scenes[i]->select();
    }
}
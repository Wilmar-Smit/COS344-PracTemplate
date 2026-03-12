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
    this->selected = !this->selected;
    for (int i = 0; i < scenes.size(); i++)
    {
        scenes[i]->select();
    }
}

template <int n>
void SceneHolder<n>::deselect()
{
    this->selected = false;
    this->selectedScene = nullptr;

    for (int i = 0; i < (int)scenes.size(); i++)
    {
        scenes[i]->deselect();
    }
}

template <int n>
Scene<n> *SceneHolder<n>::selectNext()
{
 
    if (this->selected && !scenes.empty())
    {
        this->select(); 
        this->selectedScene = scenes[0];
        this->selectedScene->select(); 
        return this->selectedScene;
    }

 
    if (this->selectedScene != nullptr)
    {
        for (int i = 0; i < scenes.size(); i++)
        {
            if (scenes[i] == selectedScene)
            {
             
                if (i + 1 < scenes.size())
                {
                    this->selectedScene->select();
                    this->selectedScene = scenes[i + 1];
                    this->selectedScene->select(); 
                    return this->selectedScene;
                }
                break; 
            }
        }
    }


    if (this->parent)
    {
        if (this->selectedScene) this->selectedScene->select(); 
        this->selectedScene = nullptr;
        
 
        if (this->selected) this->select(); 
        
        return this->parent->selectNext();
    }


    if (this->selectedScene) this->selectedScene->select();
    this->selectedScene = nullptr;
    
    if (!this->selected) this->select();
    return this;
}
#include "TotalScene.h"

TotalScene::TotalScene() {}
TotalScene::~TotalScene()
{
    for (int i = 0; i < containers.size(); i++)
    {
        if (containers[i])
            delete containers[i];
    }
}

void TotalScene::draw()
{
    for (int i = 0; i < containers.size(); i++)
    {
        if (containers[i])
            containers[i]->draw();
    }
}
void TotalScene::addScene(complexSceneHolder *scene)
{
    containers.push_back(scene);
}
void TotalScene::Rotate(float degrees)
{
    for (int i = 0; i < containers.size(); i++)
    {
        if (containers[i])
            containers[i]->RotateZ(degrees);
    }
}
void TotalScene::RotateX(float degrees)
{
    for (int i = 0; i < containers.size(); i++)
    {
        if (containers[i])
            containers[i]->RotateX(degrees);
    }
}
void TotalScene::RotateY(float degrees)
{
    for (int i = 0; i < containers.size(); i++)
    {
        if (containers[i])
            containers[i]->RotateY(degrees);
    }
}
void TotalScene::RotateZ(float degrees)
{
    for (int i = 0; i < containers.size(); i++)
    {
        if (containers[i])
            containers[i]->RotateZ(degrees);
    }
}
void TotalScene::Scale(float scale)
{
    for (int i = 0; i < containers.size(); i++)
    {
        if (containers[i])
            containers[i]->Scale(scale);
    }
}
void TotalScene::Translation(Direction dir, float step)
{
    for (int i = 0; i < containers.size(); i++)
    {
        if (containers[i])
            containers[i]->Translation(dir, step);
    }
}

void TotalScene::select()
{
    if (!this->selected)
    {
        this->selected = true;
        for (int i = 0; i < containers.size(); i++)
        {
            if (containers[i])
                containers[i]->select();
        }
    }
    else
    {
        this->selected = false;
    }
}
void TotalScene::deselect()
{
    if (this->selected)
    {
        this->select();
    }
}
void TotalScene::setWireframeMode()
{
    for (int i = 0; i < containers.size(); i++)
    {
        if (containers[i])
            containers[i]->setWireframeMode();
    }
}
void TotalScene::setNormalMode()
{
    for (int i = 0; i < containers.size(); i++)
    {
        if (containers[i])
            containers[i]->setNormalMode();
    }
}

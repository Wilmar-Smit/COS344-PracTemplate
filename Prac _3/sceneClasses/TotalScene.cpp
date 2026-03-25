#include "TotalScene.h"

TotalScene::TotalScene()
{
}
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
        {
            
            containers[i]->useTotal = true;
            containers[i]->RotateZ(degrees);
            containers[i]->useTotal = false;
        }
    }
    
}
void TotalScene::RotateX(float degrees)
{
    for (int i = 0; i < containers.size(); i++)
    {
        if (containers[i])
        {
            
            containers[i]->useTotal = true;
            containers[i]->RotateX(degrees);
            containers[i]->useTotal = false;
        }
    }
    
}
void TotalScene::RotateY(float degrees)
{
    for (int i = 0; i < containers.size(); i++)
    {
        if (containers[i])
        {
            
            containers[i]->useTotal = true;
            containers[i]->RotateY(degrees);
            containers[i]->useTotal = false;
        }
    }
    
}
void TotalScene::RotateZ(float degrees)
{
    for (int i = 0; i < containers.size(); i++)
    {
        if (containers[i])
        {
            
            containers[i]->useTotal = true;
            containers[i]->RotateZ(degrees);
            containers[i]->useTotal = false;
        }
    }
    
}
void TotalScene::Scale(float scale)
{
    for (int i = 0; i < containers.size(); i++)
    {
        if (containers[i])
        {
            
            containers[i]->useTotal = true;
            containers[i]->Scale(scale);
            containers[i]->useTotal = false;
        }
    }
    
}
void TotalScene::Translation(Direction dir, float step)
{
    for (int i = 0; i < containers.size(); i++)
    {
        if (containers[i])
        {
            
            containers[i]->useTotal = true;
            containers[i]->Translation(dir, step);
            containers[i]->useTotal = false;
        }
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

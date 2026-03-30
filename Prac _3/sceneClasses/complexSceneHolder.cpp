#include "complexSceneHolder.h"

complexSceneHolder::complexSceneHolder()
{
}

complexSceneHolder::~complexSceneHolder()
{
    for (int i = 0; i < visitors.size(); i++)
    {
        if (visitors[i])
            delete visitors[i];
    }
}

void complexSceneHolder::draw()
{
    for (int i = 0; i < visitors.size(); i++)
    {
        if (visitors[i])
            visitors[i]->draw();
    }
}
void complexSceneHolder::reloadVertices()
{
    for (int i = 0; i < visitors.size(); i++)
    {
        if (visitors[i])
            visitors[i]->reloadVertices();
    }
}
Shape<3> *complexSceneHolder::getShape() const { return nullptr; }
void complexSceneHolder::addScene(DrawerVisitor *scene)
{
    visitors.push_back(scene);
}
void complexSceneHolder::Rotate(float degrees)
{

    RotateZ(degrees);
}
void complexSceneHolder::RotateX(float degrees)
{
}

void complexSceneHolder::RotateY(float degrees)
{
}

void complexSceneHolder::RotateZ(float degrees)
{
}

void complexSceneHolder::Scale(float scale)
{
}
void complexSceneHolder::Translation(Direction dir, float step)
{
}
 void complexSceneHolder::transform(Matrix<4, 4> &trans, bool toCenter)
{

}
void complexSceneHolder::select()
{
    if (!this->selected)
    {
        this->selected = true;
        for (int i = 0; i < visitors.size(); i++)
        {
            if (visitors[i])
                visitors[i]->select();
        }
    }
    else
    {
        this->selected = false;
    }
}
void complexSceneHolder::deselect()
{
    if (this->selected)
    {
        this->select();
    }
}
void complexSceneHolder::setWireframeMode()
{

    for (int i = 0; i < visitors.size(); i++)
    {
        if (visitors[i])
            visitors[i]->setWireframeMode();
    }
}
void complexSceneHolder::setNormalMode()
{
    for (int i = 0; i < visitors.size(); i++)
    {
        if (visitors[i])
            visitors[i]->setNormalMode();
    }
}
Scene *complexSceneHolder::selectNext() { return nullptr; }    // only complex objects can be selected not individual parts
Scene *complexSceneHolder::getIndex(int i) { return nullptr; } // only complex objects can be selected not individual parts

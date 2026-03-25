#include "complexSceneHolder.h"

complexSceneHolder::complexSceneHolder() {}
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

    for (int i = 0; i < visitors.size(); i++)
    {
        if (visitors[i])
            visitors[i]->RotateZ(degrees);
    }
}
void complexSceneHolder::RotateX(float degrees)
{
    for (int i = 0; i < visitors.size(); i++)
    {
        if (visitors[i])
            visitors[i]->RotateX(degrees);
    }
}

void complexSceneHolder::RotateY(float degrees)
{
    for (int i = 0; i < visitors.size(); i++)
    {
        if (visitors[i])
            visitors[i]->RotateY(degrees);
    }
}
void complexSceneHolder::RotateZ(float degrees)
{
    for (int i = 0; i < visitors.size(); i++)
    {
        if (visitors[i])
            visitors[i]->RotateZ(degrees);
    }
}
void complexSceneHolder::Scale(float scale)
{
    for (int i = 0; i < visitors.size(); i++)
    {
        if (visitors[i])
            visitors[i]->Scale(scale);
    }
}
void complexSceneHolder::Translation(Direction dir, float step)
{

    for (int i = 0; i < visitors.size(); i++)
    {
        if (visitors[i])
            visitors[i]->Translation(dir, step);
    }
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
void complexSceneHolder::transform(Matrix<4, 4> &trans, bool toCenter)
{
    for (int i = 0; i < visitors.size(); i++)
    {
        if (visitors[i])
            visitors[i]->transform(trans, toCenter);
    }
}

void complexSceneHolder::setGivenCenter(const Vector<3> &center)
{
    this->givenCenter = center;
    for (int i = 0; i < visitors.size(); i++)
    {
        if (visitors[i])
            visitors[i]->setGivenCenter(center);
    }
}

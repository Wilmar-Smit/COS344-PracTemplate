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

Shape *complexSceneHolder::getShape() const { return nullptr; }

void complexSceneHolder::addScene(Scene *scene)
{
    visitors.push_back(scene);
}

void complexSceneHolder::Rotate(float degrees, OrientationObject *orient)
{
    if (!orient) orient = this->orientation;

    for (auto *visitor : visitors)
        visitor->Rotate(degrees, orient);
}

void complexSceneHolder::RotateX(float degrees, OrientationObject *orient)
{
    if (!orient) orient = this->orientation;

    for (auto *visitor : visitors)
        visitor->RotateX(degrees, orient);
}

void complexSceneHolder::RotateY(float degrees, OrientationObject *orient)
{
    if (!orient) orient = this->orientation;

    for (auto *visitor : visitors)
        visitor->RotateY(degrees, orient);
}

void complexSceneHolder::RotateZ(float degrees, OrientationObject *orient)
{
    if (!orient) orient = this->orientation;

    for (auto *visitor : visitors)
        visitor->RotateZ(degrees, orient);
}

void complexSceneHolder::Scale(float scale, OrientationObject *orient)
{
    if (!orient) orient = this->orientation;

    for (auto *visitor : visitors)
        visitor->Scale(scale, orient);
}

void complexSceneHolder::Translation(Direction dir, float step, OrientationObject *orient)
{
    if (!orient) orient = this->orientation;

    for (auto *visitor : visitors)
        visitor->Translation(dir, step, orient);
}

Matrix<4, 4> complexSceneHolder::transform(Matrix<4, 4> &trans, bool toCenter, OrientationObject *orient)
{
    if (!orient) orient = this->orientation;

    Matrix<4, 4> mat;
    for (auto *visitor : visitors)
        mat = visitor->transform(trans, toCenter, orient);

    if (this->orientation)
        this->orientation->update(mat, toCenter, orient);

    return mat;
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

Scene *complexSceneHolder::selectNext() { return nullptr; }
Scene *complexSceneHolder::getIndex(int i) { return this->visitors[i]; }

void complexSceneHolder::RotateArbitrary(float degrees, OrientationObject *orient)
{
    if (!orient) orient = this->orientation;

    for (auto *visitor : visitors)
        visitor->RotateArbitrary(degrees, orient);
}

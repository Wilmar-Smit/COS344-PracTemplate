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
    for (int i = 0; i < cutouts.size(); i++)
    {
        if (cutouts[i])
            delete cutouts[i];
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

void complexSceneHolder::drawCutoutShapes()
{
    for (int i = 0; i < cutouts.size(); i++)
    {
        if (cutouts[i])
            cutouts[i]->draw();
    }
    for (int i = 0; i < visitors.size(); i++)
    {
        if (visitors[i])
            visitors[i]->drawCutoutShapes();
    }
}

void complexSceneHolder::reloadVertices()
{
    for (int i = 0; i < visitors.size(); i++)
    {
        if (visitors[i])
            visitors[i]->reloadVertices();
    }
    for (int i = 0; i < cutouts.size(); i++)
    {
        if (cutouts[i])
            cutouts[i]->reloadVertices();
    }
}

Shape<3> *complexSceneHolder::getShape() const { return nullptr; }

void complexSceneHolder::addScene(Scene *scene)
{
    visitors.push_back(scene);
}

void complexSceneHolder::addCutoutShape(Scene *scene)
{
    cutouts.push_back(scene);
}

void complexSceneHolder::Rotate(float degrees, OrientationObject *orient)
{
    if (!orient) orient = this->orientation;

    for (auto *visitor : visitors)
        visitor->Rotate(degrees, orient);

    for (auto *cutout : cutouts)
        cutout->Rotate(degrees, orient);
}

void complexSceneHolder::RotateX(float degrees, OrientationObject *orient)
{
    if (!orient) orient = this->orientation;

    for (auto *visitor : visitors)
        visitor->RotateX(degrees, orient);

    for (auto *cutout : cutouts)
        cutout->RotateX(degrees, orient);
}

void complexSceneHolder::RotateY(float degrees, OrientationObject *orient)
{
    if (!orient) orient = this->orientation;

    for (auto *visitor : visitors)
        visitor->RotateY(degrees, orient);

    for (auto *cutout : cutouts)
        cutout->RotateY(degrees, orient);
}

void complexSceneHolder::RotateZ(float degrees, OrientationObject *orient)
{
    if (!orient) orient = this->orientation;

    for (auto *visitor : visitors)
        visitor->RotateZ(degrees, orient);

    for (auto *cutout : cutouts)
        cutout->RotateZ(degrees, orient);
}

void complexSceneHolder::Scale(float scale, OrientationObject *orient)
{
    if (!orient) orient = this->orientation;

    for (auto *visitor : visitors)
        visitor->Scale(scale, orient);

    for (auto *cutout : cutouts)
        cutout->Scale(scale, orient);
}

void complexSceneHolder::Translation(Direction dir, float step, OrientationObject *orient)
{
    if (!orient) orient = this->orientation;

    for (auto *visitor : visitors)
        visitor->Translation(dir, step, orient);

    for (auto *cutout : cutouts)
        cutout->Translation(dir, step, orient);
}

Matrix<4, 4> complexSceneHolder::transform(Matrix<4, 4> &trans, bool toCenter, OrientationObject *orient)
{
    if (!orient) orient = this->orientation;

    Matrix<4, 4> mat;
    for (auto *visitor : visitors)
        mat = visitor->transform(trans, toCenter, orient);

    for (auto *cutout : cutouts)
        mat = cutout->transform(trans, toCenter, orient);

    if (this->orientation)
        this->orientation->update(mat, toCenter, orient);

    return mat;
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
        for (int i = 0; i < cutouts.size(); i++)
        {
            if (cutouts[i])
                cutouts[i]->select();
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
    for (int i = 0; i < cutouts.size(); i++)
    {
        if (cutouts[i])
            cutouts[i]->setWireframeMode();
    }
}

void complexSceneHolder::setNormalMode()
{
    for (int i = 0; i < visitors.size(); i++)
    {
        if (visitors[i])
            visitors[i]->setNormalMode();
    }
    for (int i = 0; i < cutouts.size(); i++)
    {
        if (cutouts[i])
            cutouts[i]->setNormalMode();
    }
}

Scene *complexSceneHolder::selectNext() { return nullptr; }
Scene *complexSceneHolder::getIndex(int i) { return this->visitors[i]; }

void complexSceneHolder::RotateArbitrary(float degrees, OrientationObject *orient)
{
    if (!orient) orient = this->orientation;

    for (auto *visitor : visitors)
        visitor->RotateArbitrary(degrees, orient);

    for (auto *cutout : cutouts)
        cutout->RotateArbitrary(degrees, orient);
}

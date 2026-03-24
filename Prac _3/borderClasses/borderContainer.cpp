#include "borderContainer.h"

BorderContainer::BorderContainer(borderStub *border)
    : borderStub(*border) // original size based on the border given
{
}

Vector<3> *BorderContainer::Collision(borderStub *border)
{
    Vector<3> *vec = borderStub::Collision(border);
    if (vec)
    {
        delete vec;
        for (int i = 0; i < this->boxes.size(); i++)
        {
            vec = boxes[i]->Collision(border);
            if (vec)
            {
                return vec; // collides if shape == coords we need cascaded up
            }
        }
    }
    else
        return nullptr;
}

BorderContainer::~BorderContainer()
{
    for (int i = 0; i < boxes.size(); i++)
    {
        delete boxes[i];
    }
    if (myObserver)
        delete myObserver;
}

void BorderContainer::addContainer(borderStub *border)
{
    boxes.push_back(border);
    updateSize();
    if (!this->myObserver)
    {
        myObserver = new borderObserver(this);
    }

    border->attach(myObserver);
}
void BorderContainer::updateSize()
{ // unfortunately needs to check everything since boxes grow and shrink cant just be based on the
    float minX = boxes[0]->frontBottomLeft[0];
    float maxX = boxes[0]->frontBottomRight[0];
    float minY = boxes[0]->frontBottomLeft[1];
    float maxY = boxes[0]->frontTopLeft[1];
    float minZ = boxes[0]->frontBottomLeft[2];
    float maxZ = boxes[0]->backBottomLeft[2];
    for (int i = 0; i < boxes.size(); ++i)
    {
        borderStub *b = boxes[i];

        minX = std::min(minX, b->frontBottomLeft[0]);
        maxX = std::max(maxX, b->frontBottomRight[0]);
        minY = std::min(minY, b->frontBottomLeft[1]);
        maxY = std::max(maxY, b->frontTopLeft[1]);
        minZ = std::min(minZ, b->frontBottomLeft[2]);
        maxZ = std::max(maxZ, b->backBottomLeft[2]);
    }

    // Recalculate this container’s own corners
    frontBottomLeft = Vector<3>({minX, minY, minZ});
    frontBottomRight = Vector<3>({maxX, minY, minZ});
    frontTopLeft = Vector<3>({minX, maxY, minZ});
    frontTopRight = Vector<3>({maxX, maxY, minZ});

    backBottomLeft = Vector<3>({minX, minY, maxZ});
    backBottomRight = Vector<3>({maxX, minY, maxZ});
    backTopLeft = Vector<3>({minX, maxY, maxZ});
    backTopRight = Vector<3>({maxX, maxY, maxZ});
}
void BorderContainer::notify()
{ // called by my observer
    if (obs)
        obs->notify();
    this->updateSize();
}
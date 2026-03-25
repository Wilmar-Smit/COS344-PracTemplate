#include "borderVisitor.h"
#include "borderStub.h"

BorderVisitor::BorderVisitor()
{
}

BorderVisitor::~BorderVisitor()
{
}
void BorderVisitor::visitRun(_3DShape *shape, borderStub *border)
{
    border->recalculateCol(shape);
}
void BorderVisitor::visitRun(Cuboid *shape, borderStub *border)
{
    border->recalculateCol(shape);
}
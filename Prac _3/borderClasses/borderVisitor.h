#ifndef BORDERVISITOR_H
#define BORDERVISITOR_H

class _3DShape;
class Cuboid;
class borderStub;
class BorderVisitor
{
private:
public:
    BorderVisitor();
    ~BorderVisitor();
    static void visitRun(_3DShape *, borderStub *);
    static void visitRun(Cuboid *, borderStub *);
};

#endif

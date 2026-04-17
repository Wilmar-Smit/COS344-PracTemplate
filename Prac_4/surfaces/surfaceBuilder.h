#ifndef SURFACE_BUILDER_H
#define SURFACE_BUILDER_H

#include "surface.h"
#include "Vector.h"

class SurfaceBuilder
{
protected:
    Surface *surface;

public:
    static const Vector<4> Red;
    static const Vector<4> Green;
    static const Vector<4> Blue;
    static const Vector<4> Yellow;
    static const Vector<4> Cyan;
    static const Vector<4> Magenta;
    static const Vector<4> Orange;
    static const Vector<4> Purple;
    static const Vector<4> White;
    static const Vector<4> Grey;
    static const Vector<4> Maroon;
    static const Vector<4> Pink;
    static const Vector<4> Peach;
    static const Vector<4> Brown;
    static const Vector<4> DarkBrown;
    static const Vector<4> Black;
    static const Vector<4> invisible;

    SurfaceBuilder();
    virtual ~SurfaceBuilder();

    SurfaceBuilder &setBaseColor(const Vector<4> &color);
    SurfaceBuilder &setAmbient(float k);
    SurfaceBuilder &setDiffuse(float k);
    SurfaceBuilder &setSpecular(float k);
    SurfaceBuilder &setShininess(float s);

    virtual Surface build();
};

class RedBuilder : public SurfaceBuilder
{
public:
    RedBuilder();
};
class GreenBuilder : public SurfaceBuilder
{
public:
    GreenBuilder();
};
class BlueBuilder : public SurfaceBuilder
{
public:
    BlueBuilder();
};
class YellowBuilder : public SurfaceBuilder
{
public:
    YellowBuilder();
};
class CyanBuilder : public SurfaceBuilder
{
public:
    CyanBuilder();
};
class MagentaBuilder : public SurfaceBuilder
{
public:
    MagentaBuilder();
};
class OrangeBuilder : public SurfaceBuilder
{
public:
    OrangeBuilder();
};
class PurpleBuilder : public SurfaceBuilder
{
public:
    PurpleBuilder();
};
class WhiteBuilder : public SurfaceBuilder
{
public:
    WhiteBuilder();
};
class GreyBuilder : public SurfaceBuilder
{
public:
    GreyBuilder();
};
class MaroonBuilder : public SurfaceBuilder
{
public:
    MaroonBuilder();
};
class PinkBuilder : public SurfaceBuilder
{
public:
    PinkBuilder();
};
class PeachBuilder : public SurfaceBuilder
{
public:
    PeachBuilder();
};
class BrownBuilder : public SurfaceBuilder
{
public:
    BrownBuilder();
};
class DarkBrownBuilder : public SurfaceBuilder
{
public:
    DarkBrownBuilder();
};
class BlackBuilder : public SurfaceBuilder
{
public:
    BlackBuilder();
};

class ChromeBuilder : public SurfaceBuilder
{
public:
    ChromeBuilder();
};
class MatteRubberBuilder : public SurfaceBuilder
{
public:
    MatteRubberBuilder();
};
class PolishedGoldBuilder : public SurfaceBuilder
{
public:
    PolishedGoldBuilder();
};

#endif
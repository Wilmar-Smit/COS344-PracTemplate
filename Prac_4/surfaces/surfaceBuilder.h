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
    virtual Surface build() override;
};
class GreenBuilder : public SurfaceBuilder
{
public:
    GreenBuilder();
    virtual Surface build() override;
};
class BlueBuilder : public SurfaceBuilder
{
public:
    BlueBuilder();
    virtual Surface build() override;
};
class YellowBuilder : public SurfaceBuilder
{
public:
    YellowBuilder();
    virtual Surface build() override;
};
class CyanBuilder : public SurfaceBuilder
{
public:
    CyanBuilder();
    virtual Surface build() override;
};
class MagentaBuilder : public SurfaceBuilder
{
public:
    MagentaBuilder();
    virtual Surface build() override;
};
class OrangeBuilder : public SurfaceBuilder
{
public:
    OrangeBuilder();
    virtual Surface build() override;
};
class PurpleBuilder : public SurfaceBuilder
{
public:
    PurpleBuilder();
    virtual Surface build() override;
};
class WhiteBuilder : public SurfaceBuilder
{
public:
    WhiteBuilder();
    virtual Surface build() override;
};
class GreyBuilder : public SurfaceBuilder
{
public:
    GreyBuilder();
    virtual Surface build() override;
};
class MaroonBuilder : public SurfaceBuilder
{
public:
    MaroonBuilder();
    virtual Surface build() override;
};
class PinkBuilder : public SurfaceBuilder
{
public:
    PinkBuilder();
    virtual Surface build() override;
};
class PeachBuilder : public SurfaceBuilder
{
public:
    PeachBuilder();
    virtual Surface build() override;
};
class BrownBuilder : public SurfaceBuilder
{
public:
    BrownBuilder();
    virtual Surface build() override;
};
class DarkBrownBuilder : public SurfaceBuilder
{
public:
    DarkBrownBuilder();
    virtual Surface build() override;
};
class BlackBuilder : public SurfaceBuilder
{
public:
    BlackBuilder();
    virtual Surface build() override;
};

class ChromeBuilder : public SurfaceBuilder
{
public:
    ChromeBuilder();
    virtual Surface build() override;
};
class MatteRubberBuilder : public SurfaceBuilder
{
public:
    MatteRubberBuilder();
    virtual Surface build() override;
};
class PolishedGoldBuilder : public SurfaceBuilder
{
public:
    PolishedGoldBuilder();
    virtual Surface build() override;
};

#endif
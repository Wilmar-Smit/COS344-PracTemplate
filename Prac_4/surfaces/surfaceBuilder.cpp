#include "surfaceBuilder.h"

const Vector<4> SurfaceBuilder::Red{0.65f, 0.18f, 0.18f, 1.0f};
const Vector<4> SurfaceBuilder::Green{0.168f, 0.56f, 0.168f, 1.0f}; // 0.24 * 0.7 approx
const Vector<4> SurfaceBuilder::Blue{0.12f, 0.24f, 0.7f, 1.0f};
const Vector<4> SurfaceBuilder::Yellow{0.72f, 0.65f, 0.20f, 1.0f};
const Vector<4> SurfaceBuilder::Cyan{0.18f, 0.45f, 0.45f, 1.0f};
const Vector<4> SurfaceBuilder::Magenta{0.48f, 0.20f, 0.48f, 1.0f};
const Vector<4> SurfaceBuilder::Orange{0.68f, 0.40f, 0.16f, 1.0f};
const Vector<4> SurfaceBuilder::Purple{0.32f, 0.20f, 0.42f, 1.0f};
const Vector<4> SurfaceBuilder::White{0.90f, 0.90f, 0.86f, 1.0f};
const Vector<4> SurfaceBuilder::Grey{0.38f, 0.38f, 0.38f, 1.0f};
const Vector<4> SurfaceBuilder::Maroon{0.38f, 0.10f, 0.10f, 1.0f};
const Vector<4> SurfaceBuilder::Pink{0.68f, 0.50f, 0.54f, 1.0f};
const Vector<4> SurfaceBuilder::Peach{0.79f, 0.72f, 0.62f, 1.0f};
const Vector<4> SurfaceBuilder::Brown{0.40f, 0.25f, 0.12f, 1.0f};
const Vector<4> SurfaceBuilder::DarkBrown{0.25f, 0.16f, 0.08f, 1.0f};
const Vector<4> SurfaceBuilder::Black{0.05f, 0.05f, 0.05f, 1.0f};
const Vector<4> SurfaceBuilder::invisible{0.90f, 0.90f, 0.86f, 0.0f};

SurfaceBuilder::SurfaceBuilder()
{
    this->surface = new Surface();
}

SurfaceBuilder::~SurfaceBuilder()
{
    delete this->surface;
}

SurfaceBuilder &SurfaceBuilder::setBaseColor(const Vector<4> &color)
{
    if (this->surface)
    {
        this->surface->setBaseColor(color);
    }
    return *this;
}

SurfaceBuilder &SurfaceBuilder::setAmbient(float k)
{
    if (this->surface)
    {
        this->surface->setAmbientK(k);
    }
    return *this;
}

SurfaceBuilder &SurfaceBuilder::setDiffuse(float k)
{
    if (this->surface)
    {
        this->surface->setDiffuseK(k);
    }
    return *this;
}

SurfaceBuilder &SurfaceBuilder::setSpecular(float k)
{
    if (this->surface)
    {
        this->surface->setSpecularK(k);
    }
    return *this;
}

SurfaceBuilder &SurfaceBuilder::setShininess(float s)
{
    if (this->surface)
    {
        this->surface->setShininess(s);
    }
    return *this;
}

Surface SurfaceBuilder::build()
{
    if (this->surface)
    {
        return *(this->surface);
    }

    return Surface();
}

RedBuilder::RedBuilder() : SurfaceBuilder()
{
    this->setBaseColor(SurfaceBuilder::Red)
        .setAmbient(0.2f)
        .setDiffuse(0.7f)
        .setSpecular(0.4f)
        .setShininess(32.0f);
}

GreenBuilder::GreenBuilder() : SurfaceBuilder()
{
    this->setBaseColor(SurfaceBuilder::Green)
        .setAmbient(0.2f)
        .setDiffuse(0.7f)
        .setSpecular(0.4f)
        .setShininess(32.0f);
}

BlueBuilder::BlueBuilder() : SurfaceBuilder()
{
    this->setBaseColor(SurfaceBuilder::Blue)
        .setAmbient(0.2f)
        .setDiffuse(0.7f)
        .setSpecular(0.4f)
        .setShininess(32.0f);
}

YellowBuilder::YellowBuilder() : SurfaceBuilder()
{
    this->setBaseColor(SurfaceBuilder::Yellow)
        .setAmbient(0.2f)
        .setDiffuse(0.7f)
        .setSpecular(0.4f)
        .setShininess(32.0f);
}

CyanBuilder::CyanBuilder() : SurfaceBuilder()
{
    this->setBaseColor(SurfaceBuilder::Cyan)
        .setAmbient(0.2f)
        .setDiffuse(0.7f)
        .setSpecular(0.4f)
        .setShininess(32.0f);
}

MagentaBuilder::MagentaBuilder() : SurfaceBuilder()
{
    this->setBaseColor(SurfaceBuilder::Magenta)
        .setAmbient(0.2f)
        .setDiffuse(0.7f)
        .setSpecular(0.4f)
        .setShininess(32.0f);
}

OrangeBuilder::OrangeBuilder() : SurfaceBuilder()
{
    this->setBaseColor(SurfaceBuilder::Orange)
        .setAmbient(0.2f)
        .setDiffuse(0.7f)
        .setSpecular(0.4f)
        .setShininess(32.0f);
}

PurpleBuilder::PurpleBuilder() : SurfaceBuilder()
{
    this->setBaseColor(SurfaceBuilder::Purple)
        .setAmbient(0.2f)
        .setDiffuse(0.7f)
        .setSpecular(0.4f)
        .setShininess(32.0f);
}

WhiteBuilder::WhiteBuilder() : SurfaceBuilder()
{
    this->setBaseColor(SurfaceBuilder::White)
        .setAmbient(0.2f)
        .setDiffuse(0.7f)
        .setSpecular(0.4f)
        .setShininess(32.0f);
}

GreyBuilder::GreyBuilder() : SurfaceBuilder()
{
    this->setBaseColor(SurfaceBuilder::Grey)
        .setAmbient(0.2f)
        .setDiffuse(0.7f)
        .setSpecular(0.4f)
        .setShininess(32.0f);
}

MaroonBuilder::MaroonBuilder() : SurfaceBuilder()
{
    this->setBaseColor(SurfaceBuilder::Maroon)
        .setAmbient(0.2f)
        .setDiffuse(0.7f)
        .setSpecular(0.4f)
        .setShininess(32.0f);
}

PinkBuilder::PinkBuilder() : SurfaceBuilder()
{
    this->setBaseColor(SurfaceBuilder::Pink)
        .setAmbient(0.2f)
        .setDiffuse(0.7f)
        .setSpecular(0.4f)
        .setShininess(32.0f);
}

PeachBuilder::PeachBuilder() : SurfaceBuilder()
{
    this->setBaseColor(SurfaceBuilder::Peach)
        .setAmbient(0.2f)
        .setDiffuse(0.7f)
        .setSpecular(0.4f)
        .setShininess(32.0f);
}

BrownBuilder::BrownBuilder() : SurfaceBuilder()
{
    this->setBaseColor(SurfaceBuilder::Brown)
        .setAmbient(0.2f)
        .setDiffuse(0.7f)
        .setSpecular(0.4f)
        .setShininess(32.0f);
}

DarkBrownBuilder::DarkBrownBuilder() : SurfaceBuilder()
{
    this->setBaseColor(SurfaceBuilder::DarkBrown)
        .setAmbient(0.2f)
        .setDiffuse(0.7f)
        .setSpecular(0.4f)
        .setShininess(32.0f);
}

BlackBuilder::BlackBuilder() : SurfaceBuilder()
{
    this->setBaseColor(SurfaceBuilder::Black)
        .setAmbient(0.1f)
        .setDiffuse(0.8f)
        .setSpecular(0.2f)
        .setShininess(10.0f);
}

ChromeBuilder::ChromeBuilder() : SurfaceBuilder()
{
    this->setBaseColor(SurfaceBuilder::Grey)
        .setAmbient(0.1f)
        .setDiffuse(0.3f)
        .setSpecular(1.0f)
        .setShininess(128.0f);
}

MatteRubberBuilder::MatteRubberBuilder() : SurfaceBuilder()
{
    this->setBaseColor(SurfaceBuilder::Black)
        .setAmbient(0.05f)
        .setDiffuse(0.95f)
        .setSpecular(0.05f)
        .setShininess(2.0f);
}

PolishedGoldBuilder::PolishedGoldBuilder() : SurfaceBuilder()
{
    this->setBaseColor(SurfaceBuilder::Yellow)
        .setAmbient(0.3f)
        .setDiffuse(0.5f)
        .setSpecular(0.9f)
        .setShininess(64.0f);
}
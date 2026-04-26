#include "assets.h"
#include "../sceneClasses/drawerVisitor.h"
#include <iostream>

#include <stb/stb_image.h>

static GLuint loadTexture(const char *filename)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (data)
    {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0,
                     format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "failed to load tex " << filename << std::endl;
    }
    stbi_image_free(data);

    return textureID;
}

complexSceneHolder *setupScene(Colour squareColor, Colour sphereColor, bool enableTexture, bool enableDisplacement, bool enableAlpha, float alphaValue, int squareResolution, int sphereResolution)
{
    complexSceneHolder *scene = new complexSceneHolder();

    MultiFacedSurface *mult = new MultiFacedSurface({0, 0, 0}, 3, 3, squareResolution, squareColor);
    mult->setLightAffected(true);
    OrientationObject *obj = mult->getOrientation();
    scene->SetMyOrientation(obj);

    DrawerVisitor *squareDwr = new DrawerVisitor(mult);
    squareDwr->RotateX(70);
    squareDwr->Translation(Direction::down, 1);

    scene->addScene(squareDwr);

    Sphere *sphere = new Sphere({0, 0, 0}, 1, sphereResolution, sphereResolution, sphereColor, 4);
    sphere->setLightAffected(true);
    Vector<4> baseCol = SurfaceBuilder::buildColour(sphereColor);
    baseCol[3] = alphaValue; // Always set alpha for use in shader

    if (enableAlpha)
    {
        GLuint alphaTex = loadTexture("textures/alpha.png");
        sphere->getSurface().setAlphaTexture(alphaTex);
        sphere->getSurface().enableAlphaTexture(true);
    }
    else
    {
        sphere->getSurface().enableAlphaTexture(false);
    }

    sphere->getSurface().setBaseColor(baseCol);

    if (enableTexture)
    {
        GLuint sphereTex = loadTexture("textures/ColTex.png");
        sphere->getSurface().setColorTexture(sphereTex);
        sphere->getSurface().enableColorTexture(true);
    }
    else
    {
        sphere->getSurface().enableColorTexture(false);
    }

    if (enableDisplacement)
    {
        GLuint displacementTex = loadTexture("textures/Displacement.png");
        sphere->getSurface().setDisplacementTexture(displacementTex);
        sphere->getSurface().enableDisplacementTexture(true);
    }
    else
    {
        sphere->getSurface().enableDisplacementTexture(false);
    }

    DrawerVisitor *sphereDwr = new DrawerVisitor(sphere);
    sphereDwr->SetMyOrientation(obj);
    scene->addScene(sphereDwr);

    return scene;
}

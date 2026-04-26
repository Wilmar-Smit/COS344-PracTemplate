#ifndef ASSETS_H
#define ASSETS_H

#include "../sceneClasses/complexSceneHolder.h"
#include "../surfaces/surfaceBuilder.h"

/**
 * Creates and returns a new configured complexSceneHolder.
 * This function resets the scene to fixed coordinates and applies the given parameters.
 */
complexSceneHolder* setupScene(Colour squareColor, Colour sphereColor, bool enableTexture, bool enableDisplacement, bool enableAlpha, float alphaValue, int squareResolution, int sphereResolution);

#endif

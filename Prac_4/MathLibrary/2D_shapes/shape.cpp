#include "Shape.h"
#include "../../camera/camera.h"
#include "../../lights/globalLights.h"

Surface Shape::buildSurfaceFromColour(Colour col)
{
    switch (col)
    {
    case Colour::Red:
    {

        RedBuilder builder;

        return builder.build();
    }
    case Colour::Green:
    {
        GreenBuilder builder;
        return builder.build();
    }
    case Colour::Blue:
    {
        BlueBuilder builder;
        return builder.build();
    }
    case Colour::Yellow:
    {
        YellowBuilder builder;
        return builder.build();
    }
    case Colour::Cyan:
    {
        CyanBuilder builder;
        return builder.build();
    }
    case Colour::Magenta:
    {
        MagentaBuilder builder;
        return builder.build();
    }
    case Colour::Orange:
    {
        OrangeBuilder builder;
        return builder.build();
    }
    case Colour::Purple:
    {
        PurpleBuilder builder;
        return builder.build();
    }
    case Colour::White:
    {
        WhiteBuilder builder;
        return builder.build();
    }
    case Colour::Grey:
    {
        GreyBuilder builder;
        return builder.build();
    }
    case Colour::Maroon:
    {
        MaroonBuilder builder;
        return builder.build();
    }
    case Colour::Pink:
    {
        PinkBuilder builder;
        return builder.build();
    }
    case Colour::Peach:
    {
        PeachBuilder builder;
        return builder.build();
    }
    case Colour::Brown:
    {
        BrownBuilder builder;
        return builder.build();
    }
    case Colour::DarkBrown:
    {
        DarkBrownBuilder builder;
        return builder.build();
    }
    case Colour::Black:
    {
        BlackBuilder builder;
        return builder.build();
    }
    case Colour::Invisible:
    {
        SurfaceBuilder builder;
        return builder.setBaseColor(SurfaceBuilder::invisible)
            .setAmbient(0.0f)
            .setDiffuse(0.0f)
            .setSpecular(0.0f)
            .setShininess(1.0f)
            .build();
    }
    case Colour::Chrome:
    {
        ChromeBuilder builder;
        return builder.build();
    }
    case Colour::Gold:
    {
        PolishedGoldBuilder builder;
        return builder.build();
    }
    }

    WhiteBuilder fallbackBuilder;
    return fallbackBuilder.build();
}
float *Shape::exportValues()
{
    int shapeSides = getNumPoints() / getN();
    // +2 for UVs
    int totalValues = shapeSides * (getN() + 4 + 2);
    float *retValues = new float[totalValues];
    float *ShapeCoords = getPoints();
    const Matrix<4, 4> &cameraMatrix = Camera::getInstance().getMatrix();

    const std::vector<Vector<2>> uvs = this->calculateUV();

    std::vector<Vector<3>> points;
    points.reserve(shapeSides);
    for (int i = 0; i < shapeSides; i++)
    {
        int base = i * getN();
        points.push_back(Vector<3>({ShapeCoords[base], ShapeCoords[base + 1], ShapeCoords[base + 2]}));
    }

    Surface litSurface = this->surface;
    if (points.size() >= 3)
    {
        litSurface.calculateNormal(points[0], points[1], points[2]);
    }

    std::vector<Vector<4>> pointColours;
    pointColours.reserve(points.size());

    const auto &lights = GlobalLights::getInstance().getLights();
    for (int i = 0; i < points.size(); i++)
    {
        if (lights.empty())
        {
            pointColours.push_back(litSurface.getBaseColor());
            continue;
        }

        Vector<4> litColour({0.0f, 0.0f, 0.0f, litSurface.getBaseColor()[3]});
        for (Light *light : lights)
        {
            Vector<4> lightContribution = light->calculateIlluminations(points[i], litSurface);
            for (int c = 0; c < 3; c++)
            {
                litColour[c] += lightContribution[c];
            }
        }
        pointColours.push_back(litColour);
    }

    int offset = 0;

    for (int row = 0; row < shapeSides; row++)
    {
        Vector<3> point = points[row];
        Vector<4> homogeneousPoint({point[0], point[1], point[2], 1.0f});
        homogeneousPoint = cameraMatrix * ((Matrix<4, 1>)homogeneousPoint);

        float w = homogeneousPoint[3];
        for (int i = 0; i < getN(); i++)
        {
            retValues[offset++] = (w != 0.0f) ? (homogeneousPoint[i] / w) : homogeneousPoint[i];
        }

        for (int i = 0; i < 4; i++)
        {
            retValues[offset++] = pointColours[row][i];
        }

        if (this->surface.isColorTextureEnabled())
        {
            retValues[offset++] = uvs[row][0];
            retValues[offset++] = uvs[row][1];
        }
        else
        {
            retValues[offset++] = 0;
            retValues[offset++] = 0;
        }
    }

    delete[] ShapeCoords;
    return retValues;
}

float *Shape::exportWireframe()
{
    int shapeSides = getNumPoints() / getN();
    float *ShapeCoords = getPoints();
    const Matrix<4, 4> &cameraMatrix = Camera::getInstance().getMatrix();

    // Each side contributes 2 vertices (start + end). For quads, add one diagonal.
    int extraSegmentVertices = (shapeSides == 4) ? 2 : 0;
    int totalValues = (shapeSides * 2 + extraSegmentVertices) * (getN() + 4);
    float *retValues = new float[totalValues];

    int offset = 0;
    int count = 0;
    Vector<4> baseColor = surface.getBaseColor();

    for (int row = 0; row < shapeSides; row++)
    {
        // Current vertex
        Vector<4> startPoint({ShapeCoords[count], ShapeCoords[count + 1], ShapeCoords[count + 2], 1.0f});
        startPoint = cameraMatrix * ((Matrix<4, 1>)startPoint);
        float wStart = startPoint[3];

        for (int i = 0; i < getN(); i++)
            retValues[offset++] = (wStart != 0.0f) ? (startPoint[i] / wStart) : startPoint[i];
        for (int i = 0; i < 4; i++)
            retValues[offset++] = baseColor[i];

        // Next vertex
        int next = ((row + 1) % shapeSides) * getN();
        Vector<4> endPoint({ShapeCoords[next], ShapeCoords[next + 1], ShapeCoords[next + 2], 1.0f});
        endPoint = cameraMatrix * ((Matrix<4, 1>)endPoint);
        float wEnd = endPoint[3];

        for (int i = 0; i < getN(); i++)
            retValues[offset++] = (wEnd != 0.0f) ? (endPoint[i] / wEnd) : endPoint[i];
        for (int i = 0; i < 4; i++)
            retValues[offset++] = baseColor[i];

        count += getN();
    }

    // For rectangles/squares, add a diagonal (first to third vertex) to form two triangles.
    if (shapeSides == 4)
    {
        int first = 0;
        int third = 2 * getN();

        Vector<4> firstPoint({ShapeCoords[first], ShapeCoords[first + 1], ShapeCoords[first + 2], 1.0f});
        firstPoint = cameraMatrix * ((Matrix<4, 1>)firstPoint);
        float wFirst = firstPoint[3];

        for (int i = 0; i < getN(); i++)
            retValues[offset++] = (wFirst != 0.0f) ? (firstPoint[i] / wFirst) : firstPoint[i];
        for (int i = 0; i < 4; i++)
            retValues[offset++] = baseColor[i];

        Vector<4> thirdPoint({ShapeCoords[third], ShapeCoords[third + 1], ShapeCoords[third + 2], 1.0f});
        thirdPoint = cameraMatrix * ((Matrix<4, 1>)thirdPoint);
        float wThird = thirdPoint[3];

        for (int i = 0; i < getN(); i++)
            retValues[offset++] = (wThird != 0.0f) ? (thirdPoint[i] / wThird) : thirdPoint[i];
        for (int i = 0; i < 4; i++)
            retValues[offset++] = baseColor[i];
    }

    delete[] ShapeCoords;
    return retValues;
}

int Shape::getWireframeVertexCount() const
{
    int shapeSides = getNumPoints() / getN();
    int extraSegmentVertices = (shapeSides == 4) ? 2 : 0;
    return shapeSides * 2 + extraSegmentVertices;
}

Vector<4> Shape::getColourVec(Colour col)
{
    return buildSurfaceFromColour(col).getBaseColor();
}
Shape::Shape() : surface() {}

Shape::Shape(Colour col)
{
    this->surface = buildSurfaceFromColour(col);
}
Vector<4> Shape::getColourPas()
{
    Vector<4> ret;
    float mixFactor = 0.3f;
    Vector<4> baseColor = this->surface.getBaseColor();
    for (int i = 0; i < 4; i++)
    {
        if (i < 3)
        {
            ret[i] = (baseColor[i] * (1.0f - mixFactor)) + (1.0f * mixFactor);
        }
        else
        {
            ret[i] = baseColor[i];
        }
    }
    return ret;
}

std::vector<Vector<4>> Shape::getHomogeneousVectors()
{
    auto originalPoints = getVectors();
    std::vector<Vector<4>> homogeneousPoints;
    homogeneousPoints.reserve(originalPoints.size());

    for (auto &point : originalPoints)
    {
        Vector<4> homogeneousPoint;
        for (int i = 0; i < this->n; i++)
            homogeneousPoint[i] = point[i];
        homogeneousPoint[this->n] = 1.0f;

        homogeneousPoints.push_back(homogeneousPoint);
    }
    return homogeneousPoints;
}

void Shape::applyMatrix(const Matrix<4, 4> &transformationMatrix, bool per)
{
    auto originalPoints = getVectors();

    for (auto &point : originalPoints)
    {
        Vector<4> homogeneousPoint;
        for (int i = 0; i < this->n; i++)
            homogeneousPoint[i] = point[i];
        homogeneousPoint[this->n] = 1.0f;

        // Apply transformation
        homogeneousPoint = transformationMatrix * ((Matrix<4, 1>)homogeneousPoint);

        if (per) // only do perspective divide if flagged
        {
            if (homogeneousPoint[3] != 0.0f)
            {
                for (int i = 0; i < this->n; i++)
                    point[i] = homogeneousPoint[i] / homogeneousPoint[3];
            }
        }
        else
        {
            for (int i = 0; i < this->n; i++)
                point[i] = homogeneousPoint[i];
        }
    }

    setVectors(originalPoints);
}

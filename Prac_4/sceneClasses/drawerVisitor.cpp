#include "drawerVisitor.h"
void DrawerVisitor::rebuildGpuBuffers()
{
    if (!VBO.empty())
    {
        glDeleteBuffers((VBO.size()), VBO.data());
    }
    if (!VAO.empty())
    {
        glDeleteVertexArrays((VAO.size()), VAO.data());
    }

    VAO.clear();
    VBO.clear();
    vertexCounts.clear();

    VAO.resize(shapes.size());
    VBO.resize(shapes.size());
    vertexCounts.resize(shapes.size());

    Vector<3> center = this->shape->getCenter();

    for (size_t i = 0; i < shapes.size(); i++)
    {
        glGenVertexArrays(1, &VAO[i]);
        glBindVertexArray(VAO[i]);

        glGenBuffers(1, &VBO[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);

        float *vertices = nullptr;
        int stride = 0;

        if (type != GL_LINES) // normal mode (filled, textured)
        {
            vertexCounts[i] = (shapes[i]->getNumPoints() / VERTEX_DEPTH);
            vertices = shapes[i]->exportValues(&center);
            stride = VERTEX_DEPTH + COLOR_DEPTH + UV_DEPTH + NORMAL_DEPTH;
        }
        else // wireframe mode (no UVs, no Normals)
        {
            vertexCounts[i] = shapes[i]->getWireframeVertexCount();
            vertices = shapes[i]->exportWireframe();
            stride = VERTEX_DEPTH + COLOR_DEPTH;
        }

        glBufferData(GL_ARRAY_BUFFER,
                     vertexCounts[i] * stride * sizeof(GLfloat),
                     vertices,
                     GL_STATIC_DRAW);

        delete[] vertices;

        // Position attribute
        glVertexAttribPointer(0, VERTEX_DEPTH, GL_FLOAT, GL_FALSE,
                              stride * sizeof(GLfloat), (const void *)0);
        glEnableVertexAttribArray(0);

        // Color attribute
        glVertexAttribPointer(1, COLOR_DEPTH, GL_FLOAT, GL_FALSE,
                              stride * sizeof(GLfloat),
                              (const void *)(VERTEX_DEPTH * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        // UV attribute only in normal mode
        if (type != GL_LINES)
        {
            glVertexAttribPointer(2, UV_DEPTH, GL_FLOAT, GL_FALSE,
                                  stride * sizeof(GLfloat),
                                  (const void *)((VERTEX_DEPTH + COLOR_DEPTH) * sizeof(GLfloat)));
            glEnableVertexAttribArray(2);

            // Normal attribute
            glVertexAttribPointer(3, NORMAL_DEPTH, GL_FLOAT, GL_FALSE,
                                  stride * sizeof(GLfloat),
                                  (const void *)((VERTEX_DEPTH + COLOR_DEPTH + UV_DEPTH) * sizeof(GLfloat)));
            glEnableVertexAttribArray(3);
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}

void DrawerVisitor::reloadVertices()
{
    Vector<3> center = this->shape->getCenter();

    for (int i = 0; i < shapes.size(); i++)
    {
        if (type != GL_LINES)
        {
            glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
            vertexCounts[i] = (shapes[i]->getNumPoints() / VERTEX_DEPTH);
            float *vertices = shapes[i]->exportValues(&center);
            glBufferSubData(GL_ARRAY_BUFFER, 0,
                            vertexCounts[i] * (VERTEX_DEPTH + COLOR_DEPTH + UV_DEPTH + NORMAL_DEPTH) * sizeof(float),
                            vertices);
            delete[] vertices;
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
        else
        {
            glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
            vertexCounts[i] = shapes[i]->getWireframeVertexCount();
            float *vertices = shapes[i]->exportWireframe();
            glBufferSubData(GL_ARRAY_BUFFER, 0,
                            vertexCounts[i] * (VERTEX_DEPTH + COLOR_DEPTH) * sizeof(float),
                            vertices);
            delete[] vertices;
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }
}

Shape *DrawerVisitor::getShape() const { return shape; }

void DrawerVisitor::addScene(Scene *scene)
{
    delete scene; // shouldnt do anything
}

void DrawerVisitor::Rotate(float degrees, OrientationObject *orient)
{
    RotateZ(degrees, orient);
}

void DrawerVisitor::RotateX(float degrees, OrientationObject *orient)
{
    float radians = degrees * (std::acos(-1.0f) / 180.0f);

    Matrix<4, 4> rot;

    rot[0][0] = 1.0f;
    rot[1][1] = std::cos(radians);
    rot[1][2] = -std::sin(radians);
    rot[2][1] = std::sin(radians);
    rot[2][2] = std::cos(radians);
    rot[3][3] = 1.0f;

    transform(rot, true, orient);
}

void DrawerVisitor::RotateY(float degrees, OrientationObject *orient)
{
    float radians = degrees * (std::acos(-1.0f) / 180.0f);

    Matrix<4, 4> rot;

    rot[0][0] = std::cos(radians);
    rot[0][2] = std::sin(radians);
    rot[1][1] = 1.0f;
    rot[2][0] = -std::sin(radians);
    rot[2][2] = std::cos(radians);
    rot[3][3] = 1.0f;

    transform(rot, true, orient);
}

void DrawerVisitor::RotateZ(float degrees, OrientationObject *orient)
{
    float radians = degrees * (std::acos(-1.0f) / 180.0f);

    Matrix<4, 4> rot;

    rot[0][0] = std::cos(radians);
    rot[0][1] = -std::sin(radians);
    rot[1][0] = std::sin(radians);
    rot[1][1] = std::cos(radians);
    rot[2][2] = 1.0f;
    rot[3][3] = 1.0f;

    transform(rot, true, orient);
}
void DrawerVisitor::RotateArbitrary(float degrees, OrientationObject *orient)
{
    float radians = degrees * (std::acos(-1.0f) / 180.0f);
    if (orient == nullptr)
    {
        orient = this->orientation;
    }

    if (!orient)
        return;

    Vector<3> u = orient->generateDirection().unitVector();

    float ax = u[0];
    float ay = u[1];
    float az = u[2];

    float d = std::sqrt(ay * ay + az * az);

    Matrix<4, 4> Rx;
    Rx.identity();
    if (d > 0.0001f)
    {
        Rx[1][1] = az / d;
        Rx[1][2] = -ay / d;
        Rx[2][1] = ay / d;
        Rx[2][2] = az / d;
    }

    Matrix<4, 4> Ry;
    Ry.identity();
    Ry[0][0] = d;
    Ry[0][2] = -ax;
    Ry[2][0] = ax;
    Ry[2][2] = d;

    Matrix<4, 4> Rz;
    Rz.identity();
    Rz[0][0] = std::cos(radians);
    Rz[0][1] = -std::sin(radians);
    Rz[1][0] = std::sin(radians);
    Rz[1][1] = std::cos(radians);

    Matrix<4, 4> RxInv = ~Rx;
    Matrix<4, 4> RyInv = ~Ry;

    Matrix<4, 4> rotAligned = RxInv * RyInv * Rz * Ry * Rx;

    transform(rotAligned, true, orient);
}

void DrawerVisitor::Scale(float scale, OrientationObject *orient)
{
    Matrix<4, 4> scaleMatrix;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            scaleMatrix[i][j] = (i == j) ? 1.0f : 0.0f;

    for (int i = 0; i < 3; i++)
        scaleMatrix[i][i] = scale;

    transform(scaleMatrix, true, orient);
}

void DrawerVisitor::Translation(Direction dir, float step, OrientationObject *orient)
{
    float dx = 0.0f, dy = 0.0f, dz = 0.0f;
    if (dir == Direction::up)
        dy = step;
    if (dir == Direction::down)
        dy = -step;
    if (dir == Direction::left)
        dx = -step;
    if (dir == Direction::right)
        dx = step;
    if (dir == Direction::forward)
        dz = step;
    if (dir == Direction::back)
        dz = -step;

    Matrix<4, 4> translationMatrix;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            translationMatrix[i][j] = (i == j) ? 1.0f : 0.0f;

    translationMatrix[0][3] = dx;
    translationMatrix[1][3] = dy;
    translationMatrix[2][3] = dz;

    transform(translationMatrix, false, orient);
}

void DrawerVisitor::setWireframeMode()
{
    type = GL_LINES;
    rebuildGpuBuffers();
}

void DrawerVisitor::setNormalMode()
{
    type = GL_TRIANGLES;
    rebuildGpuBuffers();
}

DrawerVisitor *DrawerVisitor::selectNext() { return nullptr; }

DrawerVisitor *DrawerVisitor::getIndex(int i) { return nullptr; }

Matrix<4, 4> DrawerVisitor::transform(Matrix<4, 4> &trans, bool toCenter, OrientationObject *orient)
{
    Matrix<4, 4> fullTransform = trans;

    if (toCenter)
    {
        Vector<3> center;
        if (orient)
            center = orient->getCenter();
        else
        {
            center = this->shape->getCenter();
        }

        Matrix<4, 4> toCenter, backToOrigin;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                toCenter[i][j] = (i == j) ? 1.0f : 0.0f;
                backToOrigin[i][j] = (i == j) ? 1.0f : 0.0f;
            }
        }
        toCenter[0][3] = -center[0];
        toCenter[1][3] = -center[1];
        toCenter[2][3] = -center[2];
        backToOrigin[0][3] = center[0];
        backToOrigin[1][3] = center[1];
        backToOrigin[2][3] = center[2];
        fullTransform = backToOrigin * trans * toCenter;
    }

    for (int i = 0; i < shapes.size(); i++)
    {
        shapes[i]->applyMatrix(fullTransform);
    }

    shape->getOrientation()->update(trans, toCenter, orient);
    reloadVertices();

    return fullTransform;
}

void DrawerVisitor::Visit(Cuboid *cuboid)
{
    registerShape(cuboid->base);
    registerShape(cuboid->back);
    registerShape(cuboid->top);
    registerShape(cuboid->front);
    registerShape(cuboid->leftSide);
    registerShape(cuboid->rightSide);
    rebuildGpuBuffers();
}

void DrawerVisitor::Visit(_3DShape *shape)
{
    shape->acceptVisitor(this);
}

void DrawerVisitor::Visit(MultiFacedSurface *shape)
{
    this->shapes.clear();
    this->type = GL_TRIANGLES;
    registerShape(shape);
    this->orientation = shape->getOrientation();
    rebuildGpuBuffers();
}

void DrawerVisitor::Visit(Sphere *sphere)
{
    registerShape(sphere->centerCircle);
    for (int i = 0; i < sphere->allSides.size(); i++)
    {
        registerShape(sphere->allSides[i]);
    }
    rebuildGpuBuffers();
}

void DrawerVisitor::registerShape(Shape *s)
{
    s->setSurface(this->shape->getSurface());
    bool affected = this->shape->getSurface().getAffectedLight();
    s->setLightAffected(affected);
    this->shapes.push_back(s);
}
DrawerVisitor::DrawerVisitor(_3DShape *shape)
    : shape(shape)
{
    shape->acceptVisitor(this);
    this->orientation = shape->getOrientation();
}

DrawerVisitor::~DrawerVisitor()
{
    // Delete GPU buffers
    if (!VBO.empty())
    {
        glDeleteBuffers(static_cast<GLsizei>(VBO.size()), VBO.data());
        VBO.clear();
    }

    if (!VAO.empty())
    {
        glDeleteVertexArrays(static_cast<GLsizei>(VAO.size()), VAO.data());
        VAO.clear();
    }

    vertexCounts.clear();

    delete shape;
    shape = nullptr;
}
void DrawerVisitor::draw()
{
    Vector<3> canonicalShapeCenter = this->shape->getCenter();

    GLint currentProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);

    GLint texSamplerLoc = -1;
    GLint useTextureLoc = -1;
    GLint displacementTexLoc = -1;
    GLint useDisplacementLoc = -1;
    GLint displacementStrengthLoc = -1;
    GLint alphaTexLoc = -1;
    GLint useAlphaLoc = -1;
    GLint alphaValueLoc = -1;
    GLint shapeCenterLoc = -1;
    GLint displaceTowardCenterLoc = -1;
    GLint cameraMatrixLoc = -1;

    if (currentProgram != 0)
    {
        texSamplerLoc = glGetUniformLocation(static_cast<GLuint>(currentProgram), "tex");
        useTextureLoc = glGetUniformLocation(static_cast<GLuint>(currentProgram), "useTexture");
        displacementTexLoc = glGetUniformLocation(static_cast<GLuint>(currentProgram), "displacementTex");
        useDisplacementLoc = glGetUniformLocation(static_cast<GLuint>(currentProgram), "useDisplacement");
        displacementStrengthLoc = glGetUniformLocation(static_cast<GLuint>(currentProgram), "displacementStrength");
        alphaTexLoc = glGetUniformLocation(static_cast<GLuint>(currentProgram), "alphaTex");
        useAlphaLoc = glGetUniformLocation(static_cast<GLuint>(currentProgram), "useAlpha");
        alphaValueLoc = glGetUniformLocation(static_cast<GLuint>(currentProgram), "alphaValue");
        shapeCenterLoc = glGetUniformLocation(static_cast<GLuint>(currentProgram), "shapeCenter");
        displaceTowardCenterLoc = glGetUniformLocation(static_cast<GLuint>(currentProgram), "displaceTowardCenter");
        cameraMatrixLoc = glGetUniformLocation(static_cast<GLuint>(currentProgram), "cameraMatrix");
    }

    if (cameraMatrixLoc >= 0)
    {
        const Matrix<4, 4> &cameraMatrix = Camera::getInstance().getMatrix();
        float *flatMatrix = cameraMatrix.flatten();
        // OpenGL expects column-major by default. If your matrix is row-major, set GL_TRUE.
        // Based on multiplyHelper, it looks like standard row-major indexing.
        glUniformMatrix4fv(cameraMatrixLoc, 1, GL_TRUE, flatMatrix);
        delete[] flatMatrix;
    }

    for (size_t i = 0; i < shapes.size(); i++)
    {
        const Surface &surface = shapes[i]->getSurface();
        if (shapeCenterLoc >= 0)
        {
            glUniform3f(shapeCenterLoc,
                        canonicalShapeCenter[0],
                        canonicalShapeCenter[1],
                        canonicalShapeCenter[2]);
        }
        if (displaceTowardCenterLoc >= 0)
        {
            glUniform1i(displaceTowardCenterLoc, 0);
        }
        const bool useTexture =
            (type != GL_LINES) && surface.isColorTextureEnabled() && surface.getColorTexture() != 0;
        const bool useDisplacement =
            (type != GL_LINES) && surface.isDisplacementTextureEnabled() && surface.getDisplacementTexture() != 0;
        const bool useAlpha =
            (type != GL_LINES) && surface.isAlphaTextureEnabled() && surface.getAlphaTexture() != 0;

        // Color texture
        if (useTextureLoc >= 0)
        {
            glUniform1i(useTextureLoc, useTexture ? 1 : 0);
        }
        if (useTexture && texSamplerLoc >= 0)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, surface.getColorTexture());
            glUniform1i(texSamplerLoc, 0);
        }

        // Displacement texture
        if (useDisplacementLoc >= 0)
        {
            glUniform1i(useDisplacementLoc, useDisplacement ? 1 : 0);
        }
        if (useDisplacement && displacementTexLoc >= 0)
        {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, surface.getDisplacementTexture());
            glUniform1i(displacementTexLoc, 1);
            if (displacementStrengthLoc >= 0)
            {
                glUniform1f(displacementStrengthLoc, 0.1); // adjustable strength
            }
        }

        // Alpha texture
        if (useAlphaLoc >= 0)
        {
            glUniform1i(useAlphaLoc, useAlpha ? 1 : 0);
        }
        if (alphaValueLoc >= 0)
        {
            glUniform1f(alphaValueLoc, surface.getBaseColor()[3]);
        }
        if (useAlpha && alphaTexLoc >= 0)
        {
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, surface.getAlphaTexture());
            glUniform1i(alphaTexLoc, 2);
        }

        glBindVertexArray(VAO[i]);
        glDrawArrays(type, 0, vertexCounts[i]);
        glBindVertexArray(0);

        // Unbind textures
        if (useTexture || useDisplacement || useAlpha)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, 0);
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, 0);
            glActiveTexture(GL_TEXTURE0);
        }
    }
}

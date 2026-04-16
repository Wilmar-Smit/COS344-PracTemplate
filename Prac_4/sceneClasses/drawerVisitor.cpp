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

    for (size_t i = 0; i < shapes.size(); i++)
    {
        glGenVertexArrays(1, &VAO[i]);
        glBindVertexArray(VAO[i]);

        glGenBuffers(1, &VBO[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);

        float *vertices = nullptr;
        if (type == GL_TRIANGLE_FAN)
        {
            vertexCounts[i] = (shapes[i]->getNumPoints() / VERTEX_DEPTH);
            vertices = shapes[i]->exportValues();
        }
        else
        {
            vertexCounts[i] = shapes[i]->getWireframeVertexCount();
            vertices = shapes[i]->exportWireframe();
        }

        glBufferData(GL_ARRAY_BUFFER,
                     vertexCounts[i] * (VERTEX_DEPTH + COLOR_DEPTH) * sizeof(GLfloat),
                     vertices,
                     GL_STATIC_DRAW);

        delete[] vertices;

        glVertexAttribPointer(0, VERTEX_DEPTH, GL_FLOAT, GL_FALSE,
                              (VERTEX_DEPTH + COLOR_DEPTH) * sizeof(GLfloat), (const void *)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, COLOR_DEPTH, GL_FLOAT, GL_FALSE,
                              (VERTEX_DEPTH + COLOR_DEPTH) * sizeof(GLfloat),
                              (const void *)(VERTEX_DEPTH * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}

DrawerVisitor::DrawerVisitor(_3DShape *shape)
    : shape(shape)
{
    shape->acceptVisitor(this);
    this->orientation = shape->getOrientation();
}

DrawerVisitor::~DrawerVisitor()
{
    if (!VBO.empty())
    {
        glDeleteBuffers((VBO.size()), VBO.data());
    }

    if (!VAO.empty())
    {
        glDeleteVertexArrays((VAO.size()), VAO.data());
    }

    VBO.clear();
    VAO.clear();

    delete shape;
}

void DrawerVisitor::draw()
{
    for (size_t i = 0; i < shapes.size(); i++)
    {
        glBindVertexArray(VAO[i]);
        glDrawArrays(type, 0, vertexCounts[i]);
        glBindVertexArray(0);
    }
}

void DrawerVisitor::reloadVertices()
{

    for (int i = 0; i < shapes.size(); i++)
    {
        if (type == GL_TRIANGLE_FAN)
        {
            glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
            vertexCounts[i] = (shapes[i]->getNumPoints() / VERTEX_DEPTH);
            float *vertices = shapes[i]->exportValues();
            glBufferSubData(GL_ARRAY_BUFFER, 0,
                            vertexCounts[i] * (VERTEX_DEPTH + COLOR_DEPTH) * sizeof(float),
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

void DrawerVisitor::select()
{
    for (int i = 0; i < shapes.size(); i++)
    {
        if (!this->selected)
        {
            shapes[i]->setCoulourVec(shapes[i]->getColourPas());
        }
        else
        {
            shapes[i]->setCoulourVec(shapes[i]->dePastel(shapes[i]->getColourVec()));
        }
        this->selected = !this->selected;
    }
    reloadVertices();
}

void DrawerVisitor::deselect()
{
    if (this->selected)
    {
        this->select();
    }
}

void DrawerVisitor::setWireframeMode()
{
    for (int i = 0; i < shapes.size(); i++)
    {
        float *vertices = shapes[i]->exportWireframe();
        vertexCounts[i] = shapes[i]->getWireframeVertexCount();
        type = GL_LINES;

        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        glBufferData(GL_ARRAY_BUFFER, vertexCounts[i] * (VERTEX_DEPTH + COLOR_DEPTH) * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
        delete[] vertices;
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

void DrawerVisitor::setNormalMode()
{
    for (int i = 0; i < shapes.size(); i++)
    {
        float *vertices = shapes[i]->exportValues();
        vertexCounts[i] = static_cast<int>(shapes[i]->getNumPoints() / VERTEX_DEPTH);
        type = GL_TRIANGLE_FAN;

        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        glBufferData(GL_ARRAY_BUFFER, vertexCounts[i] * (VERTEX_DEPTH + COLOR_DEPTH) * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
        delete[] vertices;
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
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
    for (int i = 0; i < shape->squares.size(); i++)
    {
        registerShape(shape->squares[i]);
    }
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

    this->shapes.push_back(s);
}

#include "drawerVisitor.h"

DrawerVisitor::DrawerVisitor(_3DShape *shape)
    : shape(shape)
{
    Visit(this->shape);

    VAO.resize(shapes.size());
    VBO.resize(shapes.size());
    vertexCounts.resize(shapes.size());

    for (size_t i = 0; i < shapes.size(); i++)
    {
        glGenVertexArrays(1, &VAO[i]);
        glBindVertexArray(VAO[i]);

        glGenBuffers(1, &VBO[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);

        Shape<3> *currentShape = shapes[i];
        vertexCounts[i] = (currentShape->getNumPoints() / VERTEX_DEPTH);
        float *vertices = currentShape->exportValues();

        glBufferData(GL_ARRAY_BUFFER,
                     vertexCounts[i] * (VERTEX_DEPTH + COLOR_DEPTH) * sizeof(GLfloat),
                     vertices,
                     GL_STATIC_DRAW);

        delete[] vertices;

        // position attribute (location 0)
        glVertexAttribPointer(0, VERTEX_DEPTH, GL_FLOAT, GL_FALSE, (VERTEX_DEPTH + COLOR_DEPTH) * sizeof(GLfloat), (const void *)0);
        glEnableVertexAttribArray(0);

        // colour attribute (location 1)
        glVertexAttribPointer(1, COLOR_DEPTH, GL_FLOAT, GL_FALSE, (VERTEX_DEPTH + COLOR_DEPTH) * sizeof(GLfloat), (const void *)(VERTEX_DEPTH * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
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
            vertexCounts[i] = ((shapes[i]->getNumPoints() / VERTEX_DEPTH) * 2);
            float *vertices = shapes[i]->exportWireframe();
            glBufferSubData(GL_ARRAY_BUFFER, 0,
                            vertexCounts[i] * (VERTEX_DEPTH + COLOR_DEPTH) * sizeof(float),
                            vertices);
            delete[] vertices;
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }
}

Shape<3> *DrawerVisitor::getShape() const { return shape; }

void DrawerVisitor::addScene(DrawerVisitor *scene)
{
    delete scene; // shouldnt do anything
}

void DrawerVisitor::Rotate(float degrees, OrientationObject *orient)
{
    RotateZ(degrees);
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

    transform(rot, true);
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

    transform(rot, true);
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

    transform(rot, true);
}

void DrawerVisitor::Scale(float scale, OrientationObject *orient)
{
    Matrix<4, 4> scaleMatrix;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            scaleMatrix[i][j] = (i == j) ? 1.0f : 0.0f;

    for (int i = 0; i < 3; i++)
        scaleMatrix[i][i] = scale;

    transform(scaleMatrix, true);
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

    transform(translationMatrix, false);
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
        vertexCounts[i] = static_cast<int>((shapes[i]->getNumPoints() / VERTEX_DEPTH) * 2);
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

void DrawerVisitor::transform(Matrix<4, 4> &trans, bool toCenter, OrientationObject *orient)
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

    shape->notify();
    reloadVertices();
}

void DrawerVisitor::Visit(Cone *cone)
{
    this->shapes.push_back(cone->base);

    for (int i = 0; i < cone->sides.size(); i++)
    {
        this->shapes.push_back(cone->sides[i]);
    }
}

void DrawerVisitor::Visit(Cuboid *cuboid)
{
    this->shapes.push_back(cuboid->base);
    this->shapes.push_back(cuboid->back);
    this->shapes.push_back(cuboid->top);
    this->shapes.push_back(cuboid->front);
    this->shapes.push_back(cuboid->leftSide);
    this->shapes.push_back(cuboid->rightSide);
}

void DrawerVisitor::Visit(Cylinder *cyl)
{
    this->shapes.push_back(cyl->base);
    this->shapes.push_back(cyl->top);

    for (size_t i = 0; i < cyl->sides.size(); i++)
    {
        this->shapes.push_back(cyl->sides[i]);
    }
}

void DrawerVisitor::Visit(SquarePyramid *squarePyramid)
{
    this->shapes.push_back(squarePyramid->base);
    this->shapes.push_back(squarePyramid->side1);
    this->shapes.push_back(squarePyramid->side2);
    this->shapes.push_back(squarePyramid->side3);
    this->shapes.push_back(squarePyramid->side4);
}

void DrawerVisitor::Visit(TriangularPrism *triangularPrism)
{
    this->shapes.push_back(triangularPrism->base);
    this->shapes.push_back(triangularPrism->rightSide);
    this->shapes.push_back(triangularPrism->leftSide);
    this->shapes.push_back(triangularPrism->rightTop);
    this->shapes.push_back(triangularPrism->leftTop);
}

void DrawerVisitor::Visit(_3DShape *shape)
{
    shape->acceptVisitor(this);
}
void DrawerVisitor::Visit(Sphere *sphere)
{

    this->shapes.push_back(sphere->centerCircle);
    for (int i = 0; i < sphere->allSides.size(); i++)
    {
        this->shapes.push_back(sphere->allSides[i]);
    }
}
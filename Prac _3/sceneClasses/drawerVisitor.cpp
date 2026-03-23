#include "drawerVisitor.h"

template <int n>
DrawerVisitor<n>::DrawerVisitor(_3DShape<n> *shape)
    : shape(shape)
{
    // does the visiting and populates the array
    // Each shape sees visitor as a friend hence it can see its internals
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

        Shape<n> *currentShape = shapes[i];
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

template <int n>
void DrawerVisitor<n>::draw()
{
    for (size_t i = 0; i < shapes.size(); i++)
    {
        glBindVertexArray(VAO[i]);
        glDrawArrays(type, 0, vertexCounts[i]);
        glBindVertexArray(0);
    }
}

template <int n>
void DrawerVisitor<n>::reloadVertices()
{
    for (int i = 0; i < shapes.size(); i++)
    {
        if (type == GL_TRIANGLE_FAN)
        {
            glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
            vertexCounts[i] = static_cast<int>(shapes[i]->getNumPoints() / VERTEX_DEPTH);
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
            vertexCounts[i] = static_cast<int>((shapes[i]->getNumPoints() / VERTEX_DEPTH) * 2);
            float *vertices = shapes[i]->exportWireframe();
            glBufferSubData(GL_ARRAY_BUFFER, 0,
                            vertexCounts[i] * (VERTEX_DEPTH + COLOR_DEPTH) * sizeof(float),
                            vertices);
            delete[] vertices;
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }
}

template <int n>
Shape<n> *DrawerVisitor<n>::getShape() const { return shape; }

template <int n>
void DrawerVisitor<n>::addScene(Scene<n> *scene)
{
    delete scene; // shouldnt do anything
}

template <int n>
void DrawerVisitor<n>::Rotate(float degrees)
{
    RotateZ(degrees);
}

template <int n>
void DrawerVisitor<n>::RotateX(float degrees)
{

    if (n > 2)
    {
        float radians = degrees * (std::acos(-1.0f) / 180.0f);
        float cosTheta = std::cos(radians);
        float sinTheta = std::sin(radians);

        Matrix<n + 1, n + 1> rotationMatrix;
        for (int i = 0; i < n + 1; i++)
            for (int j = 0; j < n + 1; j++)
                if (i == j)
                    rotationMatrix[i][j] = 1.0f;

        rotationMatrix[2][2] = cosTheta;
        rotationMatrix[1][1] = cosTheta;
        rotationMatrix[1][2] = -sinTheta;
        rotationMatrix[2][1] = sinTheta;

        transform(rotationMatrix, true);
    }
}

template <int n>
void DrawerVisitor<n>::RotateY(float degrees)
{
    if (n > 2)
    {
        float radians = degrees * (std::acos(-1.0f) / 180.0f);
        float cosTheta = std::cos(radians);
        float sinTheta = std::sin(radians);

        Matrix<n + 1, n + 1> rotationMatrix;
        for (int i = 0; i < n + 1; i++)
            for (int j = 0; j < n + 1; j++)
                rotationMatrix[i][j] = (i == j) ? 1.0f : 0.0f;

        rotationMatrix[0][0] = cosTheta;
        rotationMatrix[0][2] = sinTheta;
        rotationMatrix[2][0] = -sinTheta;
        rotationMatrix[2][2] = cosTheta;

        transform(rotationMatrix, true);
    }
}

template <int n>
void DrawerVisitor<n>::RotateZ(float degrees)
{
    float radians = degrees * (std::acos(-1.0f) / 180.0f);
    float cosTheta = std::cos(radians);
    float sinTheta = std::sin(radians);

    Matrix<n + 1, n + 1> rotationMatrix;
    for (int i = 0; i < n + 1; i++)
        for (int j = 0; j < n + 1; j++)
            rotationMatrix[i][j] = (i == j) ? 1.0f : 0.0f;

    rotationMatrix[0][0] = cosTheta;
    rotationMatrix[0][1] = -sinTheta;
    rotationMatrix[1][0] = sinTheta;
    rotationMatrix[1][1] = cosTheta;

    transform(rotationMatrix, true);
}

template <int n>
void DrawerVisitor<n>::Scale(float scale)
{
    Matrix<n + 1, n + 1> scaleMatrix;
    for (int i = 0; i < n + 1; i++)
        for (int j = 0; j < n + 1; j++)
            scaleMatrix[i][j] = (i == j) ? 1.0f : 0.0f;

    for (int i = 0; i < n; i++)
        scaleMatrix[i][i] = scale;

    transform(scaleMatrix, true);
}

template <int n>
void DrawerVisitor<n>::Translation(Direction dir, float step)
{
    float dx = 0.0f, dy = 0.0f;
    if (dir == Direction::up)
        dy = step;
    if (dir == Direction::down)
        dy = -step;
    if (dir == Direction::left)
        dx = -step;
    if (dir == Direction::right)
        dx = step;

    Matrix<n + 1, n + 1> translationMatrix;
    for (int i = 0; i < n + 1; i++)
        for (int j = 0; j < n + 1; j++)
            translationMatrix[i][j] = (i == j) ? 1.0f : 0.0f;

    translationMatrix[0][n] = dx;
    translationMatrix[1][n] = dy;

    transform(translationMatrix, false);
}

template <int n>
void DrawerVisitor<n>::select()
{
    for (int i = 0; i < shapes.size(); i++)
    {
        if (!this)
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

template <int n>
void DrawerVisitor<n>::deselect()
{
    if (this->selected)
    {
        this->select();
    }
}

template <int n>
void DrawerVisitor<n>::setWireframeMode()
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

template <int n>
void DrawerVisitor<n>::setNormalMode()
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

template <int n>
DrawerVisitor<n> *DrawerVisitor<n>::selectNext() { return nullptr; }

template <int n>
DrawerVisitor<n> *DrawerVisitor<n>::getIndex(int i) { return nullptr; }

template <int n>
void DrawerVisitor<n>::transform(Matrix<n + 1, n + 1> &trans, bool toCenter)
{
    Matrix<n + 1, n + 1> fullTransform = trans;

    for (int i = 0; i < shapes.size(); i++)
    {
        if (toCenter)
        {
            Vector<n> center = shape->getCenter();

            Matrix<n + 1, n + 1> toCenter, backToOrigin;
            for (int i = 0; i < n + 1; i++)
                for (int j = 0; j < n + 1; j++)
                {
                    toCenter[i][j] = (i == j) ? 1.0f : 0.0f;
                    backToOrigin[i][j] = (i == j) ? 1.0f : 0.0f;
                }

            for (int i = 0; i < n; i++)
            {
                toCenter[i][n] = -center[i];
                backToOrigin[i][n] = center[i];
            }

            fullTransform = backToOrigin * trans * toCenter;
        }

        shapes[i]->applyMatrix(fullTransform);
    }

    reloadVertices();
}

template <int n>
void DrawerVisitor<n>::Visit(Cone<n> *cone)
{
    (void)cone;
}

template <int n>
void DrawerVisitor<n>::Visit(Cuboid<n> *cuboid)
{
    (void)cuboid;
}

template <int n>
void DrawerVisitor<n>::Visit(Cylinder<n> *cyl)
{
    this->shapes.push_back(cyl->base);
    this->shapes.push_back(cyl->top);

    for (size_t i = 0; i < cyl->sides.size(); i++)
    {
        this->shapes.push_back(cyl->sides[i]);
    }
}

template <int n>
void DrawerVisitor<n>::Visit(SquarePyramid<n> *squarePyramid)
{
    this->shapes.push_back(squarePyramid->base);
    this->shapes.push_back(squarePyramid->side1);
    this->shapes.push_back(squarePyramid->side2);
    this->shapes.push_back(squarePyramid->side3);
    this->shapes.push_back(squarePyramid->side4);
}

template <int n>
void DrawerVisitor<n>::Visit(TriangularPrism<n> *triangularPrism)
{
}

template <int n>
void DrawerVisitor<n>::Visit(_3DShape<n> *shape)
{
    shape->acceptVisitor(this);
}
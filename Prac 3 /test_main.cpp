// Standalone entry point for the math library test suite.
// No OpenGL / GLFW dependencies – links only LibraryTesting.cpp.
#include <iostream>

void VectorTesting();
void MatrixTesitng();
void TriangleTesting();
void SquareTesting();

int main()
{
    VectorTesting();
    std::cout << std::endl;
    MatrixTesitng();
    std::cout << std::endl;
    TriangleTesting();
    std::cout << std::endl;
    SquareTesting();
    return 0;
}

#include "Matrix.h"
#include "Vector.h"
#include "Shape.h"
#include "Triangle.h"
#include "Square.h"

#include <iostream>
#include <sstream>

template<int n>
void printVector(const Vector<n>& v) {
    std::cout << "(";
    for (int i = 0; i < n; i++) 
    {
        std::cout << v[i];

        if (i < n - 1) 
            std::cout << ", ";
    }
    std::cout << ")" << std::endl;
}

template<int n, int m>
void printMatrix(const Matrix<n, m>& mat) {
    for (int i = 0; i < n; i++) 
        {
        std::cout << "[ ";
        for (int j = 0; j < m; j++) 
            {
            std::cout << mat[i][j];

            if (j < m - 1) 
                std::cout << ", ";
        }
        std::cout << " ]" << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    // Vector testing
    std::cout << " Vector " << std::endl;

    Vector<3> v1 = {7.9f, 2.3f, 3.5f};
    Vector<3> v2 = {9.6f, 4.7f, 2.8f};

    std::cout << "v1: ";              
        printVector(v1);

    std::cout << "v2: ";              
        printVector(v2);

    std::cout << "v1 + v2: ";         
        printVector(v1 + v2);

    std::cout << "v1 - v2: ";         
        printVector(v1 - v2);

    std::cout << "v1 * 3: ";          
        printVector(v1 * 3.0f);

    std::cout << "v1 w dot product of v2: "        << (v1 * v2) << std::endl;
    std::cout << "magnitude of v1: "  << v1.magnitude() << std::endl;
    std::cout << "unit vector of v1: "; 
        printVector(v1.unitVector());
    std::cout << "v1 x v2: ";     
        printVector(v1.crossProduct(v2));

    // Matrix testing
    std::cout << "\n= Matrix " << std::endl;

    Matrix<3, 3> identity;
    identity[0][0] = 1; 
    identity[0][1] = 0; 
    identity[0][2] = 0;
    identity[1][0] = 0; 
    identity[1][1] = 1; 
    identity[1][2] = 0;
    identity[2][0] = 0; 
    identity[2][1] = 0; 
    identity[2][2] = 1;

    std::cout << "Identity matrix WEEEEEEEE:" << std::endl;
    printMatrix(identity);

    Matrix<3, 3> mat;
    mat[0][0] = 7; 
    mat[0][1] = 5; 
    mat[0][2] = 2;
    mat[1][0] = 1; 
    mat[1][1] = 9; 
    mat[1][2] = 7;
    mat[2][0] = 3; 
    mat[2][1] = 4; 
    mat[2][2] = 6;

    Matrix<3,1> mat2;
    mat2[0][0] = 7;
    mat2 [1][0] = 3;
    mat2[2][0] = -5;

    std::cout << "Matrix:" << std::endl;
    printMatrix(mat);

    std::cout << "Matrix 2:" << std::endl;
    printMatrix(mat2);

    std::cout << "Transpose:" << std::endl;
    printMatrix(~mat);

    std::cout << "Determinant: " << mat.determinant() << std::endl;

    std::cout << "Matrix * Identity:" << std::endl;
    printMatrix(mat * identity);

    std::cout << "Matrix * 2:" << std::endl;
    printMatrix(mat * 2.0f);

    std::cout << "Matrix + Matrix:" << std::endl;
    printMatrix(mat + mat);

    std::cout << "Matrix (3x3) * Matrix(3x1):" << std::endl;
    printMatrix(mat * mat2);

    // Traignle stuff
    std::cout << "\n Triangle " << std::endl;

    Vector<3> p1 = {0.0f, 0.0f, 0.0f};
    Vector<3> p2 = {1.0f, 0.0f, 0.0f};
    Vector<3> p3 = {0.0f, 1.0f, 0.0f};

    Triangle<3> tri(p1, p2, p3);
    std::cout << "Triangle:" << std::endl;
    tri.print();

    tri *= identity;
    std::cout << "Triangle after *= identity:" << std::endl;
    tri.print();

    Triangle<3>* triCopy = tri * mat;
    std::cout << "Triangle * mat (copy operator):" << std::endl;
    triCopy->print();
    delete triCopy;

    // Square stuff
    std::cout << "\n Square " << std::endl;

    Vector<2> center = {0.0f, 0.0f};
    Square<2> sq(center, 2.0f, 4.0f);
    std::cout << "Square from center (0,0), h=2, w=4:" << std::endl;
    sq.print();

    Matrix<2, 2> scale;
    scale[0][0] = 2; scale[0][1] = 0;
    scale[1][0] = 0; scale[1][1] = 2;

    Square<2>* sqCopy = sq * scale;
    std::cout << "Square * scale(2x):" << std::endl;
    sqCopy->print();
    delete sqCopy;

    return 0;
}
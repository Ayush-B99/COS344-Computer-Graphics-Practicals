#ifndef SQUARE_CPP
#define SQUARE_CPP

#include "Square.h"

// just had to be diff from the triangle
template<int n>
Square<n>::Square(const Vector<n>& center, float height, float width) {
    // Copy center into all four points first
    tl = center;
    tr = center;
    br = center;
    bl = center;

    // Adjust x (index 0) and y (index 1)
    float halfW = width / 2.0f;
    float halfH = height / 2.0f;

    // tl: x - halfW, y + halfH
    tl[0] = center[0] - halfW;
    tl[1] = center[1] + halfH;

    // tr: x + halfW, y + halfH
    tr[0] = center[0] + halfW;
    tr[1] = center[1] + halfH;

    // br: x + halfW, y - halfH
    br[0] = center[0] + halfW;
    br[1] = center[1] - halfH;

    // bl: x - halfW, y - halfH
    bl[0] = center[0] - halfW;
    bl[1] = center[1] - halfH;
}

template<int n>
Square<n>::Square(const Vector<n>& tl, const Vector<n>& tr, const Vector<n>& br, const Vector<n>& bl)
    : tl(tl), tr(tr), br(br), bl(bl) {

}

template<int n>
Square<n>::Square(const Square<n>& other)
    : tl(other.tl), tr(other.tr), br(other.br), bl(other.bl) {

}

// same as triangle, in order!  
template<int n>
Square<n>& Square<n>::operator*=(const Matrix<n, n>& mat) {
    Matrix<n, 1> m1 = (Matrix<n, 1>)tl;
    Matrix<n, 1> m2 = (Matrix<n, 1>)tr;
    Matrix<n, 1> m3 = (Matrix<n, 1>)br;
    Matrix<n, 1> m4 = (Matrix<n, 1>)bl;

    Matrix<n, 1> r1 = mat * m1;
    Matrix<n, 1> r2 = mat * m2;
    Matrix<n, 1> r3 = mat * m3;
    Matrix<n, 1> r4 = mat * m4;

    tl = Vector<n>(r1);
    tr = Vector<n>(r2);
    br = Vector<n>(r3);
    bl = Vector<n>(r4);

    return *this;
}

template<int n>
Square<n>* Square<n>::operator*(const Matrix<n, n>& mat) const {
    Square<n>* copy = new Square<n>(*this);
    *copy *= mat;
    return copy;
}

template<int n>
float* Square<n>::getPoints() const {
    int totalPoints = 4 * n;
    float* points = new float[totalPoints];
    int idx = 0;
    for (int i = 0; i < n; i++) 
    {
        points[idx++] = tl[i];
    }

    for (int i = 0; i < n; i++) 
    {
        points[idx++] = tr[i];
    }

    for (int i = 0; i < n; i++) 
    {
        points[idx++] = br[i];
    }

    for (int i = 0; i < n; i++)
    { 
        points[idx++] = bl[i];
    }

    return points;
}

template<int n>
int Square<n>::getNumPoints() const {
    return 4 * n;
}

#endif
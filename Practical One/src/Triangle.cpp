#ifndef TRIANGLE_CPP
#define TRIANGLE_CPP

#include "Triangle.h"

template<int n>
Triangle<n>::Triangle(const Vector<n>& p1, const Vector<n>& p2, const Vector<n>& p3)
    : p1(p1), p2(p2), p3(p3) {

}

template<int n>
Triangle<n>::Triangle(const Triangle<n>& other)
    : p1(other.p1), p2(other.p2), p3(other.p3) {

}

// apply matrices to points 
template<int n>
Triangle<n>& Triangle<n>::operator*=(const Matrix<n, n>& mat) {
    // convert vector to matrix -> multiply -> convert back
    // do  in order or might mess up*
    Matrix<n, 1> m1 = (Matrix<n, 1>)p1;
    Matrix<n, 1> m2 = (Matrix<n, 1>)p2;
    Matrix<n, 1> m3 = (Matrix<n, 1>)p3;

    Matrix<n, 1> r1 = mat * m1;
    Matrix<n, 1> r2 = mat * m2;
    Matrix<n, 1> r3 = mat * m3;

    p1 = Vector<n>(r1);
    p2 = Vector<n>(r2);
    p3 = Vector<n>(r3);

    return *this;
}

// does same as operator*= but this func makes a copy
template<int n>
Triangle<n>* Triangle<n>::operator*(const Matrix<n, n>& mat) const {
    Triangle<n>* copy = new Triangle<n>(*this);
    *copy *= mat;
    return copy;
}

// linear version of shape -> basically convert to an array
template<int n>
float* Triangle<n>::getPoints() const {
    int totalPoints = 3 * n;
    float* points = new float[totalPoints];
    int index = 0;

    for (int i = 0; i < n; i++) 
    {
        points[index++] = p1[i];
    }

    for (int i = 0; i < n; i++) 
    {
        points[index++] = p2[i];
    }

    for (int i = 0; i < n; i++) 
    {
        points[index++] = p3[i];
    }

    return points;
}

// multiply by 3 bc triangle
template<int n>
int Triangle<n>::getNumPoints() const {
    return 3 * n;
}

#endif
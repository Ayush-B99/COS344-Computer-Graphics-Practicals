#ifndef VECTOR_CPP
#define VECTOR_CPP

#include "Vector.h"

#include <cmath>

template<int n>
Vector<n>::Vector() {
    arr = new float[n];
    for (int i = 0; i < n; i++) 
    {
        arr[i] = 0.0f;
    }
}

// Initializer list constructor
template<int n>
Vector<n>::Vector(std::initializer_list<float> list) {
    arr = new float[n];
    int i = 0;

    for (float val : list) 
    {
        if (i >= n) 
            break;
        arr[i++] = val;
    }

    while (i < n) 
    {
        arr[i++] = 0.0f;
    }
}

// shallow 
template<int n>
Vector<n>::Vector(float* ptr) {
    arr = ptr;
}

template<int n>
Vector<n>::Vector(const Matrix<n, 1>& mat) {
    arr = new float[n];
    for (int i = 0; i < n; i++) 
    {
        arr[i] = mat[i][0];
    }
}

template<int n>
Vector<n>::~Vector() {
    delete[] arr;
}

// deep 
template<int n>
Vector<n>::Vector(const Vector<n>& other) {
    arr = new float[n];
    for (int i = 0; i < n; i++) 
    {
        arr[i] = other[i];
    }
}

// idk what exactly is happening break poitn for now
template<int n>
Vector<n>::operator Matrix<n, 1>() const {
    Matrix<n, 1> mat;

    for (int i = 0; i < n; i++) 
    {
        mat[i][0] = arr[i];
    }
    return mat;
}

template<int n>
Vector<n>& Vector<n>::operator=(const Vector<n>& other) {
    if (this == &other) 
    {
        return *this;
    }

    delete[] arr;

    arr = new float[n];
    for (int i = 0; i < n; i++) 
    {
        arr[i] = other[i];
    }

    return *this;
}

// Vector addition
template<int n>
Vector<n> Vector<n>::operator+(const Vector<n> other) const {
    Vector<n> addV;
    for (int i = 0; i < n; i++) 
    {
        addV[i] = arr[i] + other[i];
    }
    return addV;
}

// Vector subtraction
template<int n>
Vector<n> Vector<n>::operator-(const Vector<n> other) const {
    Vector<n> minusV;
    for (int i = 0; i < n; i++) 
    {
        minusV[i] = arr[i] - other[i];
    }
    return minusV;
}

// Scalar multiplication
template<int n>
Vector<n> Vector<n>::operator*(const float s) const {
    Vector<n> vMultiply;
    for (int i = 0; i < n; i++) 
    {
        vMultiply[i] = arr[i] * s;
    }
    return vMultiply;
}

// Dot product
template<int n>
float Vector<n>::operator*(const Vector<n> other) const {
    float dotVector = 0.0f;
    for (int i = 0; i < n; i++) {
        dotVector += arr[i] * other[i];
    }
    return dotVector;
}

template<int n>
float Vector<n>::magnitude() const {
    float sum = 0.0f;
    for (int i = 0; i < n; i++) 
    {
        sum += arr[i] * arr[i];
    }

    return std::sqrt(sum);
}

template<int n>
Vector<3> Vector<n>::crossProduct(const Vector<3> other) const {
    Vector<3> crossVector;

    crossVector[0] = arr[1] * other[2] - arr[2] * other[1];
    crossVector[1] = arr[2] * other[0] - arr[0] * other[2];
    crossVector[2] = arr[0] * other[1] - arr[1] * other[0];

    return crossVector;
}

// Unit vector
template<int n>
Vector<n> Vector<n>::unitVector() const {
    float mag = magnitude();
    if (mag == 0.0f) 
    {
        throw "Invalid unit vector";
    }

    Vector<n> unitV;
    for (int i = 0; i < n; i++) 
    {
        unitV[i] = arr[i] / mag;
    }

    return unitV;
}

template<int n>
int Vector<n>::getN() const {
    return n;
}

#endif
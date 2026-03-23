#ifndef MATRIX_CPP
#define MATRIX_CPP

#include "Matrix.h"

template<int n, int m>
Matrix<n, m>::Matrix() {
    arr = new float*[n];
    for (int i = 0; i < n; i++) 
    {
        arr[i] = new float[m];
        for (int j = 0; j < m; j++) 
        {
            arr[i][j] = 0.0f;
        }
    }
}

// make shallow not deep
template<int n, int m>
Matrix<n, m>::Matrix(float** ptr) {
    arr = ptr;
}

// deep copy now
template<int n, int m>
Matrix<n, m>::Matrix(const Matrix<n, m>& other) {
    arr = new float*[n];
    for (int i = 0; i < n; i++) 
    {
        arr[i] = new float[m];
        for (int j = 0; j < m; j++) 
        {
            arr[i][j] = other[i][j];
        }
    }
}


template<int n, int m>
Matrix<n, m>::~Matrix() {
    for (int i = 0; i < n; i++) 
    {
        delete[] arr[i];
    }

    delete[] arr;
}

// pulling out 110 notes to code these op functions smh man
template<int n, int m>
Matrix<n, m>& Matrix<n, m>::operator=(const Matrix<n, m>& other) {
    if (this == &other) 
    {
        return *this;
    }

    for (int i = 0; i < n; i++) 
    {
        delete[] arr[i];
    }

    delete[] arr;

    arr = new float*[n];
    for (int i = 0; i < n; i++) 
    {
        arr[i] = new float[m];
        for (int j = 0; j < m; j++) 
        {
            arr[i][j] = other[i][j];
        }
    }

    return *this;
}

// cross mutliply matrtix formula m*n x n*m only!!!
template<int n, int m>
template<int a>
Matrix<n, a> Matrix<n, m>::operator*(const Matrix<m, a> other) const {
    Matrix<n, a> cProduct;
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < a; j++) 
        {
            float sum = 0.0f;
            for (int k = 0; k < m; k++) 
            {
                sum += arr[i][k] * other[k][j];
            }
            cProduct[i][j] = sum;
        }
    }
    return cProduct;
}

// scalar product
template<int n, int m>
Matrix<n, m> Matrix<n, m>::operator*(const float s) const {
    Matrix<n, m> sProduct;
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            sProduct[i][j] = arr[i][j] * s;
        }
    }
    
    return sProduct;
}

// Matrix addition, Amn + Bmn
template<int n, int m>
Matrix<n, m> Matrix<n, m>::operator+(const Matrix<n, m> other) const {
    Matrix<n, m> result;
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            result[i][j] = arr[i][j] + other[i][j];
        }
    }
    return result;
}

// Transpose flip rows & columns but keep same mn
// W func
template<int n, int m>
Matrix<m, n> Matrix<n, m>::operator~() const {
    Matrix<m, n> tMatrix;
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            tMatrix[j][i] = arr[i][j];
        }
    }
    return tMatrix;
}

template<int n, int m>
int Matrix<n, m>::getN() const {
    return n;
}

template<int n, int m>
int Matrix<n, m>::getM() const {
    return m;
}

// Helper to get  determinant of a m x n sub-matrix stored in arr
static float detHelper(float** mat, int size) {
    if (size == 1) 
    {
        return mat[0][0];
    }

    if (size == 2) 
    {
        return mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];
    }

    float det = 0.0f;
    float** sub = new float*[size - 1];

    for (int i = 0; i < size - 1; i++) 
    {
        sub[i] = new float[size - 1];
    }

    for (int col = 0; col < size; col++) 
    {
        for (int i = 1; i < size; i++) 
        {
            int sj = 0;
            for (int j = 0; j < size; j++) 
            {
                if (j == col) 
                    continue;

                sub[i-1][sj++] = mat[i][j];
            }
        }

        float sign;
        if (col % 2 == 0)
        {
            sign = 1.0f;
        }

        else
        {
            sign = -1.0f;
        }

        det += sign * mat[0][col] * detHelper(sub, size - 1);
    }

    for (int i = 0; i < size - 1; i++) 
    {
        delete[] sub[i];
    }

    delete[] sub;

    return det;
}

template<int n, int m>
float Matrix<n, m>::determinant() const {
    if (n != m) 
    {
        throw "Matrix is not square";
    }

    return detHelper(arr, n);
}

#endif
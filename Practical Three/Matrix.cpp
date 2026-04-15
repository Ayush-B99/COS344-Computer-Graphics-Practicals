#include "Matrix.hpp"
#include <cmath>

Mat4 mat4Identity() {
    Mat4 r;
    for (int i = 0; i < 16; i++) r.m[i] = 0.0f;
    r.m[0] = 1.0f; r.m[5] = 1.0f; r.m[10] = 1.0f; r.m[15] = 1.0f;
    return r;
}

Mat4 mat4Multiply(const Mat4& A, const Mat4& B) {
    Mat4 C;
    for (int i = 0; i < 16; i++) C.m[i] = 0.0f;
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            float sum = 0.0f;
            for (int k = 0; k < 4; k++) {
                sum += A.m[k * 4 + row] * B.m[col * 4 + k];
            }
            C.m[col * 4 + row] = sum;
        }
    }
    return C;
}

Mat4 mat4Translate(float tx, float ty, float tz) {
    Mat4 r = mat4Identity();
    r.m[12] = tx;
    r.m[13] = ty;
    r.m[14] = tz;
    return r;
}

Mat4 mat4RotateX(float angle) {
    Mat4 r = mat4Identity();
    float c = cos(angle);
    float s = sin(angle);
    r.m[5]  =  c; r.m[9]  = -s;
    r.m[6]  =  s; r.m[10] =  c;
    return r;
}

Mat4 mat4RotateY(float angle) {
    Mat4 r = mat4Identity();
    float c = cos(angle);
    float s = sin(angle);
    r.m[0]  =  c; r.m[8]  =  s;
    r.m[2]  = -s; r.m[10] =  c;
    return r;
}

Mat4 mat4RotateZ(float angle) {
    Mat4 r = mat4Identity();
    float c = cos(angle);
    float s = sin(angle);
    r.m[0] =  c; r.m[4] = -s;
    r.m[1] =  s; r.m[5] =  c;
    return r;
}

Mat4 mat4Perspective(float fovRad, float aspect, float nearP, float farP) {
    Mat4 r;
    for (int i = 0; i < 16; i++) r.m[i] = 0.0f;
    float tanHalf = tan(fovRad / 2.0f);
    r.m[0]  = 1.0f / (aspect * tanHalf);
    r.m[5]  = 1.0f / tanHalf;
    r.m[10] = -(farP + nearP) / (farP - nearP);
    r.m[11] = -1.0f;
    r.m[14] = -(2.0f * farP * nearP) / (farP - nearP);
    return r;
}

Mat4 mat4LookAt(float eyeX, float eyeY, float eyeZ,
                float cenX, float cenY, float cenZ,
                float upX,  float upY,  float upZ) {
    float fx = cenX - eyeX, fy = cenY - eyeY, fz = cenZ - eyeZ;
    float fLen = sqrt(fx*fx + fy*fy + fz*fz);
    fx /= fLen; fy /= fLen; fz /= fLen;

    float sx = fy * upZ - fz * upY;
    float sy = fz * upX - fx * upZ;
    float sz = fx * upY - fy * upX;
    float sLen = sqrt(sx*sx + sy*sy + sz*sz);
    sx /= sLen; sy /= sLen; sz /= sLen;

    float ux = sy * fz - sz * fy;
    float uy = sz * fx - sx * fz;
    float uz = sx * fy - sy * fx;

    Mat4 r = mat4Identity();
    r.m[0]  =  sx; r.m[4]  =  sy; r.m[8]   =  sz;
    r.m[1]  =  ux; r.m[5]  =  uy; r.m[9]   =  uz;
    r.m[2]  = -fx; r.m[6]  = -fy; r.m[10]  = -fz;
    r.m[12] = -(sx*eyeX + sy*eyeY + sz*eyeZ);
    r.m[13] = -(ux*eyeX + uy*eyeY + uz*eyeZ);
    r.m[14] =  (fx*eyeX + fy*eyeY + fz*eyeZ);
    return r;
}
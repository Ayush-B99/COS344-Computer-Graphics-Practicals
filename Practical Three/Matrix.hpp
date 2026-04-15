#ifndef MATRIX_HPP
#define MATRIX_HPP

struct Mat4 {
    float m[16];
};

Mat4 mat4Identity();
Mat4 mat4Multiply(const Mat4& A, const Mat4& B);
Mat4 mat4Translate(float tx, float ty, float tz);
Mat4 mat4RotateX(float angle);
Mat4 mat4RotateY(float angle);
Mat4 mat4RotateZ(float angle);
Mat4 mat4Perspective(float fovRad, float aspect, float nearP, float farP);
Mat4 mat4LookAt(float eyeX, float eyeY, float eyeZ, float cenX, float cenY, float cenZ, float upX,  float upY,  float upZ);

#endif
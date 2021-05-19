#ifndef ROTATION2D_MATRIX4X4_H
#define ROTATION2D_MATRIX4X4_H
#include "Matrix.h"

class Matrix4x4
        : public Matrix<double, 4>{
public:
    Matrix4x4();
    Matrix4x4(double jaw, double pitch, double roll, Vector<double, 3> axis);
    Matrix4x4& operator=(const Matrix4x4 matrix4x4);
    Matrix4x4& operator=(const Matrix<double, 4> matrix4x4);

};
#endif //ROTATION2D_MATRIX4X4_H

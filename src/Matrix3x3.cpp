#include "../inc/Matrix3x3.h"

Matrix3x3::Matrix3x3(double degree, char axis) {
    /* [cos(), -sin(), ...]
     * [sin(),  cos(), ...]
     * [..................] */
    
    double radians = toRadians(degree);
    switch (axis) {
        case 'x':
            this->matrix[0][0] = 1;
            this->matrix[0][1] = 0;
            this->matrix[0][2] = 0;
            this->matrix[1][0] = 0;
            this->matrix[1][1] = cos(radians);
            this->matrix[1][2] = -sin(radians);
            this->matrix[2][0] = 0;
            this->matrix[2][1] = sin(radians);
            this->matrix[2][2] = cos(radians);
            break;
        case 'y':
            this->matrix[0][0] = cos(radians);
            this->matrix[0][1] = 0;
            this->matrix[0][2] = sin(radians);
            this->matrix[1][0] = 0;
            this->matrix[1][1] = 1;
            this->matrix[1][2] = 0;
            this->matrix[2][0] = -sin(radians);
            this->matrix[2][1] = 0;
            this->matrix[2][2] = cos(radians);
            break;
        case 'z':
            this->matrix[0][0] = cos(radians);
            this->matrix[0][1] = -sin(radians);
            this->matrix[0][2] = 0;
            this->matrix[1][0] = sin(radians);
            this->matrix[1][1] = cos(radians);
            this->matrix[1][2] = 0;
            this->matrix[2][0] = 0;
            this->matrix[2][1] = 0;
            this->matrix[2][2] = 1;
            break;
        default:
            std::cout << "Unknown axis, try again\n";
            break;
    }
}

Matrix3x3::Matrix3x3() {
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if (i == j){
                this->matrix[i][j] = 1;
            }else{
                this->matrix[i][j] = 0;
            }   
        }
    }
}

Matrix3x3 &Matrix3x3::operator=(const Matrix3x3 matrix3x3) {
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            this->matrix[i][j] = matrix3x3.matrix[i][j];
        }
    }
    return *this;
}

Matrix3x3 &Matrix3x3::operator=(const Matrix<double, 3> matrix3x3) {
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            this->matrix[i][j] = matrix3x3.matrix[i][j];
        }
    }
    return *this;
}


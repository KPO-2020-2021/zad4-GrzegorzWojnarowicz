#include "../inc/Matrix4x4.h"


Matrix4x4::Matrix4x4(double yaw, double pitch, double roll, Vector<double, 3> axis) {
    //yaw pitch and roll are in degrees
    // fill 4x4 matrix
    yaw = toRadians(yaw);
    pitch = toRadians(pitch);
    roll = toRadians(roll);


    this->matrix[0][0] = cos(yaw) * cos(pitch);
    this->matrix[0][1] = cos(yaw)*sin(pitch)*sin(roll) - sin(yaw) * cos(roll);
    this->matrix[0][2] = cos(yaw)*sin(pitch)*cos(roll) + sin(yaw) * sin(roll);
    this->matrix[0][3] = axis[0];

    this->matrix[1][0] = sin(yaw) * cos(pitch);
    this->matrix[1][1] = sin(yaw) * sin(pitch) * sin(roll) + cos(yaw) * cos(roll);
    this->matrix[1][2] = sin(yaw) * sin(pitch) * cos(roll) - cos(yaw) * sin(roll);
    this->matrix[1][3] = axis[1];

    this->matrix[2][0] = -sin(pitch);
    this->matrix[2][1] = cos(pitch) * sin(roll);
    this->matrix[2][2] = cos(pitch) * cos(roll);
    this->matrix[2][3] = axis[2];


    this->matrix[3][0] = 0;
    this->matrix[3][1] = 0;
    this->matrix[3][2] = 0;
    this->matrix[3][3] = 1;
}

Matrix4x4::Matrix4x4() {
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if (i == j){
                this->matrix[i][j] = 1;
            }else{
                this->matrix[i][j] = 0;
            }   
        }
    }
}

Matrix4x4 &Matrix4x4::operator=(const Matrix4x4 matrix4x4) {
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            this->matrix[i][j] = matrix4x4.matrix[i][j];
        }
    }
    return *this;
}

Matrix4x4 &Matrix4x4::operator=(const Matrix<double, 4> matrix4x4) {
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            this->matrix[i][j] = matrix4x4.matrix[i][j];
        }
    }
    return *this;
}


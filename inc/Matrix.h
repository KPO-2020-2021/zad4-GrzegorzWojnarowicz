#ifndef ROTATION3D_MATRIX_H
#define ROTATION3D_MATRIX_H

#include <ios>
#include "Vector.h"

template <typename T, unsigned int dimensions>
class Matrix {
private:
    T matrix[dimensions][dimensions];
    double toRadians(double degree);
public:
    Matrix();

    template<typename T1, unsigned int dimensions1>
    friend bool operator==(const Matrix<T1, dimensions1> &matrix1, const Matrix<T1, dimensions1> &matrix2);

    template<typename T1, unsigned int dimensions1>
    friend Vector<T1,dimensions1> operator*(const Matrix<T1, dimensions1> &matrix, Vector<T1, dimensions1> &vec);

    template<typename T1, unsigned int dimensions1>
    friend Matrix<T1,dimensions1> operator*(const Matrix<T1, dimensions1> &matrix1, const Matrix<T1, dimensions1> &matrix2);

    T &operator()(unsigned int row, unsigned int column);
    const T &operator()(unsigned int row, unsigned int column) const;

    void displayMatrix();
    template<typename T1, unsigned int dimensions1>
    friend std::ostream & operator<<(std::ostream & ost, Matrix<T1, dimensions1> &matrix);

    friend class Matrix3x3;
    friend class Matrix4x4;
};


template <typename T, unsigned int dimensions>
Matrix<T, dimensions>::Matrix() {
    for (int i = 0; i < dimensions; i++){
        for (int j = 0; j < dimensions; j++){
            this->matrix[i][j] = 0;
        }
    }
    this->matrix[0][0] = 1;
    this->matrix[dimensions-1][dimensions-1] = 1;
}


template <typename T, unsigned int dimensions>
double Matrix<T, dimensions>::toRadians(double degree){
    return degree * M_PI / 180;
}

template <typename T, unsigned int dimensions>
bool operator==(const Matrix<T, dimensions> &matrix1, const Matrix<T, dimensions> &matrix2){
    int i = 0;
    int j = 0;
    while(i < dimensions){
        while(j < dimensions){
            if(std::abs(matrix1.matrix[i][j] - matrix2.matrix[i][j]) > MIN_THRESHOLD){
                return false;
            }
            j++;
        }
        i++;
    }
    return true;
}

template <typename T, unsigned int dimensions>
Vector<T,dimensions> operator*(const Matrix<T, dimensions> &matrix, Vector<T, dimensions> &vec){
    Vector<T, dimensions> result = Vector<T,dimensions>();
    for (int i = 0; i < dimensions; i++){
        for (int j = 0; j < dimensions; j++){
            result[i] += vec[j] * matrix.matrix[i][j];
        }
    }

    return result;
}

template <typename T, unsigned int dimensions>
T &Matrix<T,dimensions>::operator()(unsigned int row, unsigned int column) {
    if(row >= dimensions || row < 0 || column >= dimensions || column < 0){
        throw std::invalid_argument("index out of range");
    }
    return matrix[row][column];
}

template <typename T, unsigned int dimensions>
const T &Matrix<T, dimensions>::operator()(unsigned int row, unsigned int column) const {
    if(row >= dimensions || row < 0 || column >= dimensions || column < 0){
        throw std::invalid_argument("index out of range");
    }
    return matrix[row][column];
}

template<typename T, unsigned int dimensions>
Matrix<T, dimensions> operator*(const Matrix<T, dimensions> &matrix1, const Matrix<T, dimensions> &matrix2) {
    Matrix<T,3> result = Matrix<T,3>();
    for(int i = 0; i < dimensions; i++){
        for(int j = 0; j < dimensions; j++){
            result(i,j) = 0;
            for(int k = 0; k < dimensions; k++){
                result(i,j) += matrix1(i,k) * matrix2(k,j);
            }
        }
    }
    return result;
}

template<typename T, unsigned int dimensions>
void Matrix<T, dimensions>::displayMatrix() {
    std::cout << std::fixed;
    std::cout << std::setprecision(10);
    for (int i = 0; i < dimensions; ++i) {
        for (int j = 0; j < dimensions; ++j) {
            std::cout << this->matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

template<typename T, unsigned int dimensions>
std::ostream &operator<<(std::ostream &ost, Matrix<T, dimensions> &matrix1) {
    std::cout << std::fixed;
    std::cout << std::setprecision(10);
    for (int i = 0; i < dimensions; ++i) {
        for (int j = 0; j < dimensions; ++j) {
            std::cout << matrix1.matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return ost;
}


#endif //ROTATION3D_MATRIX_H
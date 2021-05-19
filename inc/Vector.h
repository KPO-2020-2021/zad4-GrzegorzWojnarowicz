#ifndef ROTATION3D_VECTOR_H
#define ROTATION3D_VECTOR_H
#include "Constants.h"
#include <iostream>
#include <iomanip>
#include <cmath>

template <typename T, unsigned int dimensions>
class Vector
{
private:
    T vector [dimensions];
public:
    Vector();
    Vector(T _x, T _y);
    Vector(T _x, T _y, T _z);

    template <typename T1, unsigned int dimensions1>
    friend bool operator==(const Vector<T1, dimensions1> &Vec1, const Vector<T1, dimensions1> &Vec2);

    template <typename T1, unsigned int dimensions1>
    friend Vector<T1, dimensions1> operator+(Vector<T1, dimensions1> &Vec1, Vector<T1, dimensions1> &Vec2);

    template <typename T1, unsigned int dimensions1>
    friend Vector<T1, dimensions1> operator-(Vector<T1, dimensions1> &Vec1, Vector<T1, dimensions1> &Vec2);

    template <typename T1, unsigned int dimensions1>
    friend Vector<T1, dimensions1> operator/(Vector<T1, dimensions1> &Vec, const double &Num);

    template <typename T1, unsigned int dimensions1>
    friend Vector<T1, dimensions1> operator*(Vector<T1, dimensions1> &Vec, const double &Num);

    const T &operator[](int index) const;

    T &operator[](int index);

    T getLength();

    template<typename T1, unsigned int dimensions1>
    friend std::ostream &operator<<(std::ostream &ost, const Vector<T1, dimensions1> &Vec);

    template<typename T1, unsigned int dimensions1>
    friend std::istream &operator>>(std::istream &ist, Vector<T1, dimensions1> &Vec);

    void setX(T _x);

    void setY(T _y);

    void setZ(T _z);
};
template <typename T, unsigned int dimensions>
Vector<T, dimensions>::Vector(){
    unsigned int i = 0;
    while (i < dimensions)
    {
        this->vector[i] = 0;
        i++;
    }
    
}

template <typename T, unsigned int dimensions>
Vector<T, dimensions>::Vector(T _x, T _y){
    if (dimensions != 2){
        throw std::invalid_argument("Vector dimension is not equal 2");
    }
    this->vector[0] = _x;
    this->vector[1] = _y;
    unsigned int i = 2;
    while (i < dimensions)
    {
        this->vector[i] = 0;
        i++;
    }
}

template <typename T, unsigned int dimensions>
Vector<T, dimensions>::Vector(T _x, T _y, T _z){
    if (dimensions != 3){
        throw std::invalid_argument("Vector dimension is not equal 3");
    }
    this->vector[0] = _x;
    this->vector[1] = _y;
    this->vector[2] = _z;
    unsigned int i = 3;
    while (i < dimensions)
    {
        this->vector[i] = 0;
        i++;
    }
}

template<typename T, unsigned int dimensions>
void Vector<T, dimensions>::setX(T _x) {
    if (dimensions >= 1) this->vector[0] = _x;
}

template<typename T, unsigned int dimensions>
void Vector<T, dimensions>::setY(T _y) {
    if (dimensions >= 2) this->vector[1] = _y;
}

template<typename T, unsigned int dimensions>
void Vector<T, dimensions>::setZ(T _z) {
    if (dimensions >= 3) this->vector[2] = _z;
}

template<typename T, unsigned int dimensions>
bool operator==(const Vector<T, dimensions> &Vec1, const Vector<T, dimensions> &Vec2){
    int is_equal = 0;
    for (int i = 0; i < dimensions; i++){
        if (std::abs(Vec1.vector[i] - Vec2.vector[i]) <= MIN_THRESHOLD){
            is_equal++;
        }     
    }
    if (is_equal == dimensions){
        return true;
    }
    return false;
}

template<typename T, unsigned int dimensions>
Vector<T, dimensions> operator+(Vector<T, dimensions> &Vec1, Vector<T, dimensions> &Vec2){
    Vector<T, dimensions> Vector;
    for (int i = 0; i < dimensions; i++){
        Vector.vector[i] = Vec1.vector[i] + Vec2.vector[i]; 
    }
    return Vector;
}

template<typename T, unsigned int dimensions>
Vector<T, dimensions> operator-(Vector<T, dimensions> &Vec1, Vector<T, dimensions> &Vec2){
    Vector<T, dimensions> Vector;
    for (int i = 0; i < dimensions; i++){
        Vector.vector[i] = Vec1.vector[i] - Vec2.vector[i]; 
    }
    return Vector;
}

template<typename T, unsigned int dimensions>
Vector<T, dimensions> operator/(Vector<T, dimensions> &Vec, const double &Num){
    Vector<T, dimensions> Vector;
    if (Num == 0) throw std::invalid_argument("Division by zero");
    
    for (int i = 0; i < dimensions; i++){
        Vector.vector[i] = Vec.vector[i] / Num; 
    }
    return Vector;
}

template<typename T, unsigned int dimensions>
Vector<T, dimensions> operator*(Vector<T, dimensions> &Vec, const double &Num){
    Vector<T, dimensions> Vector;
    for (int i = 0; i < dimensions; i++){
        Vector.vector[i] = Vec.vector[i] * Num; 
    }
    return Vector;
}

template<typename T, unsigned int dimensions>
const T &Vector<T, dimensions>::operator[](int index) const {
    if (index > dimensions) throw std::invalid_argument("Index out of range");
    return this->vector[index]; 
}

template<typename T, unsigned int dimensions>
T &Vector<T, dimensions>::operator[](int index) {
    if (index > dimensions) throw std::invalid_argument("Index out of range");
    return this->vector[index]; 
}

template<typename T, unsigned int dimensions>
T Vector<T, dimensions>::getLength(){
    T square_sum = 0;
    for (int i = 0; i < dimensions; i++){
        square_sum += (this->vector[i] * this->vector[i]); 
    }
    return sqrt(square_sum);
}

template<typename T, unsigned int dimensions>
std::istream &operator>>(std::istream &ist, Vector<T, dimensions> &Vec) {
    T entry;
    for (int i = 0; i < dimensions; i++){
        std::cout << "Enter " << i << " coordinate of vector:\n";
        ist >> entry;
        Vec[i] = entry;
    }
    return ist;
}

template<typename T, unsigned int dimensions>
std::ostream &operator<<(std::ostream &ost, const Vector<T, dimensions> &Vec) {
    std::cout << std::fixed;
    std::cout << std::setprecision(VECTOR_PRECISION);
    for (int i = 0; i < dimensions - 1; i++){
        ost << Vec.vector[i] << " ";
    }
    ost << Vec.vector[dimensions - 1] << std::endl;
    return ost;
}

#endif //ROTATION3D_VECTOR_H
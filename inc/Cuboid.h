#ifndef ROTATION3D_CUBOID_H
#define ROTATION3D_CUBOID_H
#include <iostream>
#include <utility>
#include <cmath>
#include <float.h>
#include "Matrix3x3.h"
#include "Constants.h"
#include "Vector.h"

template<typename T>
class Cuboid {
private:

    Vector<T, 3> vertices[VERTICES_NUMBER];
    T sidesLength[SIDES_NUMBER];
    Vector<T, 3> centerOfMass;
    Vector<T, 3> calculateCenterOfMass();
public:
    Cuboid();
    Cuboid(Vector<T, 3> *ver);
    /* Set all parameters strictly */
    template<typename T1>
    friend bool operator==(const Cuboid<T1> &cub1, const Cuboid<T1> &cub2);
    void translationByVector(Vector<T, 3> &Vec);
    void rotationByMatrix(const Matrix3x3 &rotMatrix);

    const Vector<T, 3> & operator[](int index) const;
    Vector<T, 3> & operator[](int index);

    template<typename T1>
    friend std::ostream & operator<<(std::ostream & ost, Cuboid<T1> &cub);
    T getSideLength(unsigned int index);
    void calculateSidesLength();
    Vector<T, 3> getCenterOfMass();
};


template<typename T>
Cuboid<T>::Cuboid() {
    for(int i = 0; i < VERTICES_NUMBER; i++){
        this->vertices[i] = Vector<T, 3>();
    }
}

template<typename T>
Cuboid<T>::Cuboid(Vector<T, 3> *ver){

//  Front  || Back 
//  3   2  || 7   6 this is how vertices are alligned
//  0   1  || 4   5

    for(int i = 0; i < VERTICES_NUMBER; i++){
        this->vertices[i] = ver[i];
        for(int j = 0; j < VERTICES_NUMBER; j++){
            if(i != j){
                if(ver[i] == ver[j]){
                    throw std::invalid_argument("one or more vertices is the same in cuboid");
                }
            }
        }
    }
    calculateCenterOfMass();
    calculateSidesLength();
}

template<typename T>
bool operator==(const Cuboid<T> &cub1, const Cuboid<T> &cub2){
    if(
       cub1.vertices[0] == cub2.vertices[0] &&
       cub1.vertices[1] == cub2.vertices[1] &&
       cub1.vertices[2] == cub2.vertices[2] &&
       cub1.vertices[3] == cub2.vertices[3] &&
       cub1.vertices[4] == cub2.vertices[4] &&
       cub1.vertices[5] == cub2.vertices[5] &&
       cub1.vertices[6] == cub2.vertices[6] &&
       cub1.vertices[7] == cub2.vertices[7] ){
        return true;
    }
    return false;
}

template<typename T>
void Cuboid<T>::translationByVector(Vector<T, 3> &Vec){
    this->vertices[0] = Vec + (this->vertices[0]);
    this->vertices[1] = Vec + (this->vertices[1]);
    this->vertices[2] = Vec + (this->vertices[2]);
    this->vertices[3] = Vec + (this->vertices[3]);
    this->vertices[4] = Vec + (this->vertices[4]);
    this->vertices[5] = Vec + (this->vertices[5]);
    this->vertices[6] = Vec + (this->vertices[6]);
    this->vertices[7] = Vec + (this->vertices[7]);
    calculateCenterOfMass();
}

template<typename  T>
void Cuboid<T>::rotationByMatrix(const Matrix3x3 &rotMatrix){

    this->vertices[0] = rotMatrix * (this->vertices[0]);
    this->vertices[1] = rotMatrix * (this->vertices[1]);
    this->vertices[2] = rotMatrix * (this->vertices[2]);
    this->vertices[3] = rotMatrix * (this->vertices[3]);
    this->vertices[4] = rotMatrix * (this->vertices[4]);
    this->vertices[5] = rotMatrix * (this->vertices[5]);
    this->vertices[6] = rotMatrix * (this->vertices[6]);
    this->vertices[7] = rotMatrix * (this->vertices[7]);
    calculateCenterOfMass();
}

template<typename  T>
const Vector<T, 3> &Cuboid<T>::operator[](int index) const {
    switch (index) {
        case 0:
            return this->vertices[0];
        case 1:
            return this->vertices[1];;
        case 2:
            return this->vertices[2];
        case 3:
            return this->vertices[3];
        case 4:
            return this->vertices[4];
        case 5:
            return this->vertices[5];
        case 6:
            return this->vertices[6];
        case 7:
            return this->vertices[7];
        default:
            throw std::invalid_argument("index out of range");
    }
}

template<typename  T>
Vector<T, 3> &Cuboid<T>::operator[](int index) {
    switch (index) {
        case 0:
            return this->vertices[0];
        case 1:
            return this->vertices[1];;
        case 2:
            return this->vertices[2];
        case 3:
            return this->vertices[3];
        case 4:
            return this->vertices[4];
        case 5:
            return this->vertices[5];;
        case 6:
            return this->vertices[6];
        case 7:
            return this->vertices[7];
        default:
            throw std::invalid_argument("index out of range");
    }
}

template<typename T>
void Cuboid<T>::calculateSidesLength(){

    Vector<T, 3> side = Vector<T, 3>();
    side = this->vertices[0] - this->vertices[1];
    this->sidesLength[0] = side.getLength();
    side = this->vertices[2] - this->vertices[3];
    this->sidesLength[1] = side.getLength();
    side = this->vertices[4] - this->vertices[5];
    this->sidesLength[2] = side.getLength();
    side = this->vertices[6] - this->vertices[7];
    this->sidesLength[3] = side.getLength();


    side = this->vertices[0] - this->vertices[3];
    this->sidesLength[4] = side.getLength();
    side = this->vertices[1] - this->vertices[2];
    this->sidesLength[5] = side.getLength();
    side = this->vertices[4] - this->vertices[7];
    this->sidesLength[6] = side.getLength();
    side = this->vertices[5] - this->vertices[6];
    this->sidesLength[7] = side.getLength();


    side = this->vertices[0] - this->vertices[4];
    this->sidesLength[8] = side.getLength();
    side = this->vertices[1] - this->vertices[5];
    this->sidesLength[9] = side.getLength();
    side = this->vertices[2] - this->vertices[6];
    this->sidesLength[10] = side.getLength();
    side = this->vertices[3] - this->vertices[7];
    this->sidesLength[11] = side.getLength();
}

template<typename T>
std::ostream &operator<<(std::ostream &ost, Cuboid<T> &cub) {
    ost << std::setprecision(10) << std::fixed;
    
    double xMax = cub[1][0]; double xMin = cub[0][0]; double xMid = (xMax + xMin) /2;
    double yMax = cub[4][1]; double yMin = cub[0][1]; double yMid = (yMax + yMin) /2;
    double zMax = cub[3][2]; double zMin = cub[0][2]; double zMid = (zMax + zMin) /2;

    Vector<double, 3> up = Vector<double, 3>(xMid, yMin, zMid);
    Vector<double, 3> down = Vector<double, 3>(xMid, yMax, zMid);

    ost << up;
    ost << xMax << " " << yMin << " " << zMax << "\n";
    ost << xMax << " " << yMax << " " << zMax << "\n";
    ost << down << "#\n\n";

    ost << up;
    ost << xMax << " " << yMin << " " << zMin << "\n";
    ost << xMax << " " << yMax << " " << zMin << "\n";
    ost << down << "#\n\n";

    ost << up;
    ost << xMin << " " << yMin << " " << zMin << "\n";
    ost << xMin << " " << yMax << " " << zMin << "\n";
    ost << down << "#\n\n";

    ost << up;
    ost << xMin << " " << yMin << " " << zMax << "\n";
    ost << xMin << " " << yMax << " " << zMax << "\n";
    ost << down << "#\n\n";

    ost << up;
    ost << xMax << " " << yMin << " " << zMax << "\n";
    ost << xMax << " " << yMax << " " << zMax << "\n";
    ost << down << "#\n\n";

    return ost;
}

template<typename T>
T Cuboid<T>::getSideLength(unsigned int index) {
    if(index > SIDES_NUMBER) throw std::invalid_argument("index out of range");
    return this->sidesLength[index];
}

template<typename T>
Vector<T, 3> Cuboid<T>::calculateCenterOfMass() {

        this->centerOfMass = this->vertices[6] - this->vertices[0];
        this->centerOfMass = this->centerOfMass/2;
        this->centerOfMass = this->centerOfMass + this->vertices[0];

    return this->centerOfMass;
}

template<typename T>
Vector<T, 3> Cuboid<T>::getCenterOfMass() {
    return this->centerOfMass;
}


#endif //ROTATION3D_CUBOID_H

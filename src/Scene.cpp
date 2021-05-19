#include "Scene.h"
#include "../inc/Scene.h"


scene::scene() {
    GNU.ZmienTrybRys(PzG::TR_3D);
    this->fileName[0] = "../data/data.txt";
    this->fileName[1] = "../data/data1.txt";
    this->fileName[2] = "../data/data2.txt";
    this->fileName[3] = "../data/data3.txt";
    this->fileName[4] = "../data/data4.txt";
    this->XRange[0] = 0;
    this->XRange[1] = 0;
    this->YRange[0] = 0;
    this->YRange[1] = 0;
    
}

scene::scene(double _XRange[2], double _YRange[2], double _ZRange[2]) {
    this->fileName[0] = "../data/data.txt";
    this->fileName[1] = "../data/data1.txt";
    this->fileName[2] = "../data/data2.txt";
    this->fileName[3] = "../data/data3.txt";
    this->fileName[4] = "../data/data4.txt";

    this->XRange[0] = _XRange[0];
    this->XRange[1] = _XRange[1];
    this->YRange[0] = _YRange[0];
    this->YRange[1] = _YRange[1];
    this->ZRange[0] = _ZRange[0];
    this->ZRange[1] = _ZRange[1];


    GNU.UstawRotacjeXZ(60,30);
    for( int i = 0; i < 5; ++i){
        GNU.DodajNazwePliku(this->fileName[i].c_str())
                .ZmienSposobRys(PzG::SR_Ciagly)
                .ZmienSzerokosc(1)
                .ZmienKolor(i + 1);
    }

   

    GNU.ZmienTrybRys(PzG::TR_3D);
    GNU.UstawZakresX((this->XRange[0]),(this->XRange[1]));
    GNU.UstawZakresY((this->YRange[0]),(this->YRange[1]));
    GNU.UstawZakresZ((this->ZRange[0]),(this->ZRange[1]));
}

void scene::drawScene(){
    std::ofstream os;
    for(int i = 0; i < 5; i++){
        os.open(this->fileName[i]);
        if(!os){
            throw std::exception();
        }
        os << cub[i];

        os.close();
    }

   
    GNU.Inicjalizuj();
    GNU.Rysuj();

}


void scene::animateRotateCuboid( double &degree, char &axis) {
    Cuboid<double> oldCub = this->cub[this->chosenIndex];
    Matrix3x3 rotMatrix = Matrix3x3();
    Matrix3x3 oldMatrix = this->rotMatrix;
    double singleDegree = 0;
    while (std::abs(singleDegree) < std::abs(degree)){
        singleDegree += 2;
        if(degree >= 0){
            rotMatrix = Matrix3x3(2,axis);
            this->cub[this->chosenIndex].rotationByMatrix(rotMatrix);
        }else{
            rotMatrix = Matrix3x3(-2,axis);
            this->cub[this->chosenIndex].rotationByMatrix(rotMatrix);
        }
        usleep(ANIMATION_SPEED);
        drawScene();
    }
    this->cub[this->chosenIndex] = oldCub;
    this->rotMatrix = Matrix3x3(degree, axis);
    this->cub[this->chosenIndex].rotationByMatrix(this->rotMatrix);
    this->rotMatrix = this->rotMatrix * oldMatrix;
    drawScene();
}

void scene::animateTranslateRectangle() {
    Cuboid<double> oldCub = this->cub[this->chosenIndex];
    Vector<double, 3> animateTranslation = this->translation/this->translation.getLength();
    Vector<double, 3> unityTranslation = this->translation/this->translation.getLength();
    unityTranslation = unityTranslation/RESOLUTION;
    double i = 0;
    while (animateTranslation.getLength() < this->translation.getLength()){
        i++;
        animateTranslation = unityTranslation * i;
        this->cub[this->chosenIndex].translationByVector(animateTranslation);
        usleep(ANIMATION_SPEED);
        drawScene();
        this->cub[this->chosenIndex] = oldCub;
    }
    this->cub[this->chosenIndex] = oldCub;
    this->cub[this->chosenIndex].translationByVector(this->translation);
    drawScene();
}

void scene::rotateByAmountOfRotation(int amountOfRotation) {

    Matrix3x3 matrixGetForSingleRotation = this->rotMatrix;
    for(int k = 1; k < amountOfRotation; ++k){
        this->rotMatrix = matrixGetForSingleRotation * this->rotMatrix;
    }
    this->cub[this->chosenIndex].rotationByMatrix(this->rotMatrix);
    drawScene();
}

#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>

class Vector {
public:
    double x, y, z, h;

    Vector() {}
    Vector(double _x, double _y, double _z, double _h);
    ~Vector() {}
};

class Matrix {
public:
    double M[4][4];

    Matrix();
    Matrix(double x11, double x12, double x13, double x14,
           double x21, double x22, double x23, double x24,
           double x31, double x32, double x33, double x34,
           double x41, double x42, double x43, double x44);
    Matrix(int i);

    ~Matrix() {}
    Matrix operator *(const Matrix &A);
    Vector operator *(const Vector &V);

    static Matrix transpose(Matrix matr);

    static Matrix rotateX(double angle);
    static Matrix rotateY(double angle);
    static Matrix rotateZ(double angle);

    static Matrix scale(double a, double b, double c);
    static Matrix reflectionX();
    static Matrix translate(double dx, double dy, double dz);

    static Matrix projectionCentral(double h);
    static Matrix projectionParallel(int type);

};


#endif // MATRIX_H

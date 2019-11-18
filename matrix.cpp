#include "matrix.h"
#include "stdio.h"
/*
  Класс Vector
*/

Vector::Vector(double _x, double _y, double _z, double _h) {
    x = _x;
    y = _y;
    z = _z;
    h = _h;
}

/*
  Класс Matrix
*/

Matrix::Matrix() {}

Matrix::Matrix(double x11, double x12, double x13, double x14,
               double x21, double x22, double x23, double x24,
               double x31, double x32, double x33, double x34,
               double x41, double x42, double x43, double x44) {
    M[0][0] = x11; M[0][1] = x12; M[0][2] = x13; M[0][3] = x14;
    M[1][0] = x21; M[1][1] = x22; M[1][2] = x23; M[1][3] = x24;
    M[2][0] = x31; M[2][1] = x32; M[2][2] = x33; M[2][3] = x34;
    M[3][0] = x41; M[3][1] = x42; M[3][2] = x43; M[3][3] = x44;
}

Matrix::Matrix(int i) {
    M[0][0] = 1; M[0][1] = 0; M[0][2] = 0; M[0][3] = 0;
    M[1][0] = 0; M[1][1] = 1; M[1][2] = 0; M[1][3] = 0;
    M[2][0] = 0; M[2][1] = 0; M[2][2] = 1; M[2][3] = 0;
    M[3][0] = 0; M[3][1] = 0; M[3][2] = 0; M[3][3] = 1;
}

Matrix Matrix::transpose(Matrix matr) {
    Matrix transposed;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            transposed.M[i][j] = matr.M[j][i];
        }
    }
    return transposed;
}

///Возвращает матрицу, результат произведения на матрицу А.
Matrix Matrix::operator *(const Matrix &A)
{
    Matrix C;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            C.M[i][j] = 0;
            for (int k = 0; k < 4; k++)
                C.M[i][j] += M[i][k] * A.M[k][j];
        }
    }
    return C;
}

///Возвращает вектор, результат произведения на вектор V.
Vector Matrix::operator *(const Vector &V) {
    return Vector(M[0][0] * V.x + M[0][1] * V.y + M[0][2] * V.z + M[0][3] * V.h,
                  M[1][0] * V.x + M[1][1] * V.y + M[1][2] * V.z + M[1][3] * V.h,
                  M[2][0] * V.x + M[2][1] * V.y + M[2][2] * V.z + M[2][3] * V.h,
                  M[3][0] * V.x + M[3][1] * V.y + M[3][2] * V.z + M[3][3] * V.h);
}


///Возращает матрицу поворота на угол angle.
Matrix Matrix::rotateX(double angle) {
    double r_angle = M_PI / 180 * angle;
    return Matrix(1,          0,           0, 0,
                  0, cos(r_angle), -sin(r_angle), 0,
                  0, sin(r_angle),  cos(r_angle),  0,
                  0,          0,           0,  1);
}

Matrix Matrix::rotateY(double angle) {
    double r_angle = M_PI / 180 * angle;
    return Matrix(cos(r_angle), 0, sin(r_angle), 0,
                           0, 1,          0, 0,
                 -sin(r_angle), 0, cos(r_angle), 0,
                           0, 0,          0, 1);
}

Matrix Matrix::rotateZ(double angle) {
    double r_angle = M_PI / 180 * angle;
    return Matrix(cos(r_angle), -sin(r_angle), 0, 0,
                  sin(r_angle),  cos(r_angle), 0, 0,
                           0,           0, 1, 0,
                           0,           0, 0, 1);
}

///Возвращает матрицу масштабирования с коэффициентами a и b перед х и у соответственно.
Matrix Matrix::scale(double a, double b, double c) {
    return Matrix(a, 0, 0, 0,
                  0, b, 0, 0,
                  0, 0, c, 0,
                  0, 0, 0, 1);
}

///Возвращает матрицу симметричного отражения относительно оси Ох.
Matrix Matrix::reflectionX() {
    return Matrix(-1, 0, 0, 0,
                   0, 1, 0, 0,
                   0, 0, 1, 0,
                   0, 0, 0, 1);
}

///Вовзвращает матрицу переноса на координаты dx и dy.
Matrix Matrix::translate(double dx, double dy, double dz) {
    return Matrix(1, 0, 0, dx,
                  0, 1, 0, dy,
                  0, 0, 1, dz,
                  0, 0, 0, 1 );
}


//Для одной центральной проекции
Matrix Matrix::projectionCentral(double h)
{
    return Matrix(1, 0,    0, 0,
                  0, 1,    0, 0,
                  0, 0,    0, 0,
                  0, 0, -1/h, 1);
}

//Для четырех параллельных проекций
Matrix Matrix::projectionParallel(int type)
{
    Matrix M;

    // 1 тип - Ортографическая проекция с z = 0
    if (type == 1)
        M = Matrix(1, 0, 0, 0,
                   0, 1, 0, 0,
                   0, 0, 0, 0,
                   0, 0, 0, 1);
    /*2 тип - Триметрическая проекция (поворот на 30 вокруг Y
    поворот на 45 вокруг X и проецирование на Z = 0)*/
    if (type == 2)
        M =
    Matrix(sqrt(3)/2, 0,          1/2,       0,
           sqrt(2)/4, sqrt(2)/2, -sqrt(6)/4, 0,
           0,         0,          0,         0,
           0,         0,          0,         1);
    //3 тип - Косоугольная Свободная , т.к угол = pi/4
    if (type == 3)
       M = Matrix(1, 0, sqrt(2)/2, 0,
                  0, 1, sqrt(2)/2, 0,
                  0, 0, 0,         0,
                  0, 0, 0,         1);
    //4 тип - Косоугольная Кабинетная , т.к угол = 1/2 * pi/4
    if (type == 4)
        M = Matrix(1, 0, sqrt(2)/4, 0,
                   0, 1, sqrt(2)/4, 0,
                   0, 0, 0,         0,
                   0, 0, 0,         1);
    return M;
}

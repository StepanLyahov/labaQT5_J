#ifndef TORCHER_H
#define TORCHER_H
//Импорт родительского модуля, для уточнения числа N - граней
#include <mainwindow.h>
#include <QVector>
#include <QVector3D>
#include <QMatrix4x4>
#include <vector>
#include "matrix.h"
using namespace std;


class MyModel {
public:
    MyModel();
    void drawMyModel(QPainter *painter, vector<QPolygon> newPolygones);
    void createPoligon(vector<int> vectPoint, int pos, QColor color);

    void createPoints(double step, double start, double end);

    ~MyModel() {}
    void getPolygones();
    //Вектор точек, содержащих фигуру
    vector <QVector3D> Dots;
    //Вектор полигонов для фигуры
    vector <QPolygon> polygones;
    //Вектор точек для полигонов фигуры
    vector <vector<int>> dotsPolygones;
    //Вектор координат Z
    vector <double> zpVector;
    //Вектор цветов для каждого полигона
    vector<QColor> vectorColor;

    //Вектор состояний - нажат, не нажат
    vector <bool> isPressedVector;

    int step = 3;
};

#endif

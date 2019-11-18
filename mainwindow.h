#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QInputDialog>
#include <QShortcut>
#include <vector>
#include <myModel.h>
#include <cmath>

#include "matrix.h"

QT_BEGIN_NAMESPACE
using namespace std;
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

private slots:
public:
    MainWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void rightClick(QMouseEvent *event);
    //void mousePressEvent(QMouseEvent *event);
    int indexPressedPolygon;
    int currentIndexPressedPolygon;
    vector<QPolygon> newPolygones;


    Matrix R;

    int wheelCoeficient;
    void wheelEvent(QWheelEvent* events);

    ~MainWindow();
private:
    Ui::MainWindow *ui;
    //Координаты предыдущей точки курсора мыши
    QPointF previousPoint;
    //Повороты по осям
    //float xAxisRotation;
    //float yAxisRotation;
    //int N;

    //Вектор новых координат Zp, в соответствии с которыми сортировать
    vector<double> newZpCoordinats;
    //Вектор новых координат точек
    vector <vector<int>> newDotsPolygones;
    //Вектор новых цветов
    vector <QColor> newVectorColor;
    //Вектор новых состояний - нажат, не нажат
    vector <bool> newIsPressedVector;
};
#endif // MAINWINDOW_H

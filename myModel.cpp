#include "myModel.h"
#include "matrix.h"

void MyModel::createPoints(double step, double start, double end) {
    double arrZ[] = {2, 0.5, -0.5, -2};
    for (int i = 0; i < 4; i++) {
        Dots.push_back(QVector3D(0.5, 0.5, arrZ[i]));
        Dots.push_back(QVector3D(-0.5, 0.5, arrZ[i]));
        Dots.push_back(QVector3D(-0.5, -0.5, arrZ[i]));
        Dots.push_back(QVector3D(0.5, -0.5, arrZ[i]));
    }
}

MyModel::MyModel() {
    // первый прямоугольник (шаблон для остальных прямоугольников)
    createPoints((double)step, 2.0, -2.0);

    // второй прямоугольник
    for (int i = 0; i < ((4) * 4); i++) {
        Vector V(Dots[i].x(),Dots[i].y(), Dots[i].z(), 1);
        V = Matrix::rotateY(90) * V;
        Dots.push_back(QVector3D(V.x, V.y, V.z));
    }


    // третий мальенький прямоугольник
    for (int i = 0; i < ((4) * 4); i++) {
        Vector V(Dots[i].x(),Dots[i].y(), Dots[i].z(), 1);
        V = Matrix::rotateX(90) * V;
        Dots.push_back(QVector3D(V.x, V.y, V.z));
    }
}


// По шаблону(массив индексов) и смешению(позицию шаблона в глобальном массиве точек)
// создаём полигон и всё необохдимое для сортировки
void MyModel::createPoligon(vector<int> vectPoint, int pos, QColor color) {
    //Создаём полигон
    QPolygon *poly = new QPolygon();
    *poly << QPoint(Dots[vectPoint[0]+pos].x(),Dots[vectPoint[0]+pos].y())
          << QPoint(Dots[vectPoint[1]+pos].x(),Dots[vectPoint[1]+pos].y())
          << QPoint(Dots[vectPoint[2]+pos].x(),Dots[vectPoint[2]+pos].y())
          << QPoint(Dots[vectPoint[3]+pos].x(),Dots[vectPoint[3]+pos].y());

    //сохраняем полигон в массив полоигонов
    polygones.push_back(*poly);

    // для созданного полигона сохраняем среднее арифметическое его Z-координат(номер СА будет совпадать с номером полигона в главном массиве)
    zpVector.push_back((Dots[vectPoint[0]+pos].z()+
                        Dots[vectPoint[1]+pos].z()+
                        Dots[vectPoint[2]+pos].z()+
                        Dots[vectPoint[3]+pos].z()/4));

    // запоминаем в векторе точки, которые были использованы в этом полигоне
    vector<int> temp;
    temp.push_back(vectPoint[0]+pos);
    temp.push_back(vectPoint[1]+pos);
    temp.push_back(vectPoint[2]+pos);
    temp.push_back(vectPoint[3]+pos);
    //сохраняем этот набор точек
    dotsPolygones.push_back(temp);

    // просто выбираем какой цвет будет у этого полигона
    //vectorColor.push_back(mainColor);
    vectorColor.push_back(color);
}


//Получение полигонов
void MyModel::getPolygones(){

    for (int i = 0; i < ((step) * 4); i = i + 8) {
        // передаём шаблон и позицию и цвет
        createPoligon({0,1,2,3}, i, Qt::blue);
        createPoligon({4,5,6,7}, i, Qt::black);
        createPoligon({0,1,5,4}, i, Qt::red);
        createPoligon({0,3,7,4}, i, Qt::yellow);
        createPoligon({2,3,7,6}, i, Qt::blue);
        createPoligon({1,2,6,5}, i, Qt::cyan);
    }



    for (int i = ((step) * 4) + 4; i < ((step) * 4 * 2) + 4; i = i + 8) {
        createPoligon({0,1,2,3}, i, Qt::yellow);
        createPoligon({4,5,6,7}, i, Qt::yellow);
        createPoligon({0,1,5,4}, i, Qt::yellow);
        createPoligon({0,3,7,4}, i, Qt::yellow);
        createPoligon({2,3,7,6}, i, Qt::yellow);
        createPoligon({1,2,6,5}, i, Qt::yellow);
    }



    for (int i = ((step) * 4 * 2) + 8; i < ((step) * 4*3) + 8; i = i + 8) {
        createPoligon({0,1,2,3}, i, Qt::cyan);
        createPoligon({4,5,6,7}, i, Qt::blue);
        createPoligon({0,1,5,4}, i, Qt::yellow);
        createPoligon({0,3,7,4}, i, Qt::red);
        createPoligon({2,3,7,6}, i, Qt::black);
        createPoligon({1,2,6,5}, i, Qt::blue);
    }

}

void MyModel::drawMyModel(QPainter *painter, vector<QPolygon> newPolygones) {
    painter->setBrush(Qt::NoBrush);

    for (unsigned int i = 0; i < polygones.size(); i++){
        //Выбрать выделение согласно индексу выбранного полигона
        if (this->isPressedVector[i])
            painter->setPen(QPen(Qt::black, 7, Qt::SolidLine, Qt::RoundCap));
        else
            painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
        painter->setBrush(this->vectorColor[i]);
        painter->drawPolygon(newPolygones[i]);
    }
}

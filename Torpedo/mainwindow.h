#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "torpedomodel.h"
#include <stdlib.h> 

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *);

private:
    QVector<QLineF> _tableGraphicsOwn; // saját mező grafikája, egy vektorban tárljuk a kirajzoló vonalakat
    QVector<QLineF> _tableGraphicsEnemy; // ellenfél mező grafikája, egy vektorban tárljuk a kirajzoló vonalakat
    QRectF _shipGraphics;
    Torpedomodel _model; // a játékot megvalósító modell

};
#endif // MAINWINDOW_H

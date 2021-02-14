#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "torpedomodel.h" 

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    QVector<QLineF> _tableGraphicsOwn; // saját mező grafikája, egy vektorban tárljuk a kirajzoló vonalakat
    QVector<QLineF> _tableGraphicsEnemy; // ellenfél mező grafikája, egy vektorban tárljuk a kirajzoló vonalakat
    QVector<QLineF> _missGraphics; // kereszt grafikája (ha nem találtunk)
    QRectF _shipGraphics;
    Torpedomodel _model; // a játékot megvalósító modell
    int _boardHW;
    int _boardSide;

};
#endif // MAINWINDOW_H

#include "mainwindow.h"
#include <QMessageBox>
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setMinimumSize(430, 400);
    setBaseSize(430,400);
    setWindowTitle(tr("Torpedo"));

    int tableSize = 16;
    
    for(int i = 0; i <= tableSize; i++)
    {
        //koordináták (honnan-vízszintes, honnan-függőleges, hova-vízszintes, hova-függőleges)
        //saját tábla vízszintes csíkok
        _tableGraphicsOwn.append(QLineF(10, (i * 200 / tableSize) + 10, 210,  (i * 200 / tableSize) + 10));
        //saját tábla függőleges csíkok
        _tableGraphicsOwn.append(QLineF((i * 200 / tableSize) + 10, 10,  (i * 200 / tableSize) + 10, 210));
    }
    for(int i = 0; i <= tableSize; i++)
    {
        //ellenfél tábla vízszintes csíkok
        _tableGraphicsEnemy.append(QLineF(220, (i * 200 / tableSize) + 10, 420,  (i * 200 / tableSize) + 10));
        //ellenfél tábla függőleges csíkok
        _tableGraphicsEnemy.append(QLineF( (i * 200 / tableSize) + 220, 10,  (i * 200 / tableSize) + 220, 210));
    }
    
}

MainWindow::~MainWindow()
{
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this); // rajzoló objektum
    painter.setRenderHint(QPainter::Antialiasing); // élsimítás használata
    painter.scale(width() / 430.0, height() / 400.0); // skálázás

    painter.setPen(QPen(Qt::black, 1)); // toll beállítása
    painter.drawLines(_tableGraphicsOwn); // tábla kirajzolása
    painter.drawLines(_tableGraphicsEnemy); // tábla kirajzolása
}

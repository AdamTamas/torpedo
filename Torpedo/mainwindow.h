#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QVector<QLineF> _tableGraphicsOwn; // saját mező grafikája, egy vektorban tárljuk a kirajzoló vonalakat
    QVector<QLineF> _tableGraphicsEnemy; // ellenfél mező grafikája, egy vektorban tárljuk a kirajzoló vonalakat

protected:
    void paintEvent(QPaintEvent *);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H

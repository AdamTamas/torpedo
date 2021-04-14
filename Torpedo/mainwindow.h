#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "modelTorpedo.h"
#include "widgetNewGameOptions.h"
#include "widgetConnectGameOptions.h"
#include "widgetChat.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void setGraphics();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);

private slots:
    void model_gameWon(int won); // eseménykezelők a modell eseményeire
    void model_needNewGraphics(); // eseménykezelők a modell eseményeire

private:
    QVector<QLineF> _tableGraphics; // mező grafikája, egy vektorban tárljuk a kirajzoló vonalakat
    QVector<QLineF> _missGraphics; // kereszt grafikája (ha nem találtunk)
    QRectF _shipGraphics; // hajókocka
    modelTorpedo _model; // a játékot megvalósító modell
    int _boardHW; // tábla szélessége és magassága (NxN)
    int _boardSide; // "margó"
    widgetNewGameOptions* _newGameOptionsWidget; // új játék beálítás ablakot biztosító ablak
    widgetShippPlace* _shippplacewidget; // a mentést biztosító ablak
    widgetChat* _chatWidget;
    bool _newGameStarted;
};
#endif // MAINWINDOW_H

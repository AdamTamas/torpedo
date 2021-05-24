#ifndef SHIPPPLACEWIDGET_H
#define SHIPPPLACEWIDGET_H
#include "basebuildingblocks.h"
#include "playerBase.h"
#include <QVector>
#include <QDialog>
#include <QPushButton>

class widgetShipPlace : public QDialog // Új játékhoz beállítások ablak
{
    Q_OBJECT
public:
    explicit widgetShipPlace(playerBase* player, QWidget *parent = 0);

private:
    void setGraphics(NewGameData data);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent( QMouseEvent *event);
    QVector<QLineF> _tableGraphics; // mező grafikája, egy vektorban tárljuk a kirajzoló vonalakat
    int _boardHW = 200;
    int _boardSide = 10;
    int areaSize;
    QRectF _shipblock; // hajókocka
    playerBase* _p;
    bool HoldingShip;
};

#endif // SHIPPPLACEWIDGET_H

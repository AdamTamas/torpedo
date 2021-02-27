#ifndef SHIPPPLACEWIDGET_H
#define SHIPPPLACEWIDGET_H
#include "basebuildingblocks.h"
#include "baseplayer.h"
#include <QVector>
#include <QDialog>
#include <QPushButton>

class shippplacewidget : public QDialog // Új játékhoz beállítások ablak
{
    Q_OBJECT
public:
    explicit shippplacewidget(NewGameData &data/*baseplayer* player*/, QWidget *parent = 0);
    void placeShips(NewGameData data, std::vector<std::vector<Area>> &board);
    void setGraphics(NewGameData data);
    void paintEvent(QPaintEvent *);

private:
    QVector<QLineF> _tableGraphics; // mező grafikája, egy vektorban tárljuk a kirajzoló vonalakat
    int _boardHW = 200;
    int _boardSide = 10;
    int areaSize = 8;
    QRectF _shipGraphics[4]; // hajókocka
};

#endif // SHIPPPLACEWIDGET_H

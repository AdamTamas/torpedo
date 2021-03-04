#include "shippplacewidget.h"
#include "baseplayer.h"
#include <QPainter>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <math.h>

shippplacewidget::shippplacewidget(baseplayer* player, QWidget *parent) :
    QDialog(parent)
{
    setMinimumSize(_boardHW + _boardSide*2, _boardHW + _boardSide*2);
    setWindowTitle(tr("Torpedo"));
    _p = player;
    HoldingShip = false;
    setGraphics(_p->_data);
}

void shippplacewidget::setGraphics(NewGameData data)
{
    areaSize = data.areaSize;
    _tableGraphics.clear();
    // tábla rácsozata
    for(int i = 0; i <= areaSize; i++)
    {
        // koordináták (honnan-vízszintes, honnan-függőleges, hova-vízszintes, hova-függőleges)
        // vízszintes csíkok
        _tableGraphics.append(QLineF(_boardSide, (i * _boardHW / areaSize) + _boardSide,
                                        _boardHW + _boardSide, (i * _boardHW / areaSize) + _boardSide));
        // függőleges csíkok
        _tableGraphics.append(QLineF((i * _boardHW / areaSize) + _boardSide, _boardSide,
                                        (i * _boardHW / areaSize) + _boardSide, _boardHW + _boardSide));
    }

    // teljes hajógrafikák
        _shipblock = QRectF(0, 0, (_boardHW / areaSize), (_boardHW / areaSize));

}

void shippplacewidget::paintEvent(QPaintEvent *)
{
    setGraphics(_p->_data);
    QPainter painter(this); // rajzoló objektum
    painter.setRenderHint(QPainter::Antialiasing); // élsimítás használata
    painter.scale(width() / (float)(_boardHW + _boardSide*2), height() / (float)(_boardHW + _boardSide*2)); // skálázás

    painter.setPen(QPen(Qt::black, 1)); // toll beállítása
    painter.drawLines(_tableGraphics); // tábla kirajzolása
    for(int i = 0; i < _p->_data.areaSize; i++)
    {
        for(int j = 0; j < _p->_data.areaSize; j++)
        {
            painter.save(); // elmentjük a rajztulajdonságokat
            painter.translate((i * _boardHW / _p->_data.areaSize) + _boardSide ,
                              (j * _boardHW / _p->_data.areaSize) + _boardSide); // elmozdítjuk a rajzpontot a megfelelő mezőre
            Coordinate c{i,j};
            // hajó felrajzolása
            if ( _p->getField(c).shipID)
            {
                painter.fillRect(_shipblock,QBrush(Qt::black)); // hajógrafika kiválasztása
            }
            painter.restore(); // visszatöltjük a korábbi állapotot
        }
    }
}

void shippplacewidget::mousePressEvent(QMouseEvent *event)
{
    float newWidthUnit = width()/220.0;
    float newHeightUnit = height()/220.0;
    int x = floor((event->pos().x() - newWidthUnit*_boardSide) * _p->_data.areaSize / (newWidthUnit*_boardHW));
    int y = floor((event->pos().y() - newHeightUnit*_boardSide) * _p->_data.areaSize / (newHeightUnit*_boardHW));
    if(x < _p->_data.areaSize && x >= 0 && y < _p->_data.areaSize && y >= 0)
    {
        Coordinate c; c.x = x; c.y = y;
        if ( event->button() == Qt::LeftButton )
        {
            _p->pickUp(c); // hajó megfogása
            HoldingShip = true;
        }
        if ( event->button() == Qt::RightButton )
        {
            _p->rotate(c); // hajó megfogása
        }
        update();
    }

}

void shippplacewidget::mouseMoveEvent(QMouseEvent *event)
{
    if ( event->button() == Qt::LeftButton && HoldingShip )
    {
        float newWidthUnit = width()/220.0;
        float newHeightUnit = height()/220.0;
        int x = floor((event->pos().x() - newWidthUnit*_boardSide) * _p->_data.areaSize / (newWidthUnit*_boardHW));
        int y = floor((event->pos().y() - newHeightUnit*_boardSide) * _p->_data.areaSize / (newHeightUnit*_boardHW));

        if(x < _p->_data.areaSize && x >= 0 && y < _p->_data.areaSize && y >= 0)
        {
            Coordinate c; c.x = x; c.y = y;
            _p->moveShip(c); // elmozgatjuk a hajót az aktuális egérpozícióra
            update();
        }
        update();
    }

}

void shippplacewidget::mouseReleaseEvent(QMouseEvent *event)
{
    if ( event->button() == Qt::LeftButton )
    {
        float newWidthUnit = width()/220.0;
        float newHeightUnit = height()/220.0;
        int x = floor((event->pos().x() - newWidthUnit*_boardSide) * _p->_data.areaSize / (newWidthUnit*_boardHW));
        int y = floor((event->pos().y() - newHeightUnit*_boardSide) * _p->_data.areaSize / (newHeightUnit*_boardHW));

        if(x < _p->_data.areaSize && x >= 0 && y < _p->_data.areaSize && y >= 0)
        {
            Coordinate c; c.x = x; c.y = y;
            _p->putDownShip(); // letesszük a hajót
            HoldingShip = false;
            update();
        }
        update();
    }

}


#include "shippplacewidget.h"
#include "baseplayer.h"
#include <QPainter>
#include <QVBoxLayout>
 #include <QPixmap>

shippplacewidget::shippplacewidget(baseplayer* player, QWidget *parent) :
    QDialog(parent)
{
    setMinimumSize(_boardHW + _boardSide*2, _boardHW + _boardSide*2);
    setWindowTitle(tr("Torpedo"));
    _p = player;
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


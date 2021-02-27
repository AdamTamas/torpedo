#include "shippplacewidget.h"
#include "baseplayer.h"
#include <QPainter>
#include <QVBoxLayout>
 #include <QPixmap>

shippplacewidget::shippplacewidget(NewGameData &data/*baseplayer* player*/, QWidget *parent) :
    QDialog(parent)
{
    setMinimumSize(_boardHW + _boardSide*2, _boardHW + _boardSide*2);
    setWindowTitle(tr("Torpedo"));
    setGraphics(data);
}

void shippplacewidget::placeShips(NewGameData data, std::vector<std::vector<Area>> &board)
{

    setGraphics(data);
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
    for (int i = 0; i < 4; i++) {
        _shipGraphics[i] = QRectF(0, 0, (_boardHW / areaSize), (_boardHW / areaSize)*(i+2));
    }

}

void shippplacewidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this); // rajzoló objektum
    painter.setRenderHint(QPainter::Antialiasing); // élsimítás használata
    painter.scale(width() / (float)(_boardHW + _boardSide*2), height() / (float)(_boardHW + _boardSide*2)); // skálázás

    painter.setPen(QPen(Qt::black, 1)); // toll beállítása
    painter.drawLines(_tableGraphics); // tábla kirajzolása
    painter.save(); // elmentjük a rajztulajdonságokat
    /*
    painter.translate( _boardHW  + _boardSide ,  0); // elmozdítjuk a rajzpontot a megfelelő mezőre
    painter.drawLines(_tableGraphics); // ellenfél tábla kirajzolása
    */
    painter.restore(); // visszatöltjük a korábbi állapotot

}

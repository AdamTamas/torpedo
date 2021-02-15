#include "mainwindow.h"
#include <QMessageBox>
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include "torpedomodel.h"
#include <math.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    _boardHW = 200;
    _boardSide = 10;
    setMinimumSize(_boardHW*2 + _boardSide*3, _boardHW + _boardSide*2);
    setBaseSize(_boardHW*2 + _boardSide*3, _boardHW + _boardSide*2);
    setWindowTitle(tr("Torpedo"));

    //saját tábla rácsozata
    for(int i = 0; i <= _model.areaSize; i++)
    {
        //koordináták (honnan-vízszintes, honnan-függőleges, hova-vízszintes, hova-függőleges)
        //saját tábla vízszintes csíkok
        _tableGraphics.append(QLineF(_boardSide, (i * _boardHW / _model.areaSize) + _boardSide,
                                        _boardHW + _boardSide, (i * _boardHW / _model.areaSize) + _boardSide));
        //saját tábla függőleges csíkok
        _tableGraphics.append(QLineF((i * _boardHW / _model.areaSize) + _boardSide, _boardSide,
                                        (i * _boardHW / _model.areaSize) + _boardSide, _boardHW + _boardSide));
    }

    // hajó és egyéb kis grafikák
    _shipGraphics = QRectF(0, 0, _boardHW / _model.areaSize, _boardHW / _model.areaSize);
    _missGraphics.append(QLineF(3, 3, (_boardHW / _model.areaSize) - 3, (_boardHW / _model.areaSize) - 3));
    _missGraphics.append(QLineF(3, (_boardHW / _model.areaSize) - 3, (_boardHW / _model.areaSize) - 3, 3));
    // új játék kezdése első alkalomhoz
    _model.newGame();
}

MainWindow::~MainWindow()
{
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this); // rajzoló objektum
    painter.setRenderHint(QPainter::Antialiasing); // élsimítás használata
    painter.scale(width() / (float)(_boardHW*2 + _boardSide*3), height() / (float)(_boardHW + _boardSide*2)); // skálázás

    painter.setPen(QPen(Qt::black, 1)); // toll beállítása
    painter.drawLines(_tableGraphics); // tábla kirajzolása
    painter.save(); // elmentjük a rajztulajdonságokat
    painter.translate( _boardHW  + _boardSide ,  0); // elmozdítjuk a rajzpontot a megfelelő mezőre
    painter.drawLines(_tableGraphics); // ellenfél tábla kirajzolása
    painter.restore(); // visszatöltjük a korábbi állapotot

    // saját tábla hajók és lövések felrajzolása
    for(int i = 0; i < _model.areaSize; i++)
    {
        for(int j = 0; j < _model.areaSize; j++)
        {
            painter.save(); // elmentjük a rajztulajdonságokat
            painter.translate((i * _boardHW / _model.areaSize) + _boardSide ,
                              (j * _boardHW / _model.areaSize) + _boardSide); // elmozdítjuk a rajzpontot a megfelelő mezőre
            Area a = _model.getField(i, j);
            // hajó felrajzolása
            if ( a.shipID && !a.isShot)
            {
                painter.fillRect(_shipGraphics,QBrush(Qt::black)); // hajógrafika kiválasztása
            }
            if ( a.shipID && a.isShot && _model.getShipByID(a.shipID).hitPoint)
            {
                painter.fillRect(_shipGraphics,QBrush(Qt::darkRed)); // hajógrafika kiválasztása sárült hajóhoz
            }
            if ( a.shipID && a.isShot && !_model.getShipByID(a.shipID).hitPoint)
            {
                painter.fillRect(_shipGraphics,QBrush(Qt::red)); // hajógrafika kiválasztása elsűlyedt hajóhoz
            }
            if ( !a.shipID && a.isShot )
            {
                painter.drawLines(_missGraphics);           // miss kirajzolása
            }
            painter.restore(); // visszatöltjük a korábbi állapotot
        }
    }
    // ellenfél tábla hajók és lövések felrajzolása
    for(int i = 0; i < _model.areaSize; i++)
    {
        for(int j = 0; j < _model.areaSize; j++)
        {
            painter.save(); // elmentjük a rajztulajdonságokat
            painter.translate((i * _boardHW / _model.areaSize) + _boardHW + _boardSide*2,
                              (j * _boardHW / _model.areaSize) + _boardSide); // elmozdítjuk a rajzpontot a megfelelő mezőre
            Area a = _model.getEnemyField(i, j);
            // lövések felrajzolása
            if ( a.shipID && a.isShot && _model.getEnemyShipByID(a.shipID).hitPoint)
            {
                painter.fillRect(_shipGraphics,QBrush(Qt::darkRed)); // hajógrafika kiválasztása sárült hajóhoz
            }
            if ( a.shipID && a.isShot && !_model.getEnemyShipByID(a.shipID).hitPoint)
            {
                painter.fillRect(_shipGraphics,QBrush(Qt::red)); // hajógrafika kiválasztása elsűlyedt hajóhoz
            }
            if ( !a.shipID && a.isShot )
            {
                painter.drawLines(_missGraphics);           // miss kirajzolása
            }
            painter.restore(); // visszatöltjük a korábbi állapotot
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{       
    if (event->key() == Qt::Key_N && QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
        // lekezeljük a Ctrl+N kombinációt
        _model.newGame();
        update();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    float newWidthUnit = width()/430.0;
    float newHeightUnit = height()/220.0;
    // az event->pos() megadja az egérpozíciót, ami QPoint típusú, ebbõl kiszámolható, melyik mezőn vagyunk:
    int x = floor((event->pos().x() - newWidthUnit*(_boardHW + _boardSide*2)) * _model.areaSize / (newWidthUnit*_boardHW));
    int y = floor((event->pos().y() - newHeightUnit*_boardSide) * _model.areaSize / (newHeightUnit*_boardHW));

    if(x < _model.areaSize && x >= 0 && y < _model.areaSize && y >= 0)
    {
        _model.stepGame(x, y); // játék léptetése
        update();
    }
}

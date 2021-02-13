#include "mainwindow.h"
#include <QMessageBox>
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include "torpedomodel.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setMinimumSize(430, 400);
    setBaseSize(430,400);
    setWindowTitle(tr("Torpedo"));

    //saját tábla rácsozata
    for(int i = 0; i <= _model.areaSize; i++)
    {
        //koordináták (honnan-vízszintes, honnan-függőleges, hova-vízszintes, hova-függőleges)
        //saját tábla vízszintes csíkok
        _tableGraphicsOwn.append(QLineF(10, (i * 200 / _model.areaSize) + 10, 210,  (i * 200 / _model.areaSize) + 10));
        //saját tábla függőleges csíkok
        _tableGraphicsOwn.append(QLineF((i * 200 / _model.areaSize) + 10, 10,  (i * 200 / _model.areaSize) + 10, 210));
    }
    // ellenfél táblarácsok
    for(int i = 0; i <= _model.areaSize; i++)
    {
        //ellenfél tábla vízszintes csíkok
        _tableGraphicsEnemy.append(QLineF(220, (i * 200 / _model.areaSize) + 10, 420,  (i * 200 / _model.areaSize) + 10));
        //ellenfél tábla függőleges csíkok
        _tableGraphicsEnemy.append(QLineF( (i * 200 / _model.areaSize) + 220, 10,  (i * 200 / _model.areaSize) + 220, 210));
    }
    // hajógrafika
    _shipGraphics = QRectF(0, 0, 200 / _model.areaSize, 200 / _model.areaSize);
    _missGraphics.append(QLineF(3, 3, (200 / _model.areaSize) - 3, (200 / _model.areaSize) - 3));
    _missGraphics.append(QLineF(3, (200 / _model.areaSize) - 3, (200 / _model.areaSize) - 3, 3));
    _model.newGame();
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

    // TODO generalizálni a 2 tába felrajzolását
    // ellenfél tábla hajók és lövések felrajzolása
    for(int i = 0; i < _model.areaSize; i++)
    {
        for(int j = 0; j < _model.areaSize; j++)
        {
            painter.save(); // elmentjük a rajztulajdonságokat
            painter.translate((i * 200 / _model.areaSize) + 10 , (j * 200 / _model.areaSize) + 10); // elmozdítjuk a rajzpontot a megfelelő mezőre
            Torpedomodel::Area a = _model.getField(i, j);
            // hajó felrajzolása
            if ( a.shipID && !a.isShot)
            {
                painter.fillRect(_shipGraphics,QBrush(Qt::black)); // hajógrafika kiválasztása
            }
            if ( a.shipID && a.isShot)
            {
                painter.fillRect(_shipGraphics,QBrush(Qt::darkRed)); // hajógrafika kiválasztása
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
            painter.translate((i * 200 / _model.areaSize) + 220 , (j * 200 / _model.areaSize) + 10); // elmozdítjuk a rajzpontot a megfelelő mezőre
            Torpedomodel::Area a = _model.getEnemyField(i, j);
            // hajó felrajzolása
            if ( a.shipID && !a.isShot)
            {
                painter.fillRect(_shipGraphics,QBrush(Qt::black)); // hajógrafika kiválasztása
            }
            if ( a.shipID && a.isShot)
            {
                painter.fillRect(_shipGraphics,QBrush(Qt::darkRed)); // hajógrafika kiválasztása
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

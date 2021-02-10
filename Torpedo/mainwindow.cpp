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
    for(int i = 0; i <= areaSize; i++)
    {
        //koordináták (honnan-vízszintes, honnan-függőleges, hova-vízszintes, hova-függőleges)
        //saját tábla vízszintes csíkok
        _tableGraphicsOwn.append(QLineF(10, (i * 200 / areaSize) + 10, 210,  (i * 200 / areaSize) + 10));
        //saját tábla függőleges csíkok
        _tableGraphicsOwn.append(QLineF((i * 200 / areaSize) + 10, 10,  (i * 200 / areaSize) + 10, 210));
    }
    // ellenfél táblarácsok
    for(int i = 0; i <= areaSize; i++)
    {
        //ellenfél tábla vízszintes csíkok
        _tableGraphicsEnemy.append(QLineF(220, (i * 200 / areaSize) + 10, 420,  (i * 200 / areaSize) + 10));
        //ellenfél tábla függőleges csíkok
        _tableGraphicsEnemy.append(QLineF( (i * 200 / areaSize) + 220, 10,  (i * 200 / areaSize) + 220, 210));
    }
    // hajógrafika
    _shipGraphics = QRectF(0, 0, 200 / areaSize, 200 / areaSize);

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
    _model.newGame();
    
    for(int i = 0; i < areaSize; i++)
    {
        for(int j = 0; j < areaSize; j++)
        {
            painter.save(); // elmentjük a rajztulajdonságokat
            painter.translate((i * 200 / areaSize) + 10 , (j * 200 / areaSize) + 10); // elmozdítjuk a rajzpontot a megfelelő mezőre

            // mező kirajzolása a játékos függvényében
            if ( _model.getField(i, j).shipID )
            {
                painter.fillRect(_shipGraphics,QBrush(Qt::black));
                painter.drawRect(_shipGraphics); // hajógrafika kiválasztása
            }
            painter.restore(); // visszatöltjük a korábbi állapotot
        }
    }
    
}

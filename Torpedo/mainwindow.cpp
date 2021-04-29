#include "mainwindow.h"
#include <QMessageBox>
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include "modelTorpedo.h"
#include <math.h>
#include <QTextStream>
#include <QTcpSocket>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    _boardHW = 200;
    _boardSide = 10;
    setMinimumSize(_boardHW*2 + _boardSide*3, _boardHW + _boardSide*2);
    setBaseSize(_boardHW*2 + _boardSide*3, _boardHW + _boardSide*2);
    setWindowTitle(tr("Torpedo"));
    _newGameOptionsWidget = NULL;
    _chatWidget = new widgetChat();
    setGraphics();

    // model eseményeinek feldolgozása
    connect(&_model, SIGNAL(gameWon(int)), this, SLOT(model_gameWon(int)));
    connect(&_model, SIGNAL(needNewGraphics()), this, SLOT(model_needNewGraphics()));
    connect(&_model, SIGNAL(needGraphicsUpdate()), this, SLOT(model_needGraphicsUpdate()));
    connect(&_model, SIGNAL(gotNewData()), this, SLOT(model_gotNewData()));
    connect(&_model.cModel, SIGNAL(msgRecieved(QString)), this, SLOT(model_msgRecieved(QString)));
    connect(_chatWidget->_sendButton, SIGNAL(clicked()), this, SLOT(_sendMSG()));

    // új játék kezdése első alkalomhoz
    _model.newGame();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setGraphics()
{
    _tableGraphics.clear();
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
    _shipGraphics = QRectF(0, 0, (_boardHW / _model.areaSize)+1, (_boardHW / _model.areaSize)+1);
    _missGraphics.clear();
    _missGraphics.append(QLineF(3, 3, (_boardHW / _model.areaSize) - 3, (_boardHW / _model.areaSize) - 3));
    _missGraphics.append(QLineF(3, (_boardHW / _model.areaSize) - 3, (_boardHW / _model.areaSize) - 3, 3));
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
            Coordinate c; c.x = i; c.y = j;
            Area a = _model.getField(c);
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
            Coordinate c; c.x = i; c.y = j;
            Area a = _model.getEnemyField(c);
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
    // lekezeljük a Ctrl+N kombinációt
    if (event->key() == Qt::Key_N && QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
        this->hide();
        widgetNewGameOptions newGameOptionsWidget(&_model, this);
        if(newGameOptionsWidget.exec() == QDialog::Rejected)
        {
            this->show();
            return;
        }
        if(_model.playerOne->_data.online)
        {
            _model.connectToHost("localhost", 3333);
            _model.cModel.setNickName("Player1");
            _chatWidget->open();
        }


        widgetShippPlace shipPlaceWidget(_model.playerOne, this);
        shipPlaceWidget.exec();
        this->show();
    }
    // lekezeljük a Ctrl+C kombinációt
    if (event->key() == Qt::Key_C && QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
        this->hide();
        widgetConnectGameOptions connectGameOptionsWidget(this);
        if(connectGameOptionsWidget.exec() == QDialog::Rejected){
            this->show();
            return;
        }
        _model.connectToHost(connectGameOptionsWidget.hostname(), connectGameOptionsWidget.port());
        _model.cModel.setNickName("Player2");
        _chatWidget->open();
/*
        widgetShippPlace shipPlaceWidget(_model.playerOne, this);
        shipPlaceWidget.exec();
        _model.cModel.sendReady();
        this->show();*/

    }
    // lekezeljük a Ctrl+U kombinációt
    if (event->key() == Qt::Key_U && QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
        _chatWidget->open();
    }
}

void MainWindow::model_msgRecieved(QString S){
    _chatWidget->msgRecieved(S);
}



void MainWindow::model_gotNewData(){
    this->hide();
    widgetShippPlace shipPlaceWidget(_model.playerOne, this);
    shipPlaceWidget.exec();
    _model.cModel.sendReady();
    this->show();
}

void MainWindow::_sendMSG(){
    _model.cModel.sendMessenge(_chatWidget->_send());
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
        Coordinate c; c.x = x; c.y = y;
        _model.stepGame(c); // játék léptetése
        update();
    }
}

void MainWindow::model_gameWon(int won)
{
    // az eredmény függvényében jelenítjük meg a győztest
    if (won)
    {
        QMessageBox::information(this, ("Torpedo"), ("Játék vége! Nyertél!"));
        _model.newGame();
    }else{
        QMessageBox::information(this, ("Torpedo"), ("Játék vége! Vesztettél!"));
        _model.newGame();
    }
}

void MainWindow::model_needNewGraphics()
{ setGraphics(); }


void MainWindow::model_needGraphicsUpdate()
{ update(); }

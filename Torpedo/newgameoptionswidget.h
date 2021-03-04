#ifndef NEWGAMEOPTIONSWIDGET_H
#define NEWGAMEOPTIONSWIDGET_H

#include <QDialog>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include "basebuildingblocks.h"
#include "torpedomodel.h"
#include "shippplacewidget.h"

class newgameoptionswidget : public QDialog // Új játékhoz beállítások ablak
{
    Q_OBJECT
public:
    // Explicit specifies that the constructor is explicit,
    // it cannot be used for implicit conversions and copy-initialization.
    explicit newgameoptionswidget(Torpedomodel* model, QWidget *parent = 0);


protected:
    std::vector<QComboBox*> _shipQuantitiesComboBoxes;
    QComboBox* _comboBoxBoard;
    QCheckBox* _isOnline;

    QPushButton* _okButton;
    QPushButton* _cancelButton;

private slots:
    void _newGameSlot(); // eseménykezelők a modell eseményeire

private:
    int _maxShipSize = 5;
    int _maxShipQuantity = 3;
    int _maxBoardSize = 17;
    Torpedomodel* _model;
    shippplacewidget* _shippplacewidget; // a mentést biztosító ablak
};


#endif // NEWGAMEOPTIONSWIDGET_H

#include "newgameoptionswidget.h"

#include <QVBoxLayout>
#include <QLabel>

newgameoptionswidget::newgameoptionswidget(QWidget *parent) :
    QDialog(parent)
{
    setFixedSize(300, 200);
    setWindowTitle("Játékbeállítások");

    _okButton = new QPushButton("Ok");
    _cancelButton = new QPushButton("Mégse");

    // függőleges layout az elemeknek
    QVBoxLayout* vlayout = new QVBoxLayout();


    // pájaméret
    QHBoxLayout* hlayoutBoard = new QHBoxLayout;
    hlayoutBoard->addWidget(new QLabel("Pályaméret:"));
    QComboBox* comboBoxBoard = new QComboBox;
    for(int i = 5; i < _maxBoardSize; i++)
    {
        comboBoxBoard->addItem(QString::number(i));
    }
    hlayoutBoard->addWidget(comboBoxBoard);
    vlayout->addLayout(hlayoutBoard);

    // combobox hajómennyiségeknek
    std::vector<QHBoxLayout*> hlayoutShips;
    for(int i = 0; i < _maxShipSize-1; i++)
    {
        _shipQuantitiesComboBoxes.push_back(new QComboBox);
        for(int j = 0; j < _maxShipQuantity; j++)
        {
            _shipQuantitiesComboBoxes[i]->addItem(QString::number(j));
        }
        hlayoutShips.push_back(new QHBoxLayout());
        hlayoutShips[i]->addWidget(new QLabel(QString::number(i+2)+" méretű hajó:"));
        hlayoutShips[i]->addWidget(_shipQuantitiesComboBoxes[i]);
        vlayout->addLayout(hlayoutShips[i]);
    }

    // alsó gombok
    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->addWidget(_okButton);
    hlayout->addWidget(_cancelButton);

    vlayout->addLayout(hlayout);

    setLayout(vlayout);

    connect(_okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}


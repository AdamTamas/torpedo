#include "widgetNewGameOptions.h"

#include <QVBoxLayout>
#include <QLabel>

widgetNewGameOptions::widgetNewGameOptions(modelTorpedo* model, QWidget *parent) :
    QDialog(parent)
{
    _shippplacewidget = NULL;
    _model = model;
    setFixedSize(300, 200);
    setWindowTitle("Játékbeállítások");

    _okButton = new QPushButton("Ok");
    _cancelButton = new QPushButton("Mégse");

    // függőleges layout az elemeknek
    QVBoxLayout* vlayout = new QVBoxLayout();


    // pájaméret
    QHBoxLayout* hlayoutBoard = new QHBoxLayout;
    hlayoutBoard->addWidget(new QLabel("Pályaméret:"));
    _comboBoxBoard = new QComboBox;
    for(int i = 5; i < _maxBoardSize; i++)
    {
        _comboBoxBoard->addItem(QString::number(i));
    }
    hlayoutBoard->addWidget(_comboBoxBoard);
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
    hlayout->addWidget(new QLabel("Online:"));
    _isOnline = new QCheckBox();
    hlayout->addWidget(_isOnline);
    hlayout->addWidget(_okButton);
    hlayout->addWidget(_cancelButton);
    vlayout->addLayout(hlayout);

    setLayout(vlayout);

    connect(_okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_okButton, SIGNAL(clicked()), this, SLOT(_newGameSlot()));
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}
void widgetNewGameOptions::_newGameSlot()
{
    NewGameData data;
    data.areaSize = _comboBoxBoard->currentText().toInt();
    for(size_t i = 0; i < _shipQuantitiesComboBoxes.size(); i++)
    {
        data.shipNumForSizes[i] = _shipQuantitiesComboBoxes[i]->currentText().toInt();
    }
    data.online = _isOnline->isChecked();

    if (_shippplacewidget == NULL) // ha még egyszer sem nyitották meg az ablakot
    {
        _shippplacewidget = new widgetShippPlace(_model->playerOne);

    }
    _model->newGameData(data);
    _shippplacewidget->open();
    //_model->newGameData(data);
}

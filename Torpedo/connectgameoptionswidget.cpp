#include "connectgameoptionswidget.h"

#include <QVBoxLayout>
#include <QLabel>

connectgameoptionswidget::connectgameoptionswidget(QWidget *parent) :
    QDialog(parent)
{
    setFixedSize(300, 200);
    setWindowTitle("Játékbeállítások");

    _okButton = new QPushButton("Ok");
    _cancelButton = new QPushButton("Mégse");

    // függőleges layout az elemeknek
    QVBoxLayout* vlayout = new QVBoxLayout();


    // alsó gombok
    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->addWidget(new QLabel("Online:"));
    hlayout->addWidget(_okButton);
    hlayout->addWidget(_cancelButton);
    vlayout->addLayout(hlayout);

    setLayout(vlayout);

    connect(_okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_okButton, SIGNAL(clicked()), this, SLOT(_connectGameSlot()));
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}
void connectgameoptionswidget::_connectGameSlot()
{
}

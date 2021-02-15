#include "newgameoptionswidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

newgameoptionswidget::newgameoptionswidget(QWidget *parent) :
    QDialog(parent)
{
    setFixedSize(300, 200);
    setWindowTitle("Játékbeállítások");

    _okButton = new QPushButton("Ok");
    _cancelButton = new QPushButton("Mégse");

    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->addWidget(_okButton);
    hlayout->addWidget(_cancelButton);

    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->addLayout(hlayout);

    setLayout(vlayout);

    connect(_okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}


#include "widgetConnectGameOptions.h"

#include <QVBoxLayout>
#include <QLabel>


// Helper átméretezni a textEdit paneleket
void widgetConnectGameOptions::setHeight (QPlainTextEdit *ptxt, int nRows)
{
    QTextDocument *pdoc = ptxt->document ();
    QFontMetrics fm (pdoc->defaultFont ());
    QMargins margins = ptxt->contentsMargins ();
    int nHeight = fm.lineSpacing () * nRows +
        (pdoc->documentMargin () + ptxt->frameWidth ()) * 2 +
        margins.top () + margins.bottom ();
    ptxt->setFixedHeight (nHeight);
    ptxt->setFixedWidth(nHeight*7);
}

widgetConnectGameOptions::widgetConnectGameOptions(QWidget *parent) :
    QDialog(parent)
{
    setFixedSize(300, 200);
    setWindowTitle("Játékbeállítások");

    _okButton = new QPushButton("Ok");
    _cancelButton = new QPushButton("Mégse");
    _IP = new QPlainTextEdit();
    _Port  = new QPlainTextEdit();
    setHeight(_IP, 1);
    setHeight(_Port, 1);

    // függőleges layout az elemeknek
    QVBoxLayout* vlayout = new QVBoxLayout();


    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->addWidget(new QLabel("IP cím:"));
    hlayout->addWidget(_IP);
    QHBoxLayout* hlayout1 = new QHBoxLayout();
    hlayout1->addWidget(new QLabel("Port:"));
    hlayout1->addWidget(_Port);
    // alsó gombok
    QHBoxLayout* hlayout2 = new QHBoxLayout();
    hlayout2->addWidget(_okButton);
    hlayout2->addWidget(_cancelButton);
    vlayout->addLayout(hlayout);
    vlayout->addLayout(hlayout1);
    vlayout->addLayout(hlayout2);

    setLayout(vlayout);

    connect(_okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_okButton, SIGNAL(clicked()), this, SLOT(_connectGameSlot()));
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}
void widgetConnectGameOptions::_connectGameSlot()
{
}

#include "widgetChat.h"

#include <QVBoxLayout>
#include <QLabel>


// Helper átméretezni a textEdit paneleket
void widgetChat::setHeight (QPlainTextEdit *ptxt, int nRows)
{
    QTextDocument *pdoc = ptxt->document ();
    QFontMetrics fm (pdoc->defaultFont ());
    QMargins margins = ptxt->contentsMargins ();
    int nHeight = fm.lineSpacing () * nRows +
        (pdoc->documentMargin () + ptxt->frameWidth ()) * 2 +
        margins.top () + margins.bottom ();
    ptxt->setFixedHeight (nHeight);
}

widgetChat::widgetChat(QWidget *parent) :
    QDialog(parent)
{
    setMinimumSize(300, 200);
    setBaseSize(300, 200);
    setWindowTitle("Csevegés");

    _sendButton = new QPushButton("Küld");
    _messengeField = new QPlainTextEdit();
    _chatField  = new QPlainTextEdit();
    setHeight(_messengeField, 1);

    // függőleges layout az elemeknek
    QVBoxLayout* vlayout = new QVBoxLayout();


    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->addWidget(_messengeField);
    hlayout->addWidget(_sendButton);

    vlayout->addWidget(_chatField);
    vlayout->addLayout(hlayout);

    setLayout(vlayout);

    connect(_sendButton, SIGNAL(clicked()), this, SLOT(_send()));
}
void widgetChat::_send()
{
}

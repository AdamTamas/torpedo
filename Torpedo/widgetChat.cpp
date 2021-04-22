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
    _chatField->setReadOnly(true);
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

QString widgetChat::_send()
{
     // üzenetküldés meghívás
    QString s = _messengeField->toPlainText();
    // írható mező kitisztítása
    _messengeField->clear();
    return s;
}

void widgetChat::msgRecieved(QString msg)
{
    /*
    // szövegszín beállítás
     QPalette p = _chatField->palette();
     p.setColor(QPalette::Text, Qt::red);
     _chatField->setPalette(p);
     */
    _chatField->appendPlainText(msg);
}


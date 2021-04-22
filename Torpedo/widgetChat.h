#ifndef WIDGETCHAT_H
#define WIDGETCHAT_H

#include <QDialog>
#include <QPushButton>
#include <QPlainTextEdit>
#include "modelConnection.h"

class widgetChat : public QDialog // online catlakozás beállítások ablak
{
    Q_OBJECT
public:
    // Explicit specifies that the constructor is explicit,
    // it cannot be used for implicit conversions and copy-initialization.
    explicit widgetChat(QWidget *parent = 0);
    void append(QString S);
    void connectToHost(QTcpSocket* S);
    void setNickName(QString name);
    void msgRecieved(QString msg);
    QPushButton* _sendButton;
    QString _send();

protected:
    QPushButton* _cancelButton;
    QPlainTextEdit* _messengeField;
    QPlainTextEdit* _chatField;
    void setHeight (QPlainTextEdit *ptxt, int nRows);


private:
};

#endif // WIDGETCHAT_H
